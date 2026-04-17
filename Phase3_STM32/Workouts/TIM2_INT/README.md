# ⏲️ STM32 Timer Interrupt (TIM2) – LED Toggle (Bare-Metal)

## 📌 Overview

This project demonstrates how to use a **hardware timer (TIM2)** with interrupts to toggle an LED on STM32F407.

Unlike SysTick, this uses a **general-purpose timer peripheral**, giving more flexibility and precision.

---

## 🎯 Objective

* Learn **hardware timer (TIM2) configuration**
* Use **interrupts for periodic events**
* Understand **prescaler and auto-reload**
* Toggle LED using ISR (no polling)

---

## ⚙️ How It Works

### 🔹 Timer Configuration

```c
TIM2_PSC = 16 - 1;
TIM2_ARR = 1000 - 1;
```

* Prescaler → 16 MHz / 16 = **1 MHz (1 µs tick)**
* Auto-reload → 1000 → **1 ms overflow**

---

### 🔹 Enable Interrupt

```c
TIM2_DIER |= 1;
```

👉 Enables **Update Interrupt (UIE)**

---

### 🔹 Start Timer

```c
TIM2_CR1 |= 1;
```

👉 Counter starts running

---

### 🔹 NVIC Configuration

```c
NVIC_ISER0 |= (1 << 28);
```

👉 Enables TIM2 interrupt in NVIC

---

### 🔹 Interrupt Handler

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

👉 Executes every **1 ms**
👉 Toggles LED (PD12)

---

## 🔁 System Flow

```text
TIM2 Counter
    ↓
Overflow (1 ms)
    ↓
Interrupt Trigger
    ↓
TIM2_IRQHandler()
    ↓
LED Toggle (PD12)
```

---

## 💡 Behavior

* LED toggles every **1 ms interrupt**
* Very fast blinking (almost invisible)
* Fully interrupt-driven (no delay loop)

---

## 🧠 Key Concepts

### 🔹 Prescaler (PSC)

* Divides input clock
* Controls timer speed

---

### 🔹 Auto Reload Register (ARR)

* Defines when timer overflows
* Sets interrupt period

---

### 🔹 Update Interrupt Flag (UIF)

```c
TIM2_SR & 1
```

* Set when timer overflows
* Must be cleared manually

---

### 🔹 NVIC

* Enables interrupt at CPU level

---

## ⚠️ Important Notes

* LED toggles too fast → increase ARR for visible blinking
* Always clear interrupt flag (`UIF`)
* Timer runs independently of CPU
* ISR must be short

---

## 🛠️ Hardware Used

* STM32F407 Discovery
* LED (PD12)

---

## ⚙️ Software Used

* ARM GCC
* STM32CubeIDE / Keil

---

## 🚀 How to Run

1. Build project
2. Flash to STM32F407
3. Observe LED (very fast blinking)

---

## 🔧 Suggested Improvement

To make LED visible:

```c
TIM2_ARR = 500000 - 1; // ~500ms
```

---

## 🧠 What You Learned

✔ Hardware timers
✔ Interrupt-driven design
✔ NVIC configuration
✔ Precise timing control
✔ Bare-metal peripheral handling

---

## 🔥 SysTick vs TIM2

| Feature     | SysTick    | TIM2              |
| ----------- | ---------- | ----------------- |
| Type        | Core timer | Peripheral timer  |
| Flexibility | Limited    | High              |
| Channels    | 1          | Multiple          |
| Use case    | OS tick    | Real applications |

---

## 📈 Next Steps

* PWM using timer
* Input capture (measure signal)
* Output compare
* Timer + DMA
* Timer + FreeRTOS integration

---

## 🧑‍💻 Author

**Muhammad Arshaq**
