#include <stdint.h>

/* ---------------- RCC ---------------- */
#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x40))

/* ---------------- GPIOD ---------------- */
#define GPIOD_BASE      0x40020C00UL
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_AFRH      (*(volatile uint32_t*)(GPIOD_BASE + 0x24))

/* ---------------- TIM4 ---------------- */
#define TIM4_BASE       0x40000800UL
#define TIM4_CR1        (*(volatile uint32_t*)(TIM4_BASE + 0x00))
#define TIM4_CCMR1      (*(volatile uint32_t*)(TIM4_BASE + 0x18))
#define TIM4_CCER       (*(volatile uint32_t*)(TIM4_BASE + 0x20))
#define TIM4_PSC        (*(volatile uint32_t*)(TIM4_BASE + 0x28))
#define TIM4_ARR        (*(volatile uint32_t*)(TIM4_BASE + 0x2C))
#define TIM4_CCR1       (*(volatile uint32_t*)(TIM4_BASE + 0x34))

int main(void)
{
    /* 1. Enable GPIOD clock */
    RCC_AHB1ENR |= (1 << 3);

    /* 2. Set PD12 to Alternate Function mode */
    GPIOD_MODER &= ~(3 << (12 * 2));
    GPIOD_MODER |=  (2 << (12 * 2));   // AF mode

    /* 3. Select AF2 (TIM4) */
    GPIOD_AFRH &= ~(0xF << ((12 - 8) * 4));
    GPIOD_AFRH |=  (2 << ((12 - 8) * 4));

    /* 4. Enable TIM4 clock */
    RCC_APB1ENR |= (1 << 2);

    /* 5. Timer configuration */
    TIM4_PSC = 15;        // 16 MHz / 16 = 1 MHz
    TIM4_ARR = 1000 - 1;  // 1 kHz PWM frequency

    /* 6. PWM mode 1 */
    TIM4_CCMR1 |= (6 << 4);   // OC1M = 110 (PWM mode 1)
    TIM4_CCMR1 |= (1 << 3);   // OC1PE (preload enable)

    /* 7. Enable channel output */
    TIM4_CCER |= 1;

    /* 8. Set duty cycle (50%) */
    TIM4_CCR1 = 100;

    /* 9. Enable auto-reload preload */
    TIM4_CR1 |= (1 << 7);

    /* 10. Start timer */
    TIM4_CR1 |= 1;

    while (1)
    {
        // PWM runs in hardware
    }
}
