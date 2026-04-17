#include <stdint.h>

/* ---------------- RCC ---------------- */
#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x40))

/* ---------------- GPIOD ---------------- */
#define GPIOD_BASE      0x40020C00UL
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))

/* ---------------- TIM2 ---------------- */
#define TIM2_BASE       0x40000000UL
#define TIM2_CR1        (*(volatile uint32_t*)(TIM2_BASE + 0x00))
#define TIM2_DIER       (*(volatile uint32_t*)(TIM2_BASE + 0x0C))
#define TIM2_SR         (*(volatile uint32_t*)(TIM2_BASE + 0x10))
#define TIM2_PSC        (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR        (*(volatile uint32_t*)(TIM2_BASE + 0x2C))

/* ---------------- NVIC ---------------- */
#define NVIC_ISER0      (*(volatile uint32_t*)0xE000E100UL)

/* ====================== TIM2 IRQ ====================== */
void TIM2_IRQHandler(void)
{
    if (TIM2_SR & 1)     // UIF?
    {
        TIM2_SR &= ~1;   // clear UIF

        GPIOD_ODR ^= (1 << 12); // toggle LED
    }
}

/* ====================== MAIN ====================== */
int main(void)
{
    /* Enable GPIOD clock */
    RCC_AHB1ENR |= (1 << 3);

    /* PD12 output */
    GPIOD_MODER &= ~(3 << 24);
    GPIOD_MODER |=  (1 << 24);

    /* Enable TIM2 clock */
    RCC_APB1ENR |= (1 << 0);

    /* Timer config */
    TIM2_PSC = 16 - 1;      // 1 MHz tick (1us)
    TIM2_ARR = 1000 - 1;    // 1ms overflow

    TIM2_DIER |= 1;         // enable update interrupt
    TIM2_CR1  |= 1;         // start timer

    /* NVIC enable TIM2 IRQ */
    NVIC_ISER0 |= (1 << 28);

    while (1)
    {
        // ISR toggles LED
    }
}
