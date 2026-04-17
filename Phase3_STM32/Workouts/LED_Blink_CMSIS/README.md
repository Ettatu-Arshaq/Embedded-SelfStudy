# STM32F4 Bare-Metal LED Blink using SysTick (GPIOD Pin 12)

This project demonstrates a **bare-metal STM32F4 firmware** using **register-level programming + SysTick timer delay** to blink an LED connected to **PD12**.

---

## 🚀 Features
- Direct register-level programming (no HAL/CMSIS drivers)
- GPIO configuration using structured register mapping
- SysTick timer-based 1ms delay generation
- Clean peripheral abstraction using structs
- LED blinking on GPIOD Pin 12

---

## 🛠️ Hardware Requirements
- STM32F4 series microcontroller (e.g., STM32F407 Discovery board)
- On-board LED connected to PD12
- ST-Link programmer/debugger

---

## ⚙️ Working Principle

### 1. Peripheral Mapping
GPIO and RCC registers are mapped using C structures for clean access.

### 2. Clock Enable
GPIOD peripheral clock is enabled using RCC AHB1ENR register.

### 3. GPIO Configuration
PD12 is configured as a general-purpose output pin.

### 4. SysTick Timer
SysTick is configured to generate **1ms timing ticks** using:
- Reload value = 16000-1 (assuming 16 MHz clock)
- Processor clock as source
- COUNTFLAG used for delay timing

### 5. LED Toggle
LED is toggled every 1000 ms using SysTick-based delay.

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
    SYST_RVR = 16000 - 1;   // 1ms reload (assuming 16 MHz clock)
    SYST_CVR = 0;           // clear current value
    SYST_CSR = (1 << 0) | (1 << 2); // enable counter, processor clock
}

int main(void)
{
    RCC->AHB1ENR |= (1 << 3);          // enable GPIOD clock
    GPIOD->MODER &= ~(3 << (12 * 2));  // clear mode
    GPIOD->MODER |=  (1 << (12 * 2));  // set output mode

    SysTick_Init();

    while (1)
    {
        GPIOD->ODR ^= (1 << 12);       // toggle LED
        delay_ms(1000);
    }
}
📚 What You Learn
SysTick timer configuration in STM32
Bare-metal GPIO control using structs
Register-level embedded design pattern
Hardware delay generation without loops
Clean peripheral abstraction technique