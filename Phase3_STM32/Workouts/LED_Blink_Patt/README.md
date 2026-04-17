# STM32F4 Bare-Metal LED Patterns using SysTick (GPIOD Pins 12–15)

This project demonstrates **advanced bare-metal GPIO control on STM32F4** using **register-level programming + SysTick delay** to create multiple LED patterns on **GPIOD pins 12, 13, 14, and 15**.

---

## 🚀 Features
- Bare-metal embedded programming (no HAL/CMSIS)
- GPIO register configuration using structs
- SysTick-based millisecond delay
- Multiple LED animation patterns
- Control of 4 LEDs (PD12–PD15)

---

## 🛠️ Hardware Requirements
- STM32F4 series microcontroller (e.g., STM32F407 Discovery board)
- 4 LEDs connected to:
  - PD12
  - PD13
  - PD14
  - PD15
- ST-Link programmer/debugger

---

## ⚙️ Working Principle

### 1. GPIO Configuration
All pins PD12–PD15 are configured as output using MODER register.

### 2. SysTick Delay
SysTick is configured for **1ms tick generation**, used for precise delays.

### 3. LED Patterns
Three different LED behaviors are implemented:

- **Run LED Pattern**
  - LEDs light one after another (chasing effect)
  - Then all are turned OFF

- **All ON/OFF Blink**
  - All 4 LEDs blink together

- **Counter Pattern**
  - Binary counting pattern displayed on LEDs

---

## 💻 Code

```c
#include <stdint.h>

#define PERIPH_BASE        0x40000000UL
#define AHB1PERIPH_BASE    (PERIPH_BASE + 0x00020000UL)
#define GPIOD_BASE         (AHB1PERIPH_BASE + 0x0C00UL)
#define RCC_BASE           (AHB1PERIPH_BASE + 0x3800UL)

// SysTick Registers
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
    for(uint32_t i = 0; i < ms; i++)
    {
        while((SYST_CSR & (1 << 16)) == 0); // wait for COUNTFLAG
    }
}

void SysTick_Init(void)
{
    SYST_RVR = 16000 - 1;   // 1ms tick (assuming 16 MHz clock)
    SYST_CVR = 0;
    SYST_CSR = (1 << 0) | (1 << 2);
}

// Chasing LED pattern
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

// All LEDs ON/OFF pattern
void allon(void){
    GPIOD->ODR = (0xF << 12);
    delay_ms(500);
    GPIOD->ODR = 0;
    delay_ms(500);
}

// Binary counter pattern
void counter_led(void){
    for (int count = 0; count < 16; count++)
    {
        GPIOD->ODR = (count << 12);
        delay_ms(300);
    }
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);              // Enable GPIOD clock
    GPIOD->MODER &= ~(0xFF << (12 * 2));   // Clear mode bits
    GPIOD->MODER |=  (0x55 << (12 * 2));   // Set PD12–PD15 as output

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
📚 What You Learn
Multi-pin GPIO control (PD12–PD15)
Bitwise LED pattern design
SysTick timer usage in embedded systems
Structured register mapping (HAL-style design)
Basic embedded state machine thinkin