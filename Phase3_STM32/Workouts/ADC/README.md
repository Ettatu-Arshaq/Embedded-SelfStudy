# 🌡️ STM32 ADC (Analog-to-Digital Conversion) – Basic Input Read

## 📌 Overview

This project demonstrates how to use **ADC1** on STM32F407 to read an **analog signal** from a GPIO pin (PA1).

👉 It converts real-world analog voltage (0–3.3V) into a **digital value (0–4095)**.

---

## 🎯 Objective

* Configure ADC in **bare-metal (register-level)**
* Read analog input from **PA1 (Channel 1)**
* Understand ADC conversion process
* Observe digital values using debugger

---

## ⚙️ ADC Working Principle

```text
Analog Voltage (0–3.3V)
        ↓
ADC Converter
        ↓
Digital Value (0–4095)
```

👉 12-bit resolution:

* 0V → 0
* 3.3V → 4095

---

## 🔌 Pin Configuration

| Pin | Function      |
| --- | ------------- |
| PA1 | ADC Channel 1 |

---

## ⚙️ Initialization Steps

### 🔹 Enable GPIOA Clock

```c
RCC_AHB1ENR |= (1 << 0);
```

---

### 🔹 Set Analog Mode

```c
GPIOA_MODER |= (3 << 2);
```

👉 Analog mode disables digital input/output

---

### 🔹 Enable ADC Clock

```c
RCC_APB2ENR |= (1 << 8);
```

---

### 🔹 Sampling Time

```c
ADC1_SMPR2 |= (3 << 3);
```

👉 56 cycles (stable reading)

---

### 🔹 Select Channel

```c
ADC1_SQR3 = 1;
```

👉 Channel 1 (PA1)

---

### 🔹 Enable ADC

```c
ADC1_CR2 |= (1 << 0);
```

---

## 🔄 ADC Read Function

```c
uint16_t ADC1_Read(void)
{
    ADC1_CR2 |= (1 << 30);          // Start conversion

    while (!(ADC1_SR & (1 << 1)));  // Wait for EOC

    return (uint16_t)ADC1_DR;       // Read result
}
```

---

## 🔁 Execution Flow

```text
Start Conversion
      ↓
ADC Sampling
      ↓
Conversion Complete (EOC)
      ↓
Read ADC_DR
      ↓
Get Digital Value
```

---

## 💡 Output Behavior

* `adc_value` changes based on input voltage
* Use debugger to monitor values

---

## 📊 Example Values

| Voltage | ADC Value |
| ------- | --------- |
| 0V      | 0         |
| 1.65V   | ~2048     |
| 3.3V    | 4095      |

---

## 🧠 Key Concepts

### 🔹 Resolution (12-bit)

* Range: 0–4095

---

### 🔹 Sampling Time

* Longer = more stable
* Shorter = faster

---

### 🔹 EOC (End Of Conversion)

```c
ADC1_SR & (1 << 1)
```

👉 Indicates conversion complete

---

### 🔹 Data Register (DR)

* Holds converted value

---

## ⚠️ Important Notes

* Pin **must be in analog mode**
* Do not use pull-up/down resistors
* ADC is sensitive to noise
* Add delay between readings

---

## 🛠️ Hardware Setup

* Potentiometer (recommended)
* Connect:

  * One end → 3.3V
  * Other end → GND
  * Middle → PA1

---

## 🚀 How to Run

1. Flash code
2. Rotate potentiometer
3. Watch `adc_value` in debugger

---

## 🧠 What You Learned

✔ ADC fundamentals
✔ Analog vs digital signals
✔ Register-level configuration
✔ Polling-based ADC read
✔ Sensor interfacing basics

---

## 🔥 Real-World Applications

* Temperature sensors
* Light sensors (LDR)
* Battery monitoring
* Joystick input
* Audio signals

---



---

## 🧑‍💻 Author

**Muhammad Arshaq**
