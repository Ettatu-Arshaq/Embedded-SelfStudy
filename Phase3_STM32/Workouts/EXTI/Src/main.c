#include <stdint.h>

/* ---------------- RCC REGISTERS ---------------- */
#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x44))

/* ---------------- GPIOA REGISTERS ---------------- */
#define GPIOA_BASE      0x40020000UL
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_PUPDR     (*(volatile uint32_t*)(GPIOA_BASE + 0x0C))

/* ---------------- GPIOD REGISTERS ---------------- */
#define GPIOD_BASE      0x40020C00UL
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))

/* ---------------- SYSCFG REGISTERS ---------------- */
#define SYSCFG_BASE     0x40013800UL
#define SYSCFG_EXTICR1  (*(volatile uint32_t*)(SYSCFG_BASE + 0x08))

/* ---------------- EXTI REGISTERS ---------------- */
#define EXTI_BASE       0x40013C00UL
#define EXTI_IMR        (*(volatile uint32_t*)(EXTI_BASE + 0x00))
#define EXTI_RTSR       (*(volatile uint32_t*)(EXTI_BASE + 0x08))
#define EXTI_FTSR       (*(volatile uint32_t*)(EXTI_BASE + 0x0C))
#define EXTI_PR         (*(volatile uint32_t*)(EXTI_BASE + 0x14))

/* ---------------- NVIC REGISTERS ---------------- */
#define NVIC_ISER0      (*(volatile uint32_t*)0xE000E100UL) // ISER0 register

/* ===================================================
                       EXTI0 HANDLER
   =================================================== */
void EXTI0_IRQHandler(void)
{
    if (EXTI_PR & (1 << 0))       // Check pending flag
    {
        EXTI_PR |= (1 << 0);      // Clear pending flag
        GPIOD_ODR ^= (1 << 12);   // Toggle LED
    }
}

/* ===================================================
                          MAIN
   =================================================== */
int main(void)
{
    /* --- Step 1: Enable clocks for GPIOA, GPIOD, SYSCFG --- */
    RCC_AHB1ENR |= (1 << 0) | (1 << 3);  // GPIOA + GPIOD
    RCC_APB2ENR |= (1 << 14);            // SYSCFG

    /* --- Step 2: Configure PA0 as input (00) --- */
    GPIOA_MODER &= ~(3 << 0);
    GPIOA_PUPDR &= ~(3 << 0);            // no pull-up/down

    /* --- Step 3: Configure PD12 as output (01) --- */
    GPIOD_MODER &= ~(3 << 24);
    GPIOD_MODER |=  (1 << 24);

    /* --- Step 4: Map EXTI0 line to PA0 --- */
    SYSCFG_EXTICR1 &= ~(0xF << 0);       // 0000 = PA0

    /* --- Step 5: Configure EXTI0 --- */
    EXTI_IMR  |= (1 << 0);               // Unmask EXTI0
    EXTI_RTSR |= (1 << 0);               // Rising-edge trigger
    EXTI_FTSR &= ~(1 << 0);              // No falling-edge

    /* --- Step 6: Enable EXTI0 interrupt in NVIC --- */
    NVIC_ISER0 |= (1 << 6);              // IRQ #6 = EXTI0

    /* --- Infinite Loop: MCU waits for interrupt --- */
    while (1)
    {
        // Nothing here — interrupt will toggle the LED
    }
}

