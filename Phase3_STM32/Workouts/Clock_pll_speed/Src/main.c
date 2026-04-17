#include <stdint.h>

#define RCC_BASE        0x40023800UL
#define RCC_CR          (*(volatile uint32_t*)(RCC_BASE + 0x00))
#define RCC_PLLCFGR     (*(volatile uint32_t*)(RCC_BASE + 0x04))
#define RCC_CFGR        (*(volatile uint32_t*)(RCC_BASE + 0x08))
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define FLASH_ACR       (*(volatile uint32_t*)0x40023C00UL)

#define SYST_CSR (*(volatile uint32_t*)0xE000E010)
#define SYST_RVR (*(volatile uint32_t*)0xE000E014)
#define SYST_CVR (*(volatile uint32_t*)0xE000E018)


#define GPIOD_BASE 0x40020C00UL
#define GPIOD_MODER (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR (*(volatile uint32_t*)(GPIOD_BASE + 0x14))

// Simple delay
void SysTick_Delay_ms(uint32_t ms, uint32_t cpu_freq_mhz) {
    SYST_RVR = (cpu_freq_mhz * 1000) - 1;  // reload for 1 ms
    SYST_CVR = 0;                          // clear current value
    SYST_CSR = 5;                          // enable, use CPU clock
    for (uint32_t i = 0; i < ms; i++) {
        while (!(SYST_CSR & (1 << 16)));   // wait for COUNTFLAG
    }
    SYST_CSR = 0;                          // stop timer
}


void HSE_init(void) {
    RCC_CR |= (1 << 16);            // HSEON = 1
    while (!(RCC_CR & (1 << 17)));  // Wait until HSERDY = 1
}

void pll_config(void) {
#define PLL_M 8
#define PLL_N 336
#define PLL_P 2
    RCC_PLLCFGR = (PLL_M) |
                  (PLL_N << 6) |
                  (((PLL_P / 2) - 1) << 16) |
                  (1 << 22); // PLL source = HSE
}

void pll_init(void) {
    // Set Flash latency for 168 MHz
    FLASH_ACR |= (5 << 0);  // 5 wait states

    RCC_CR |= (1 << 24);            // PLLON = 1
    while (!(RCC_CR & (1 << 25)));  // Wait until PLLRDY = 1

    RCC_CFGR &= ~(0x3);   // Clear SW bits
    RCC_CFGR |=  (0x2);   // Select PLL as system clock
    while (((RCC_CFGR >> 2) & 0x3) != 0x2); // Wait until PLL used
}

void LED_init(void) {
    RCC_AHB1ENR |= (1 << 3);  // Enable GPIOD clock

    // Set PD12–PD14 as output
    GPIOD_MODER &= ~(0x3F << 24);
    GPIOD_MODER |=  (0x15 << 24);
}

void show_clk_source(uint32_t clk_src) {
    // Turn all LEDs off
    GPIOD_ODR &= ~((1 << 12) | (1 << 13) | (1 << 14));


    if (clk_src == 0x00)
        GPIOD_ODR = (1 << 12);  // HSI
    else if (clk_src == 0x01)
        GPIOD_ODR = (1 << 13);  // HSE
    else if (clk_src == 0x02)
        GPIOD_ODR = (1 << 14);  // PLL
    else
        GPIOD_ODR = (1 << 15);  // Invalid (should never happen)
 // PLL active → PD14 ON
}

int main(void) {
    LED_init();

    HSE_init();
    pll_config();
    pll_init();
    RCC_AHB1ENR |= (1 << 3);
    GPIOD_MODER &= ~(3 << 24);
    GPIOD_MODER |=  (1 << 24);

    while (1) {
        GPIOD_ODR ^= (1 << 12);   // toggle LED
        SysTick_Delay_ms(500, 168);  // for PLL=168 MHz use 168, for HSI=16 MHz use 16
    }
}
