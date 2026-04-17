# ⚡ STM32 External Interrupt (EXTI) – Button Triggered LED

## 📌 Overview

This project demonstrates how to use **External Interrupt (EXTI)** on STM32.

👉 A button press on **PA0** triggers an interrupt and toggles an LED on **PD12**.

---

## 🎯 Objective

* Configure **GPIO input (PA0)**
* Setup **EXTI line 0**
* Enable **NVIC interrupt**
* Toggle LED using interrupt handler

---

## 🧠 What is EXTI?

👉 EXTI = External Interrupt/Event Controller

✔ Detects signal changes on GPIO
✔ Triggers interrupt instantly
✔ No CPU polling required

---

## ⚙️ System Architecture

```text id="6qk9y1"
Button (PA0)
     ↓
   EXTI0
     ↓
   NVIC
     ↓
Interrupt Handler
     ↓
Toggle LED (PD12)
```

---

## 🔁 Working Flow

```text id="3k8zbf"
Button Press (Rising Edge)
        ↓
EXTI detects event
        ↓
Interrupt triggered
        ↓
ISR executes
        ↓
LED toggles
```

---

## 🔌 Pin Configuration

| Pin  | Function       |
| ---- | -------------- |
| PA0  | Input (Button) |
| PD12 | Output (LED)   |

---

## ⚙️ Configuration Steps

---

### 🔹 1. Enable Clocks

```c id="9ps4z1"
RCC_AHB1ENR |= (1 << 0) | (1 << 3); // GPIOA + GPIOD
RCC_APB2ENR |= (1 << 14);           // SYSCFG
```

---

### 🔹 2. Configure PA0 as Input

```c id="7fxz2r"
GPIOA_MODER &= ~(3 << 0);
GPIOA_PUPDR &= ~(3 << 0);
```

---

### 🔹 3. Configure LED (PD12)

```c id="2kjq9n"
GPIOD_MODER &= ~(3 << 24);
GPIOD_MODER |=  (1 << 24);
```

---

### 🔹 4. Map EXTI Line to PA0

```c id="5cnr3d"
SYSCFG_EXTICR1 &= ~(0xF << 0);
```

👉 Connects EXTI0 → PA0

---

### 🔹 5. Configure EXTI Trigger

```c id="8x0l1m"
EXTI_IMR  |= (1 << 0);  // Unmask
EXTI_RTSR |= (1 << 0);  // Rising edge
EXTI_FTSR &= ~(1 << 0); // Disable falling
```

---

### 🔹 6. Enable NVIC Interrupt

```c id="z1v8hf"
NVIC_ISER0 |= (1 << 6);
```

👉 IRQ6 = EXTI0

---

## ⚡ Interrupt Handler

```c id="r8l3yt"
void EXTI0_IRQHandler(void)
{
    if (EXTI_PR & (1 << 0))
    {
        EXTI_PR |= (1 << 0);     // Clear flag
        GPIOD_ODR ^= (1 << 12);  // Toggle LED
    }
}
```

---

## 💡 Key Concept: Pending Register

```c id="3ok2d1"
EXTI_PR |= (1 << 0);
```

👉 Must clear interrupt flag manually
👉 Otherwise ISR keeps triggering

---

## 🔄 Behavior

* Button pressed → LED toggles
* No polling required
* CPU sleeps until interrupt

---

## 📈 Advantages

✔ Fast response
✔ Low CPU usage
✔ Event-driven design

---

## ⚠️ Important Notes

* Always clear **pending flag**
* Configure correct edge trigger
* Use pull-up/down for stable input

---

## 🛠️ Hardware Setup

* Button connected to PA0
* LED on PD12

👉 Optional:

* Add **pull-down resistor** for stability

---

## 🚀 How to Run

1. Flash code
2. Press button
3. LED toggles instantly

---

## 🧠 What You Learned

✔ Interrupt-based programming
✔ EXTI configuration
✔ NVIC basics
✔ Event-driven systems

---

## 🔥 Real-World Applications

* Button interfaces
* Motion detection
* Sensor triggers
* Wake-up events
* Embedded UI

---



## 🧑‍💻 Author

**Muhammad Arshaq**
