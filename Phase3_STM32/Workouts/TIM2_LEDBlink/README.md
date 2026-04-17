# ⏲️ STM32 TIM2 Interrupt – 500ms LED Blink (Accurate Timer Setup)

## 📌 Overview

This project demonstrates a **precise hardware timer interrupt** using **TIM2** on STM32F407 to blink an LED every **500 ms**.

This version improves timing accuracy by correctly configuring the timer based on an **84 MHz system clock**.

---

## 🎯 Objective

* Configure **TIM2 with correct clock scaling**
* Generate **accurate 500 ms interrupt**
* Toggle LED using **interrupt service routine (ISR)**
* Understand real-world timer calculations

---

## ⚙️ Timer Calculation (Important!)

### 🔹 System Clock

* STM32F407 runs at **84 MHz** (default with PLL)

---

### 🔹 Prescaler

```c
TIM2_PSC = 8399;
```

👉 84 MHz / (8399 + 1) = **10 kHz**

👉 Timer tick = **0.1 ms (100 µs)**

---

### 🔹 Auto Reload

```c
TIM2_ARR = 4999;
```

👉 5000 ticks × 0.1 ms = **500 ms**

---

✅ Final Result:
**Interrupt every 500 ms**

---

## 🔁 Flow of Execution

```text
TIM2 Clock (84 MHz)
      ↓
Prescaler → 10 kHz tick
      ↓
Counter counts to 5000
      ↓
Overflow (500 ms)
      ↓
Interrupt Trigger
      ↓
TIM2_IRQHandler()
      ↓
LED Toggle (PD12)
```

---

## 💡 Code Breakdown

### 🔹 Enable GPIO

```c
RCC_AHB1ENR |= (1 << 3);
```

👉 Enables clock for GPIOD

---

### 🔹 Configure LED Pin

```c
GPIOD_MODER |= (1 << (12 * 2));
```

👉 PD12 set as output

---

### 🔹 Enable Timer

```c
RCC_APB1ENR |= (1 << 0);
```

👉 Enables TIM2 peripheral

---

### 🔹 Enable Interrupt

```c
TIM2_DIER |= 1;
```

👉 Update interrupt enabled (UIE)

---

### 🔹 NVIC Setup

```c
NVIC_ISER0 |= (1 << 28);
```

👉 TIM2 interrupt enabled at CPU level

---

### 🔹 Start Timer

```c
TIM2_CR1 |= 1;
```

👉 Counter starts running

---

## 🔔 Interrupt Handler

```c
void TIM2_IRQHandler(void)
{
    if (TIM2_SR & 1)
    {
        TIM2_SR &= ~1;
        GPIOD_ODR ^= (1 << 12);
    }
}
```

### ✔ What happens:

* Check interrupt flag (UIF)
* Clear flag (VERY IMPORTANT)
* Toggle LED

---

## 💡 Output Behavior

* LED toggles every **500 ms**
* Full ON-OFF cycle = **1 second**
* Clearly visible blinking

---

## 🧠 Key Concepts

### 🔹 TIM2_CNT

* Holds current counter value
* Reset to 0 before starting

---

### 🔹 TIM2_PSC (Prescaler)

* Slows down clock input

---

### 🔹 TIM2_ARR (Auto Reload)

* Defines interrupt period

---

### 🔹 TIM2_SR (Status Register)

* UIF flag indicates overflow

---

### 🔹 NVIC

* Enables interrupt handling in CPU

---

## ⚠️ Common Mistakes

❌ Forgetting to clear UIF → continuous interrupt
❌ Wrong clock assumption (16 MHz vs 84 MHz)
❌ Not enabling NVIC
❌ Incorrect prescaler math

---

## 🛠️ Hardware

* STM32F407 Discovery board
* LED on PD12

---

## 🚀 How to Run

1. Build project
2. Flash to board
3. Observe LED blinking every 0.5 sec

---

## 🔥 Comparison (Old vs This)

| Feature          | Previous Code | This Code       |
| ---------------- | ------------- | --------------- |
| Clock assumption | 16 MHz        | 84 MHz ✅        |
| Accuracy         | Low           | High ✅          |
| Blink visibility | Very fast     | Human-visible ✅ |

---

## 📈 Next Steps

* PWM using TIM (LED brightness control)
* Input Capture (measure frequency)
* Output Compare
* Timer + DMA
* Multi-channel timers

---

## 🧑‍💻 Author

**Muhammad Arshaq**
