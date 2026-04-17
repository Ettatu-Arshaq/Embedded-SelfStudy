# 🌡️💡 STM32 Smart Control System (UART + PWM + Sensor Logic)

## 📌 Overview

This project implements a **smart embedded control system** on STM32F407 using:

* UART (USART2) for communication
* PWM (TIM2) for fan control
* GPIO for LED control
* Command-based input system

👉 The system simulates an **IoT-like controller**:

* Temperature controls **fan speed**
* Light controls **LED**
* UART commands override automation

---

## 🎯 Features

✅ UART Command Interface (115200 baud)
✅ PWM-based Fan Speed Control
✅ Automatic + Manual Modes
✅ LED Control based on Light Sensor
✅ Real-time Status Feedback
✅ String Parsing (Bare-metal)

---

## ⚙️ System Architecture

```text
UART (PC / Serial Monitor)
        ↓
Command Parser
        ↓
 ┌───────────────┬───────────────┐
 │               │               │
Fan Control   LED Control   Status System
(PWM)         (GPIO)        (UART Output)
```

---

## 🔌 Peripherals Used

| Peripheral | Purpose         |
| ---------- | --------------- |
| USART2     | Communication   |
| TIM2       | PWM generation  |
| GPIOA      | UART + PWM pins |
| GPIOD      | LED output      |

---

## ⚙️ PWM (Fan Control)

### 🔹 Timer Setup

```c id="q2g3lw"
TIM2_PSC = 16 - 1;
TIM2_ARR = 1000 - 1;
```

👉 1 MHz timer clock
👉 1 kHz PWM frequency

---

### 🔹 Duty Cycle Control

```c id="kqz5s9"
TIM2_CCR1 = duty * 10;
```

* Duty range: **0–100%**
* CCR1 range: **0–1000**

---

### 🔹 Fan Logic

```c id="b5q9cf"
if (temp < 500)
    duty = 0;
else
    duty = temp / 40;
```

👉 Higher temperature → higher fan speed
👉 Minimum duty = 20% (when active)

---

## 💡 LED Control Logic

```c id="rjuyc3"
if (light < 1000)
    LED_ON();
else
    LED_OFF();
```

👉 Dark → LED ON
👉 Bright → LED OFF

---

## 📡 UART Communication

### 🔹 Baud Rate

```c id="v2q1pm"
USART2_BRR = 0x8B;
```

👉 115200 baud @ 16 MHz

---

### 🔹 Supported Commands

| Command      | Function                  |
| ------------ | ------------------------- |
| `TEMP:XXXX`  | Set temperature           |
| `LIGHT:XXXX` | Set light level           |
| `FAN:XX`     | Manual fan speed (0–100%) |
| `LED:ON`     | Turn LED ON               |
| `LED:OFF`    | Turn LED OFF              |
| `AUTO`       | Enable auto mode          |
| `STATUS`     | Print system state        |

---

## 🧠 Command Parsing

### 🔹 Prefix Matching

```c id="s9wrhc"
startsWith(cmd, "TEMP:")
```

👉 Detects command type

---

### 🔹 Value Extraction

```c id="t9g2zr"
parse_value(&cmd[5]);
```

👉 Converts string → integer

---

## 🔁 System Flow

```text
Receive UART char
      ↓
Build command string
      ↓
Command complete (\n)
      ↓
Parse command
      ↓
Update system state
      ↓
Apply control (Fan + LED)
      ↓
Send response (if needed)
```

---

## 📊 Status Output Example

When `STATUS` command is sent:

```text
T:2500
L:800
F:62
```

* T → Temperature
* L → Light
* F → Fan duty (%)

---

## 🔄 Modes of Operation

### 🔹 AUTO Mode (default)

* Fan controlled by temperature
* LED controlled by light

---

### 🔹 MANUAL Mode

* Override using UART:

```text
FAN:70
LED:ON
```

---

### 🔹 Back to AUTO

```text
AUTO
```

---

## ⚠️ Important Notes

* Buffer overflow protection included
* Commands are **case-sensitive (partially handled)**
* PWM resolution = 1000 steps
* Blocking UART (no interrupts yet)

---

## 🛠️ Hardware Connections

| Pin  | Function         |
| ---- | ---------------- |
| PA2  | USART2 TX        |
| PA3  | USART2 RX        |
| PA0  | PWM Output (Fan) |
| PD12 | LED              |

---

## 🚀 How to Run

1. Flash code to STM32F407
2. Open Serial Monitor (115200 baud)
3. Send commands like:

```text
TEMP:2500
LIGHT:800
STATUS
```

---

## 🧠 What You Learned

✔ UART communication (TX/RX)
✔ PWM generation using timer
✔ Command parsing in C
✔ Embedded control logic
✔ Manual vs automatic system design
✔ Multi-peripheral integration

---

## 🔥 Real-World Mapping

| This Project | Real System          |
| ------------ | -------------------- |
| Temp input   | Temperature sensor   |
| Light input  | LDR sensor           |
| PWM Fan      | Cooling system       |
| LED          | Smart lighting       |
| UART         | IoT / Serial control |

---

## 📈 Next Steps

* UART interrupt (non-blocking)
* ADC integration (real sensors)
* FreeRTOS version (multi-tasking)
* LCD / OLED display
* WiFi (ESP8266 / ESP32)

---

## 🧑‍💻 Author

**Muhammad Arshaq**
