# ⚡ STM32 System Clock Configuration (HSE + PLL → 168 MHz)

## 📌 Overview

This project demonstrates how to configure the STM32 system clock using:

* **HSE (External Crystal)**
* **PLL (Phase Locked Loop)**

👉 Final system clock: **168 MHz**

---

## 🎯 Objective

* Enable **external oscillator (HSE)**
* Configure **PLL for high-speed operation**
* Switch system clock to PLL
* Indicate active clock source using LEDs

---

## 🧠 Clock Architecture

```text id="6p2m6x"
HSI (16 MHz)  ─┐
               ├──> System Clock (SYSCLK)
HSE (8 MHz)   ─┘
        ↓
       PLL
        ↓
     168 MHz
```

---

## 🔁 Clock Flow

```text id="0u7w8k"
HSE → PLL → SYSCLK
```

---

## ⚙️ Step-by-Step Configuration

---

### 🔹 1. Enable HSE (External Clock)

```c id="j6g4pt"
RCC_CR |= (1 << 16);            // HSEON
while (!(RCC_CR & (1 << 17)));  // Wait HSERDY
```

👉 Wait until external crystal stabilizes

---

### 🔹 2. Configure PLL

```c id="g4k92l"
#define PLL_M 8
#define PLL_N 336
#define PLL_P 2
```

```c id="9hp6yf"
RCC_PLLCFGR = (PLL_M) |
              (PLL_N << 6) |
              (((PLL_P / 2) - 1) << 16) |
              (1 << 22); // HSE source
```

---

### 🔹 PLL Formula

```text id="r2kx4j"
VCO = (HSE / M) × N
SYSCLK = VCO / P
```

👉 With values:

* HSE = 8 MHz
* M = 8 → 1 MHz
* N = 336 → 336 MHz
* P = 2 → **168 MHz**

---

### 🔹 3. Flash Latency

```c id="gk9l0v"
FLASH_ACR |= (5 << 0);
```

👉 Required for high-speed operation

---

### 🔹 4. Enable PLL

```c id="xg6p8c"
RCC_CR |= (1 << 24);
while (!(RCC_CR & (1 << 25)));
```

---

### 🔹 5. Switch System Clock to PLL

```c id="zpxk7v"
RCC_CFGR &= ~(0x3);
RCC_CFGR |=  (0x2);
```

```c id="mn2s7c"
while (((RCC_CFGR >> 2) & 0x3) != 0x2);
```

👉 Ensures PLL is active

---

## 💡 Clock Source Detection

```c id="k7m4pc"
uint32_t clk_src = (RCC_CFGR >> 2) & 0x3;
```

---

## 💡 LED Indication

| Clock Source | LED  |
| ------------ | ---- |
| HSI          | PD12 |
| HSE          | PD13 |
| PLL          | PD14 |
| Error        | PD15 |

---

## 🔌 GPIO Setup

```c id="n2x7sj"
RCC_AHB1ENR |= (1 << 3);
GPIOD_MODER |= (0x15 << 24);
```

👉 PD12–PD14 → Output

---

## 🧪 Behavior

* System boots
* Switches to **168 MHz PLL**
* LED shows active clock

👉 Expected:

* **PD14 ON → PLL active**

---

## 📈 Why Use PLL?

✔ High performance
✔ Faster processing
✔ Required for advanced peripherals

---

## ⚠️ Important Notes

* Always set **Flash latency before switching clock**
* Wait for **ready flags (HSERDY, PLLRDY)**
* Incorrect config → system crash

---

## 🛠️ Hardware

* STM32F407 Discovery board
* External 8 MHz crystal (built-in)
* LEDs (PD12–PD15)

---

## 🚀 How to Run

1. Flash code
2. Observe LED:

   * PD14 ON → Success

---

## 🧠 What You Learned

✔ Clock tree basics
✔ HSE vs HSI
✔ PLL configuration
✔ System clock switching
✔ Hardware-level timing control

---

## 🔥 Real-World Importance

* CPU speed control
* Peripheral timing (UART, SPI, I2C)
* Power vs performance tradeoff

---


## 🧑‍💻 Author

**Muhammad Arshaq**
