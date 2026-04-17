# STM32F4 Bare-Metal LED Blink (GPIOD Pin 12)

This project demonstrates a simple **bare-metal embedded system program** for the STM32F4 series microcontroller. It directly accesses hardware registers (without HAL/Standard Libraries) to toggle an LED connected to **GPIOD Pin 12**.

---

## 🚀 Features

- Direct register-level programming (no HAL / CMSIS drivers)
- GPIO configuration for output mode
- Simple software delay using NOP loop
- LED blinking example on STM32F4 Discovery-style boards

---

## 🛠️ Hardware Requirements

- STM32F4 series microcontroller (e.g., STM32F407)
- On-board LED connected to **PD12** (common on Discovery boards)
- Power supply / ST-Link for flashing

---

## ⚙️ How It Works

### 1. Enable GPIO Clock
The code enables clock for **GPIOD** using RCC register:
```c
RCC_AHB1ENR |= (1 << 3);
2. Configure Pin Mode

PD12 is configured as general-purpose output:

GPIOD_MODER &= ~(3 << (12 * 2));
GPIOD_MODER |=  (1 << (12 * 2));
3. Toggle LED

Inside an infinite loop, the output pin is toggled:

GPIOD_ODR ^= (1 << 12);
4. Delay

A simple software delay using NOP instructions:

for (uint32_t i = 0; i < (ms * 800); i++) __asm__("nop");
📌 Code Overview
#include <stdint.h>

#define PERIPH_BASE       0x40000000UL
#define AHB1PERIPH_OFFSET 0x00020000UL
#define AHB1PERIPH_BASE   (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define RCC_BASE          (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOD_BASE        (AHB1PERIPH_BASE + 0x0C00UL)

#define RCC_AHB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOD_MODER       (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR         (*(volatile uint32_t *)(GPIOD_BASE + 0x14))

static void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < (ms * 800); i++) __asm__("nop");
}

int main(void){
    RCC_AHB1ENR |= (1 << 3);          // Enable GPIOD clock
    GPIOD_MODER &= ~(3 << (12 * 2));  // Clear mode bits for PD12
    GPIOD_MODER |=  (1 << (12 * 2));  // Set PD12 as output

    while(1){
        GPIOD_ODR ^= (1 << 12);       // Toggle LED
        delay_ms(1000);
    }
}
📚 Learning Outcomes
Understanding STM32 memory-mapped registers
GPIO configuration at hardware level
RCC clock enabling mechanism
Basic embedded delay implementation
Bare-metal firmware structure
⚡ Future Improvements
Replace delay loop with SysTick timer
Use interrupt-based toggling
Expand to multiple GPIO pins
Add FreeRTOS support
📄 License

This project is open-source and free to use for learning purposes.

