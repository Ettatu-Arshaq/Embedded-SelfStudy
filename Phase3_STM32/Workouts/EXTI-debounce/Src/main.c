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
#define EXTI_PR         (*(volatile uint32_t*)(EXTI_BASE + 0x14))

/* ---------------- NVIC REGISTERS ---------------- */
#define NVIC_ISER0      (*(volatile uint32_t*)0xE000E100UL)

/* ---------------- SysTick REGISTERS ---------------- */
#define SYST_CSR        (*(volatile uint32_t*)0xE000E010UL)
#define SYST_RVR        (*(volatile uint32_t*)0xE000E014UL)
#define SYST_CVR        (*(volatile uint32_t*)0xE000E018UL)

/* ========== GLOBALS ========== */
volatile uint32_t debounce_active = 0;
volatile uint32_t debounce_counter = 0;

/* ===================================================
                       EXTI0 HANDLER
   =================================================== */
void EXTI0_IRQHandler(void)
{
    if (EXTI_PR & (1 << 0))
    {
        EXTI_PR |= (1 << 0);      // Clear pending flag

        if (!debounce_active)     // Accept only if not bouncing
        {
            debounce_active = 1;
            debounce_counter = 20;  // 20 ms debounce window

            EXTI_IMR &= ~(1 << 0);  // Disable EXTI0 temporarily

            GPIOD_ODR ^= (1 << 12); // Toggle LED
        }
    }
}

/* ===================================================
                SYSTICK HANDLER (1ms)
   =================================================== */
void SysTick_Handler(void)
{
    if (debounce_active)
    {
        if (debounce_counter > 0)
        {
            debounce_counter--;
        }
        else
        {
            debounce_active = 0;
            EXTI_IMR |= (1 << 0);   // Re-enable EXTI0
        }
    }
}

/* ===================================================
                          MAIN
   =================================================== */
int main(void)
{
    /* Enable GPIOA, GPIOD, SYSCFG */
    RCC_AHB1ENR |= (1 << 0) | (1 << 3);
    RCC_APB2ENR |= (1 << 14);

    /* PA0 = input */
    GPIOA_MODER &= ~(3 << 0);

    /* PD12 = output */
    GPIOD_MODER &= ~(3 << 24);
    GPIOD_MODER |=  (1 << 24);

    /* Map PA0 → EXTI0 */
    SYSCFG_EXTICR1 &= ~(0xF << 0);

    /* EXTI0 rising edge */
    EXTI_IMR  |= (1 << 0);
    EXTI_RTSR |= (1 << 0);

    /* Enable EXTI0 interrupt */
    NVIC_ISER0 |= (1 << 6);

    /* --- Configure SysTick for 1 ms tick --- */
    SYST_RVR = 160000 - 1;            // 1ms @ 16 MHz (HSI)
    SYST_CVR = 0;
    SYST_CSR = 7;                     // ENABLE + TICKINT + CLKSOURCE

    while (1)
    {
        // MCU waits here; ISR handles button
    }
}
