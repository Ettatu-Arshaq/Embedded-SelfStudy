# ⏱️ SysTick Timer + LED Patterns (STM32F407 Bare-Metal)

## 📌 Overview

This project demonstrates how to use the **SysTick timer** for millisecond delays and generate multiple **LED patterns** on the STM32F407 without using HAL or RTOS.

It showcases precise timing using interrupts and efficient delay handling.

---

## 🎯 Objective

* Learn **SysTick timer configuration**
* Generate **accurate millisecond delays**
* Implement **non-blocking delay logic**
* Control multiple LEDs with patterns

---

## ⚙️ How It Works

### 🔹 SysTick Timer Setup

```c
SYST_RVR = 16000 - 1;
SYST_CVR = 0;
SYST_CSR = (1 << 0) | (1 << 1) | (1 << 2);
```

* Reload value → 1 ms (assuming 16 MHz clock)
* Interrupt enabled
* Uses processor clock

---

### 🔹 Interrupt Handler

```c
void SysTick_Handler(void)
{
    msTicks++;
}
```

👉 Increments every **1 ms**

---

### 🔹 Delay Function

```c
while ((msTicks - start) < ms);
```

👉 Non-blocking style delay using tick counter

---

## 💡 LED Patterns

### 🔹 1. Running LED

```text
PD12 → PD13 → PD14 → PD15
```

👉 Sequential blinking

---

### 🔹 2. All LEDs Blink

```text
ALL ON → ALL OFF
```

👉 Synchronized blinking

---

### 🔹 3. Binary Counter

```text
0000 → 0001 → 0010 → ... → 1111
```

👉 LEDs act as a **4-bit counter**

---

## 🔁 System Flow

```text
SysTick Interrupt (1ms)
        ↓
    msTicks++
        ↓
   delay_ms()
        ↓
 LED Pattern Functions
        ↓
   GPIO Output (PD12–PD15)
```

---

## 🧠 Key Concepts

### 🔹 SysTick Timer

* Built-in Cortex-M timer
* Generates periodic interrupts
* Used for OS ticks or delays

---

### 🔹 Non-Blocking Delay

* CPU not fully stuck like `for` loop delay
* Can be extended to multitasking systems

---

### 🔹 Direct Register Access

```c
GPIOD->MODER
GPIOD->ODR
RCC->AHB1ENR
```

👉 Full control without HAL

---

## ⚠️ Important Notes

* Assumes **16 MHz system clock (HSI)**
* Delay accuracy depends on clock
* `msTicks` must be `volatile`
* ISR must be lightweight

---

## 🛠️ Hardware Used

* STM32F407 Discovery Board
* LEDs: PD12, PD13, PD14, PD15

---

## ⚙️ Software Used

* ARM GCC
* STM32CubeIDE / Keil

---

## 🚀 How to Run

1. Build project
2. Flash to STM32F407
3. Observe LED patterns:

   * Running LED
   * All blink
   * Binary counter

---

## 🧠 What You Learned

✔ SysTick configuration
✔ Interrupt handling
✔ Time-based logic
✔ GPIO control
✔ Bare-metal embedded design

---

## 📈 Next Steps

* Use SysTick with FreeRTOS
* Add button control to switch patterns
* Use external interrupts
* Optimize with low-power modes

---

## 🧑‍💻 Author

**Muhammad Arshaq**
