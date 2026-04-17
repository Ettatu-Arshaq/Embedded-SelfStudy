# 🕒 STM32 Clock Source Detection (Bare-Metal)

## 📌 Overview

This project demonstrates how to **read and identify the system clock source** of an STM32 microcontroller using direct register access.

It checks whether the MCU is running on:

* Internal oscillator (HSI)
* External oscillator (HSE)
* Phase-Locked Loop (PLL)

---

## 🎯 Objective

* Understand **RCC (Reset and Clock Control)**
* Learn how to read **hardware registers**
* Identify active **system clock source**
* Practice **bare-metal programming (no HAL/RTOS)**

---

## ⚙️ How It Works

### 🔹 Step 1: Access RCC Register

```c
#define RCC_CFGR (*(volatile uint32_t*)(RCC_BASE + 0x08))
```

👉 This register holds system clock configuration

---

### 🔹 Step 2: Extract Clock Source Bits

```c
uint32_t clk_src = (RCC_CFGR >> 2) & 0x3;
```

👉 Bits **[3:2] = SWS (System Clock Switch Status)**

---

### 🔹 Step 3: Interpret Value

```c
00 → HSI (Internal RC oscillator)
01 → HSE (External crystal)
10 → PLL (Phase-Locked Loop)
```

---

## 🧠 Register Breakdown

| Bits  | Name | Description                |
| ----- | ---- | -------------------------- |
| [3:2] | SWS  | System clock source status |
| 00    | HSI  | Internal 16 MHz clock      |
| 01    | HSE  | External crystal           |
| 10    | PLL  | PLL output                 |

---

## 💡 Behavior

* Code reads current clock source
* No output (debug via debugger/watch window)
* Useful for **low-level system verification**

---

## 🔍 Example Use Case

* Verify clock configuration after boot
* Debug PLL setup issues
* Ensure correct clock before peripherals init

---

## 🛠️ Hardware Used

* STM32F407 Discovery Board

---

## ⚙️ Software Used

* ARM GCC
* STM32CubeIDE / Keil / OpenOCD

---

## 🚀 How to Test

1. Build and flash code
2. Open debugger
3. Inspect variable:

```c
clk_src
```

---

## 🧠 Expected Values

| Value | Meaning |
| ----- | ------- |
| 0     | HSI     |
| 1     | HSE     |
| 2     | PLL     |

---

## ⚠️ Notes

* Default after reset → **HSI (0)**
* No peripheral initialization required
* Pure register-level programming

---

## 📈 Next Steps

* Switch clock source manually
* Configure PLL for higher frequency
* Output clock to MCO pin
* Measure clock using oscilloscope

---

## 🧑‍💻 Author

**Muhammad Arshaq**
