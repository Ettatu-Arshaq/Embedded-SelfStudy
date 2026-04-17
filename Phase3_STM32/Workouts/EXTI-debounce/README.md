# 🧠 STM32 EXTI + SysTick (Interrupt-Based Button Debouncing)

## 📌 Overview

This project demonstrates a **robust button handling system** using:

* **EXTI (External Interrupt)** → Detect button press
* **SysTick Timer (1 ms)** → Handle debounce timing

👉 Fully **interrupt-driven**, no blocking delays, no polling.

---

## 🎯 Objective

* Eliminate **button bouncing problem**
* Use **interrupt + timer combination**
* Implement **non-blocking debounce logic**
* Toggle LED reliably on button press

---

## ⚠️ Problem: Button Bouncing

```text
Ideal Press:     ──────┐
                     └──────

Real Press:      ──┐┌─┐┌─┐┌─┐
                  └┘ └┘ └┘ └────
```

👉 Multiple unwanted triggers occur

---

## ✅ Solution Strategy

```text id="zj0l6y"
Button Press → EXTI Interrupt
              ↓
Disable EXTI
              ↓
Start Debounce Timer (SysTick)
              ↓
Wait 20 ms
              ↓
Re-enable EXTI
```

---

## 🧠 System Architecture

```text id="w9v3l1"
PA0 (Button)
     ↓
   EXTI0
     ↓
Disable Interrupt
     ↓
SysTick (1 ms)
     ↓
Debounce Logic
     ↓
Re-enable EXTI
     ↓
Toggle LED (PD12)
```

---

## 🔁 Execution Flow

```text id="7jtx7f"
EXTI Trigger
    ↓
Check debounce flag
    ↓
Disable EXTI
    ↓
Start countdown (20 ms)
    ↓
SysTick decrements counter
    ↓
Re-enable EXTI
```

---

## 🔑 Key Variables

```c
volatile uint32_t debounce_active;
volatile uint32_t debounce_counter;
```

| Variable         | Purpose                        |
| ---------------- | ------------------------------ |
| debounce_active  | Indicates debounce in progress |
| debounce_counter | Time left (ms)                 |

---

## ⚡ EXTI Interrupt Handler

```c
void EXTI0_IRQHandler(void)
{
    if (EXTI_PR & (1 << 0))
    {
        EXTI_PR |= (1 << 0);

        if (!debounce_active)
        {
            debounce_active = 1;
            debounce_counter = 20;

            EXTI_IMR &= ~(1 << 0);  // Disable EXTI

            GPIOD_ODR ^= (1 << 12);
        }
    }
}
```

---

## ⏱️ SysTick Handler (1 ms)

```c
void SysTick_Handler(void)
{
    if (debounce_active)
    {
        if (debounce_counter > 0)
            debounce_counter--;
        else
        {
            debounce_active = 0;
            EXTI_IMR |= (1 << 0);  // Re-enable EXTI
        }
    }
}
```

---

## ⚙️ SysTick Configuration

```c
SYST_RVR = 160000 - 1; // 1 ms @ 16 MHz
SYST_CVR = 0;
SYST_CSR = 7;          // Enable + Interrupt + CPU clock
```

---

## 💡 Behavior

* Press button → LED toggles once
* No multiple triggers
* System remains responsive

---

## 📈 Advantages

✔ Non-blocking design
✔ Accurate debounce timing
✔ Interrupt-driven system
✔ CPU efficient

---

## ⚠️ Important Notes

* EXTI disabled during debounce
* SysTick must run at correct frequency
* Variables must be `volatile`

---

## 🛠️ Hardware Setup

| Component | Connection |
| --------- | ---------- |
| Button    | PA0        |
| LED       | PD12       |

👉 Recommended:

* Add pull-down resistor

---

## 🚀 How to Run

1. Flash code
2. Press button
3. LED toggles **cleanly (no bounce)**

---

## 🧠 What You Learned

✔ Real-world debouncing technique
✔ Interrupt + timer synergy
✔ Event-driven embedded design
✔ Non-blocking systems

---

## 🔥 Why This Is Important

👉 This is how **professional firmware** handles inputs

Used in:

* Industrial buttons
* Keypads
* Embedded UI systems

---



## 🧑‍💻 Author

**Muhammad Arshaq**
