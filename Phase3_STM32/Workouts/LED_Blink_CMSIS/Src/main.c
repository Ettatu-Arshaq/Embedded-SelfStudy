#include <stdint.h>

#define PERIPH_BASE        0x40000000UL
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x00020000UL)
#define GPIOD_BASE         (AHB1PERIPH_BASE + 0x0C00UL)
#define RCC_BASE           (AHB1PERIPH_BASE + 0x3800UL)

//For SYS_TICK
#define SYST_CSR   (*(volatile uint32_t *)0xE000E010)
#define SYST_RVR   (*(volatile uint32_t *)0xE000E014)
#define SYST_CVR   (*(volatile uint32_t *)0xE000E018)

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
} GPIO_RegDef_t;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    uint32_t RESERVED0[2];
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
} RCC_RegDef_t;

#define GPIOD ((GPIO_RegDef_t*) GPIOD_BASE)
#define RCC   ((RCC_RegDef_t*)  RCC_BASE)

static void delay_ms(uint32_t ms)
{
//    for (uint32_t i = 0; i < ms * 800; i++) __asm__("nop");  normal delay using clk calc
    for(uint32_t i = 0; i < ms; i++)
    {
        while((SYST_CSR & (1 << 16)) == 0); // wait for COUNTFLAG
    }
}

void SysTick_Init(void)
{
    SYST_RVR = 16000 - 1;   // 1ms reload (assuming 16 MHz clock)
    SYST_CVR = 0;           // clear current value
    SYST_CSR = (1 << 0) | (1 << 2); // enable counter, clock source = processor clock
    // bit0 = ENABLE, bit1 = TICKINT (disabled), bit2 = CLKSOURCE (processor)
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);          // enable clock for GPIOD
    GPIOD->MODER &= ~(3 << (12 * 2));  // clear mode bits
    GPIOD->MODER |=  (1 << (12 * 2));  // set PD12 as output
    SysTick_Init();
    while (1)
    {
        GPIOD->ODR ^= (1 << 12);
        delay_ms(1000);
    }
}
