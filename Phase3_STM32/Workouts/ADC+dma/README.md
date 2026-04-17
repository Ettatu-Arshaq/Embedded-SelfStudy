# ⚡ STM32 ADC + DMA (Continuous Analog Sampling)

## 📌 Overview

This project demonstrates how to use **ADC with DMA** on STM32F407 to continuously read analog data **without CPU involvement**.

👉 Instead of reading one value at a time, ADC fills a **memory buffer automatically** using DMA.

---

## 🎯 Objective

* Use **DMA with ADC** for efficient data transfer
* Enable **continuous sampling**
* Store multiple ADC values in a buffer
* Learn high-performance embedded design

---

## ⚙️ Why ADC + DMA?

### ❌ Without DMA (Polling)

* CPU waits for ADC
* Slow and inefficient

---

### ✅ With DMA

* ADC → Memory directly
* CPU is free
* Ideal for real-time systems

---

## 🧠 System Architecture

```text
Analog Input (PA1)
        ↓
      ADC1
        ↓
      DMA2
        ↓
Memory Buffer (adc_buffer[])
        ↓
CPU (optional processing)
```

---

## 🔁 Data Flow

```text
ADC Conversion Complete
        ↓
DMA transfers data
        ↓
Stored in adc_buffer[]
        ↓
Repeat (circular mode)
```

---

## 🔌 Configuration Steps

### 🔹 Enable Clocks

```c
RCC_AHB1ENR |= (1 << 0);   // GPIOA
RCC_AHB1ENR |= (1 << 22);  // DMA2
RCC_APB2ENR |= (1 << 8);   // ADC1
```

---

### 🔹 GPIO Setup (Analog Mode)

```c
GPIOA_MODER |= (3 << 2);
```

👉 PA1 → Analog input

---

## ⚡ DMA Configuration

### 🔹 Peripheral & Memory Address

```c
DMA2_S0PAR  = (uint32_t)&ADC1_DR;
DMA2_S0M0AR = (uint32_t)adc_buffer;
```

---

### 🔹 Transfer Size

```c
DMA2_S0NDTR = ADC_BUFFER_SIZE;
```

---

### 🔹 Mode Setup

```c
DMA2_S0CR |= (1 << 8);   // Circular mode
DMA2_S0CR |= (1 << 10);  // Memory increment
DMA2_S0CR |= (1 << 13);  // Memory = 16-bit
DMA2_S0CR |= (1 << 11);  // Peripheral = 16-bit
```

---

### 🔹 Enable DMA

```c
DMA2_S0CR |= (1 << 0);
```

---

## ⚙️ ADC Configuration

```c
ADC1_SMPR2 |= (3 << 3);  // Sampling time
ADC1_SQR3 = 1;           // Channel 1
```

---

### 🔹 Enable DMA in ADC

```c
ADC1_CR2 |= (1 << 8);
```

---

### 🔹 Continuous Mode

```c
ADC1_CR2 |= (1 << 1);
```

👉 ADC keeps converting automatically

---

### 🔹 Start ADC

```c
ADC1_CR2 |= (1 << 0);   // Enable
ADC1_CR2 |= (1 << 30);  // Start conversion
```

---

## 📊 Buffer

```c
#define ADC_BUFFER_SIZE 10
uint16_t adc_buffer[ADC_BUFFER_SIZE];
```

👉 Holds last **10 ADC samples**
👉 Continuously updated

---

## 💡 Behavior

* ADC runs continuously
* DMA fills buffer in loop
* No CPU intervention needed

---

## 🔄 Circular Mode Explained

```text
adc_buffer[0] → adc_buffer[9]
        ↓
Wrap around → overwrite old data
```

👉 Always contains latest readings

---

## 📈 Advantages

✔ Zero CPU overhead
✔ High-speed sampling
✔ Efficient memory usage
✔ Real-time capable

---

## ⚠️ Important Notes

* Buffer is continuously overwritten
* No interrupt used here (yet)
* Ensure correct data size (16-bit)
* ADC + DMA must match configuration

---

## 🛠️ Hardware Setup

* Potentiometer connected to PA1
* 3.3V ↔ GND ↔ Signal → PA1

---

## 🚀 How to Run

1. Flash code
2. Run debugger
3. Watch `adc_buffer[]`

👉 Values update automatically

---

## 🧠 What You Learned

✔ DMA basics
✔ Peripheral-to-memory transfer
✔ Circular buffering
✔ Continuous ADC sampling
✔ High-performance embedded design

---

## 🔥 Real-World Applications

* Audio signal processing
* Sensor arrays
* Oscilloscope-like systems
* Data logging
* IoT real-time monitoring

---

## 📈 Next Steps (VERY IMPORTANT)

### 1️⃣ DMA Interrupt

* Process buffer when full

---

### 2️⃣ Moving Average Filter

* Smooth noisy signals

---

### 3️⃣ Multi-Channel ADC

* Read multiple sensors

---

### 4️⃣ ADC + DMA + UART

* Stream live data to PC

---

## 🧑‍💻 Author

**Muhammad Arshaq**
