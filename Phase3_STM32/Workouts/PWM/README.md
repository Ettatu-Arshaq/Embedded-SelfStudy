# STM32F4 Bare-Metal PWM Generation using TIM4 (PD12)

This project demonstrates **hardware PWM generation on STM32F4** using **TIM4 timer + alternate function GPIO configuration**, written in pure **bare-metal register-level C (no HAL/CMSIS)**.

---

## 🚀 Features
- Bare-metal STM32 timer programming
- PWM generation using TIM4 (Channel 1)
- GPIO alternate function configuration
- Hardware-driven PWM (no CPU load after setup)
- Fixed frequency + adjustable duty cycle

---

## 🛠️ Hardware Requirements
- STM32F4 series microcontroller (e.g., STM32F407 Discovery board)
- Output pin: **PD12 (TIM4_CH1)**
- LED or oscilloscope for PWM observation
- ST-Link programmer/debugger

---

## ⚙️ Working Principle

### 1. GPIO Alternate Function Setup
PD12 is configured into **Alternate Function mode (AF)** and mapped to **TIM4 (AF2)**.

### 2. Timer Clock Enable
TIM4 peripheral clock is enabled via RCC APB1 bus.

### 3. PWM Configuration
- Prescaler divides clock to **1 MHz**
- Auto-reload sets PWM frequency to **1 kHz**
- PWM mode 1 is selected

### 4. Duty Cycle Control
CCR1 register controls duty cycle:
- Example: `CCR1 = 100` → low duty cycle PWM

### 5. Hardware PWM Output
Once started, TIM4 generates PWM independently without CPU intervention.

---

## 💻 Code

```c
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
    /* Enable GPIOD clock */
    RCC_AHB1ENR |= (1 << 3);

    /* Set PD12 to Alternate Function mode */
    GPIOD_MODER &= ~(3 << (12 * 2));
    GPIOD_MODER |=  (2 << (12 * 2));

    /* Select AF2 (TIM4) for PD12 */
    GPIOD_AFRH &= ~(0xF << ((12 - 8) * 4));
    GPIOD_AFRH |=  (2 << ((12 - 8) * 4));

    /* Enable TIM4 clock */
    RCC_APB1ENR |= (1 << 2);

    /* Configure timer */
    TIM4_PSC = 15;        // 16 MHz / 16 = 1 MHz
    TIM4_ARR = 1000 - 1;  // 1 kHz PWM frequency

    /* PWM mode 1 */
    TIM4_CCMR1 |= (6 << 4);
    TIM4_CCMR1 |= (1 << 3);

    /* Enable output channel */
    TIM4_CCER |= 1;

    /* Duty cycle */
    TIM4_CCR1 = 100;

    /* Enable auto-reload preload */
    TIM4_CR1 |= (1 << 7);

    /* Start timer */
    TIM4_CR1 |= 1;

    while (1)
    {
        // PWM runs in hardware
    }
}
📚 What You Learn
STM32 timer architecture (TIM4)
PWM generation without interrupts
Alternate function GPIO mapping
Prescaler and auto-reload concept