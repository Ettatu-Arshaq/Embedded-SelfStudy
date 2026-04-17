# 🔄 FreeRTOS Queue Communication Example (STM32F407)

## 📌 Overview

This project demonstrates **inter-task communication using queues** in FreeRTOS on the STM32F407.

One task generates data (counter), and another task consumes it to control an LED.

---

## 🎯 Objective

* Learn how to use **FreeRTOS queues**
* Understand **producer-consumer pattern**
* Control hardware based on task communication

---

## ⚙️ How It Works

### 🔹 Task 1 (Producer)

* Increments a counter every 500 ms
* Sends the value to a queue

```id="y4k2jf"
count++;
xQueueSend(myQueue, &count, portMAX_DELAY);
```

---

### 🔹 Task 2 (Consumer)

* Waits for data from the queue
* Controls LED based on received value

```id="y3p8dn"
if(received % 2 == 0)
    LED ON
else
    LED OFF
```

---

## 💡 System Behavior

```id="j2m6ls"
1 → LED OFF
2 → LED ON
3 → LED OFF
4 → LED ON
...
```

👉 LED toggles based on **even/odd values**

---

## 🧠 Architecture

```id="o9k1zx"
[ Task 1 (Producer) ]
        ↓
     (Queue)
        ↓
[ Task 2 (Consumer) ]
        ↓
     LED Control
```

---

## 🛠️ Hardware Used

* STM32F407 Discovery Board
* LED PD13 (Orange)

---

## ⚙️ Software Used

* FreeRTOS
* STM32CubeIDE
* ARM GCC Toolchain

---

## 🚀 How to Run

1. Build project in STM32CubeIDE
2. Flash to STM32F407 board
3. Observe LED behavior:

   * Even count → LED ON
   * Odd count → LED OFF

---

## 🧠 Key Concepts

### 🔹 Queue

* Used for **safe data transfer between tasks**
* FIFO (First In First Out)

---

### 🔹 Blocking API

```id="y0c8pz"
xQueueReceive(..., portMAX_DELAY);
```

👉 Task waits until data is available (no CPU waste)

---

### 🔹 Task Priorities

* Task1 → Priority 2 (Producer)
* Task2 → Priority 1 (Consumer)

---

## ⚠️ Notes

* Queue size = 5 elements
* If queue is full → sender blocks
* If queue is empty → receiver waits

---

## 📈 Next Steps

* Use queue with structures
* Add multiple producers
* Combine with UART output
* Integrate with interrupts (ISR → Queue)

---

## 🧑‍💻 Author

**Muhammad Arshaq**
