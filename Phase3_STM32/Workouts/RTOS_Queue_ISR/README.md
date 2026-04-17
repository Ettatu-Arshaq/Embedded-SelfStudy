# 📡 FreeRTOS Queue + UART Communication (STM32F407)

## 📌 Overview

This project demonstrates **inter-task communication using FreeRTOS queues**, where data is transmitted over **UART (USART2)**.

A producer task generates numbers and sends them through a queue, while a consumer task receives and prints them via UART.

---

## 🎯 Objective

* Learn **Queue-based communication**
* Send data between tasks safely
* Output data using **UART without printf**
* Understand real-time data flow

---

## ⚙️ How It Works

### 🔹 Task 1 (Producer)

* Generates an incrementing counter
* Sends value to queue every 500 ms

```c
count++;
xQueueSend(dataQueue, &count, portMAX_DELAY);
```

---

### 🔹 Task 2 (Consumer)

* Waits for data from queue
* Sends received value over UART

```c
xQueueReceive(dataQueue, &receivedData, portMAX_DELAY);
UART_SendNumber(receivedData);
```

---

## 📤 UART Output Example

```text
1
2
3
4
5
...
```

👉 Continuous counting printed via serial terminal

---

## 🧠 Architecture

```
[ Producer Task ]
        ↓
      Queue
        ↓
[ Consumer Task ]
        ↓
      UART TX
        ↓
 Serial Monitor
```

---

## 🛠️ Hardware Used

* STM32F407 Discovery Board
* USB to Serial (via USART2 PA2)

---

## ⚙️ Software Used

* FreeRTOS
* STM32CubeIDE
* ARM GCC

---

## 🔧 Key Functions Explained

### 🔹 Queue Creation

```c
dataQueue = xQueueCreate(5, sizeof(uint32_t));
```

* Holds 5 elements
* Each element is 32-bit

---

### 🔹 Sending Data

```c
xQueueSend(dataQueue, &count, portMAX_DELAY);
```

* Blocks if queue is full

---

### 🔹 Receiving Data

```c
xQueueReceive(dataQueue, &receivedData, portMAX_DELAY);
```

* Waits until data is available

---

### 🔹 UART Number Transmission

* Custom function converts integer → ASCII
* Avoids heavy `printf()`

---

## ⚠️ Notes

* Queue size = 5
* Both tasks have equal priority
* Blocking APIs ensure efficient CPU usage
* UART is polling-based (no interrupt used)

---

## 🚀 How to Run

1. Build project
2. Flash to STM32F407
3. Open serial terminal:

   * Baudrate: 115200
4. Observe incrementing numbers

---

## 🧠 Key Concepts Learned

* Producer–Consumer model
* Queue-based synchronization
* UART communication without stdio
* Blocking vs non-blocking APIs

---

## 📈 Possible Improvements

* Add mutex for UART (if multiple writers)
* Use interrupt-based UART
* Send structured data (structs)
* Add multiple producers

---

## 🧑‍💻 Author

**Muhammad Arshaq**
