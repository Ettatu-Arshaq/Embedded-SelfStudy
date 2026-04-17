# ⚡ STM32 Smart Control System (UART Interrupt + PWM + Automation)

## 📌 Overview

This project is an **advanced embedded system** built on STM32F407 featuring:

* **Interrupt-driven UART (USART2)**
* **PWM fan control (TIM2)**
* **Automatic + Manual control logic**
* **LED control based on light input**

🚀 This version upgrades your previous design by replacing **blocking UART** with **interrupt-based communication**, making the system more efficient and responsive.

---

## 🎯 Key Improvements

✅ Non-blocking UART using interrupts
✅ ISR-based data reception
✅ Main loop handles logic (clean design)
✅ Better CPU utilization
✅ Scalable architecture (RTOS-ready)

---

## ⚙️ System Architecture

```text
UART RX Interrupt (ISR)
        ↓
Command Buffer
        ↓
Main Loop (Processing)
        ↓
 ┌───────────────┬───────────────┐
 │               │               │
Fan Control   LED Control   Status Output
(PWM)         (GPIO)        (UART TX)
```

---

## 🔁 System Flow

```text
User sends command (UART)
        ↓
USART2_IRQHandler()
        ↓
Store characters in buffer
        ↓
Command complete (\n)
        ↓
Set flag → command_ready = 1
        ↓
Main loop processes command
```

---

## ⚡ Interrupt-Based UART

### 🔹 Enable RX Interrupt

```c
USART2_CR1 |= (1 << 5); // RXNEIE
```

---

### 🔹 NVIC Enable

```c
NVIC_ISER1 |= (1 << 6); // USART2 IRQ
```

---

### 🔹 ISR (Core Logic)

```c
void USART2_IRQHandler(void)
{
    if (USART2_SR & (1 << 5))
    {
        char c = USART2_DR;

        if (c == '\n' || c == '\r')
        {
            rx_buffer[index] = '\0';
            command_ready = 1;
            index = 0;
        }
        else
        {
            if (index < BUFFER_SIZE - 1)
                rx_buffer[index++] = c;
        }
    }
}
```

### 💡 Key Idea:

👉 ISR only **collects data**
👉 Main loop does **processing**

---

## 🧠 Why This Design is Powerful

### ❌ Old (Blocking UART)

```c
char c = UART2_ReadChar(); // waits forever
```

* CPU stuck waiting
* No multitasking

---

### ✅ New (Interrupt-based)

* CPU is free
* Works like mini-RTOS
* Event-driven design

---

## ⚙️ PWM (Fan Control)

```c
TIM2_PSC = 16 - 1;
TIM2_ARR = 1000 - 1;
```

👉 1 kHz PWM

```c
TIM2_CCR1 = duty * 10;
```

👉 Duty cycle control (0–100%)

---

## 🌡️ Fan Logic

```c
if (fan_manual != -1)
    FAN_SetSpeed(fan_manual);
```

### Auto Mode:

* Temp < 500 → OFF
* Temp increases → speed increases
* Min speed = 20%

---

## 💡 LED Logic

```c
if (light < 1000)
    LED_ON();
else
    LED_OFF();
```

---

## 📡 Supported Commands

| Command      | Description           |
| ------------ | --------------------- |
| `TEMP:XXXX`  | Set temperature       |
| `LIGHT:XXXX` | Set light level       |
| `FAN:XX`     | Manual fan speed      |
| `LED:ON`     | Turn LED ON           |
| `LED:OFF`    | Turn LED OFF          |
| `AUTO`       | Enable automatic mode |
| `STATUS`     | Print system state    |

---

## 📊 Status Output

```text
T:2500
L:800
F:62
```

---

## 🔐 Safety Features

* Buffer overflow protection
* ISR kept minimal
* Flag-based synchronization
* Manual override support

---

## 🛠️ Hardware Mapping

| Pin  | Function  |
| ---- | --------- |
| PA2  | USART2 TX |
| PA3  | USART2 RX |
| PA0  | PWM (Fan) |
| PD12 | LED       |

---

## 🚀 How to Run

1. Flash code to STM32F407
2. Open Serial Monitor (115200 baud)
3. Send commands:

```text
TEMP:3000
LIGHT:500
STATUS
```

---

## 🧠 What You Learned

✔ Interrupt-driven UART
✔ ISR vs Main loop separation
✔ Event-driven embedded design
✔ PWM + control logic integration
✔ Scalable architecture

---

## 🔥 Embedded Design Pattern

This project follows a **professional pattern**:

👉 ISR = Event Capture
👉 Main Loop = Processing Engine

---

## 📈 Next Steps (VERY IMPORTANT)

🚀 Convert this into:

### 1️⃣ FreeRTOS Version

* UART Task
* Control Task
* PWM Task

---

### 2️⃣ Add ADC

* Real temperature sensor
* Real LDR input

---

### 3️⃣ Advanced Features

* DMA for UART
* LCD display
* WiFi module (ESP8266)

---

## 🧑‍💻 Author

**Muhammad Arshaq**
