#include <stdint.h>

#define PERIPH_BASE        0x40000000UL
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x00020000UL)
#define GPIOD_BASE         (AHB1PERIPH_BASE + 0x0C00UL)
#define RCC_BASE           (AHB1PERIPH_BASE + 0x3800UL)

//For SYS_TICK
#define SYST_CSR   (*(volatile uint32_t *)0xE000E010)
#define SYST_RVR   (*(volatile uint32_t *)0xE000E014)
#define SYST_CVR   (*(volatile uint32_t *)0xE000E018)

volatile uint32_t msTicks = 0;

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

void delay_ms(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms)
    {
        // CPU free to run other code (poll sensors, etc.)
    }
}

void SysTick_Init(void)
{
    SYST_RVR = 16000 - 1;   // 1ms reload (assuming 16 MHz clock)
    SYST_CVR = 0;           // clear current value
    SYST_CSR = (1 << 0) |(1<<1)| (1 << 2); // enable counter, clock source = processor clock
    // bit0 = ENABLE, bit1 = TICKINT , bit2 = CLKSOURCE (processor)
}

void Run_led(void){
    GPIOD->ODR ^= (1 << 12);
    delay_ms(100);
    GPIOD->ODR ^= (1 << 13);
    delay_ms(100);
    GPIOD->ODR ^= (1 << 14);
    delay_ms(100);
    GPIOD->ODR ^= (1 << 15);
    delay_ms(100);
    GPIOD->ODR &= ~(0xFF << 12);
    delay_ms(100);
}

void allon(void){
    // Pattern 1: All blink together
    GPIOD->ODR = (0xF << 12);
    delay_ms(500);
    GPIOD->ODR = 0;
    delay_ms(500);

}

void counter_led(void){
    for (int count = 0; count < 16; count++)
    {
        GPIOD->ODR = (count << 12);
        delay_ms(300);
    }
}



void SysTick_Handler(void)
{
    msTicks++;    // runs every 1 ms
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);          // enable clock for GPIOD
    GPIOD->MODER &= ~(0xFF << (12 * 2));  // clear mode bits
    GPIOD->MODER |=  (0x55 << (12 * 2));  // set PD12 as output
    SysTick_Init();
    while (1)
    {
    	Run_led();
    	delay_ms(2000);
    	allon();
    	delay_ms(2000);
    	counter_led();
    	delay_ms(2000);

    }
}

