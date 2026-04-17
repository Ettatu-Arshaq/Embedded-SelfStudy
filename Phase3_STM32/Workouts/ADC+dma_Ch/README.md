# 🔥 STM32 ADC + DMA (Multi-Channel Scanning)

## 📌 Overview

This project demonstrates how to read **multiple analog channels** using **ADC + DMA + Scan Mode** on STM32.

👉 The ADC automatically scans multiple inputs and DMA stores results in memory — **fully autonomous system**.

---

## 🎯 Objective

* Read **multiple analog inputs (PA1, PA2, PA3)**
* Use **ADC Scan Mode**
* Transfer data using **DMA (circular mode)**
* Store readings in an array

---

## 🧠 System Architecture

```text
PA1 ─┐
PA2 ─┼──> ADC1 (Scan Mode)
PA3 ─┘        ↓
             DMA2
              ↓
     adc_buffer[3]
```

---

## 🔁 Working Flow

```text
CH1 → CH2 → CH3
 ↓     ↓     ↓
DMA writes sequentially
 ↓
adc_buffer[0..2]
 ↓
Repeat (circular)
```

---

## 🔌 Channel Mapping

| Buffer Index  | Pin | Channel |
| ------------- | --- | ------- |
| adc_buffer[0] | PA1 | CH1     |
| adc_buffer[1] | PA2 | CH2     |
| adc_buffer[2] | PA3 | CH3     |

---

## ⚙️ Configuration Breakdown

---

### 🔹 Enable Clocks

```c
RCC_AHB1ENR |= (1 << 0);   // GPIOA
RCC_AHB1ENR |= (1 << 22);  // DMA2
RCC_APB2ENR |= (1 << 8);   // ADC1
```

---

### 🔹 GPIO Analog Mode

```c
GPIOA_MODER |= (3 << 2);   // PA1
GPIOA_MODER |= (3 << 4);   // PA2
GPIOA_MODER |= (3 << 6);   // PA3
```

---

## ⚡ DMA Setup

```c
DMA2_S0PAR  = (uint32_t)&ADC1_DR;
DMA2_S0M0AR = (uint32_t)adc_buffer;
DMA2_S0NDTR = NUM_CHANNELS;
```

---

### 🔹 DMA Features

```c
DMA2_S0CR |= (1 << 8);   // Circular mode
DMA2_S0CR |= (1 << 10);  // Memory increment
DMA2_S0CR |= (1 << 13);  // Memory size = 16-bit
DMA2_S0CR |= (1 << 11);  // Peripheral size = 16-bit
```

---

## ⚙️ ADC Configuration

---

### 🔹 Scan Mode

```c
ADC1_CR1 |= (1 << 8);
```

👉 Enables multi-channel scanning

---

### 🔹 Continuous Mode + DMA

```c
ADC1_CR2 |= (1 << 1);   // Continuous
ADC1_CR2 |= (1 << 8);   // DMA enable
```

---

### 🔹 Sampling Time

```c
ADC1_SMPR2 |= (3 << 3);   // CH1
ADC1_SMPR2 |= (3 << 6);   // CH2
ADC1_SMPR2 |= (3 << 9);   // CH3
```

---

### 🔹 Sequence Length

```c
ADC1_SQR1 |= ((NUM_CHANNELS - 1) << 20);
```

👉 3 conversions per cycle

---

### 🔹 Channel Order

```c
ADC1_SQR3 |= (1 << 0);   // 1st → CH1
ADC1_SQR3 |= (2 << 5);   // 2nd → CH2
ADC1_SQR3 |= (3 << 10);  // 3rd → CH3
```

---

### 🔹 Start ADC

```c
ADC1_CR2 |= (1 << 0);   // ON
ADC1_CR2 |= (1 << 30);  // Start
```

---

## 📊 Buffer Behavior

```c
uint16_t adc_buffer[3];
```

* Continuously updated
* Always contains **latest readings**
* No CPU polling needed

---

## 🔄 Circular Mode Visualization

```text
Cycle 1: [CH1][CH2][CH3]
Cycle 2: overwrite again
Cycle 3: overwrite again
...
```

---

## 💡 Key Concepts

---

### 🔹 Scan Mode

ADC reads multiple channels automatically

---

### 🔹 DMA Circular Mode

* Continuous data flow
* No restart needed

---

### 🔹 Sequence Registers

* SQR1 → number of channels
* SQR3 → order

---

## 📈 Advantages

✔ Read multiple sensors simultaneously
✔ Zero CPU overhead
✔ Scalable system design
✔ Real-time data acquisition

---

## ⚠️ Important Notes

* Order in SQR3 = buffer order
* Buffer updates very fast → debugger may lag
* All channels must be analog mode
* Ensure correct sampling time

---

## 🛠️ Hardware Setup

Use 3 sensors or potentiometers:

| Pin | Connection |
| --- | ---------- |
| PA1 | Sensor 1   |
| PA2 | Sensor 2   |
| PA3 | Sensor 3   |

---

## 🚀 How to Run

1. Flash code
2. Open debugger
3. Watch:

```c
adc_buffer[0]
adc_buffer[1]
adc_buffer[2]
```

---

## 🧠 What You Learned

✔ Multi-channel ADC
✔ Scan mode operation
✔ DMA multi-transfer
✔ Embedded data pipelines
✔ Real-time sensor systems

---

## 🔥 Real-World Applications

* Multi-sensor IoT nodes
* Robotics (distance, light, temp)
* Industrial monitoring
* Smart home systems
* Data acquisition systems

---

## 🚀 Next Level (VERY IMPORTANT)

### 1️⃣ Add DMA Interrupt

Process data when buffer full

---

### 2️⃣ Sensor Fusion

Combine multiple sensor inputs

---

### 3️⃣ ADC → PWM Control

Control motors / LEDs

---

### 4️⃣ Stream via UART

Live sensor dashboard

---

### 5️⃣ Move to RTOS

Separate tasks for:

* ADC
* Processing
* Communication

---

## 🧑‍💻 Author

**Muhammad Arshaq**
