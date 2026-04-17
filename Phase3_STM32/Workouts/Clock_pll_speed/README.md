# ⏱️ STM32 SysTick Timer (Precise Delay with PLL @ 168 MHz)

## 📌 Overview

This project demonstrates how to use the **SysTick Timer** to generate accurate **millisecond delays** based on the system clock.

👉 Combined with **PLL (168 MHz)** for precise timing.

---

## 🎯 Objective

* Configure **SysTick timer**
* Generate **accurate millisecond delays**
* Blink LED using precise timing
* Understand core timer inside Cortex-M

---

## 🧠 What is SysTick?

👉 SysTick is a **built-in timer inside ARM Cortex-M core**

✔ No peripheral clock needed
✔ Runs directly from CPU clock
✔ Ideal for delays & RTOS

---

## ⚙️ SysTick Registers

| Register | Purpose          |
| -------- | ---------------- |
| SYST_CSR | Control & status |
| SYST_RVR | Reload value     |
| SYST_CVR | Current value    |

---

## 🔁 Working Principle

```text id="lq6d5k"
Load Value → Count Down → Reach 0
        ↓
COUNTFLAG = 1
        ↓
Repeat
```

---

## ⏱️ Delay Function

```c id="7ycfqk"
void SysTick_Delay_ms(uint32_t ms, uint32_t cpu_freq_mhz)
{
    SYST_RVR = (cpu_freq_mhz * 1000) - 1;
    SYST_CVR = 0;
    SYST_CSR = 5;

    for (uint32_t i = 0; i < ms; i++)
    {
        while (!(SYST_CSR & (1 << 16)));
    }

    SYST_CSR = 0;
}
```

---

## 💡 How It Works

👉 Example for **168 MHz**

```text id="1y6j9q"
1 ms = 168,000 cycles
```

So:

```c id="m5w3qp"
SYST_RVR = 168000 - 1;
```

---

## ⚙️ Clock Setup (PLL)

* HSE = 8 MHz
* PLL → **168 MHz system clock**

---

## 🔁 Main Loop

```c id="c9h8ab"
while (1) {
    GPIOD_ODR ^= (1 << 12);
    SysTick_Delay_ms(500, 168);
}
```

👉 LED blinks every **500 ms**

---

## 🔌 Hardware

* STM32F407 Discovery
* LED → PD12

---

## 💡 Output Behavior

* LED toggles ON/OFF
* Accurate timing using SysTick

---

## 📊 Timing Examples

| Delay  | Value         |
| ------ | ------------- |
| 1 ms   | 168000 cycles |
| 100 ms | 100 loops     |
| 500 ms | 500 loops     |

---

## ⚠️ Important Notes

* Max reload = **24-bit (16,777,215)**
* Must match CPU frequency
* Blocking delay (CPU waits)

---

## 🧠 Key Concepts

---

### 🔹 COUNTFLAG

```c id="h2z4kj"
SYST_CSR & (1 << 16)
```

👉 Set when timer reaches 0

---

### 🔹 Clock Source

```c id="v3pl0m"
SYST_CSR = 5;
```

* Bit 2 → CPU clock
* Bit 0 → Enable

---

## 📈 Advantages

✔ Accurate timing
✔ Simple to use
✔ Core-level (always available)

---

## ❌ Limitations

* Blocking delay
* Not efficient for multitasking

---

## 🚀 Real-World Use

* RTOS tick timer
* Delay functions
* Time measurement
* Scheduling

---

## 🔥 What You Learned

✔ SysTick internals
✔ CPU-based timing
✔ Delay calculation
✔ Clock-dependent timing

---



## 🧑‍💻 Author

**Muhammad Arshaq**
