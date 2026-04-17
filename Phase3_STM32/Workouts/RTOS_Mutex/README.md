# 🔐 FreeRTOS UART Mutex Example (STM32F407)

## 📌 Overview

This project demonstrates how to safely share a **common resource (UART)** between multiple tasks using a **mutex** in FreeRTOS.

Two tasks attempt to send data over UART simultaneously, and a mutex ensures **data integrity** by preventing conflicts.

---

## 🎯 Objective

* Understand **mutex (mutual exclusion)**
* Prevent resource conflicts between tasks
* Learn safe UART communication in RTOS

---

## ⚙️ How It Works

### 🔹 Task 1

* Sends:

```id="a1x92k"
AAAAA
```

### 🔹 Task 2

* Sends:

```id="b8m3lp"
BBBBB
```

---

### 🔐 Mutex Protection

Both tasks:

```id="z9d2qw"
xSemaphoreTake(uartMutex, portMAX_DELAY);
...
xSemaphoreGive(uartMutex);
```

👉 Ensures only **one task uses UART at a time**

---

## 🖥️ Output Behavior

### ✅ With Mutex (Correct)

```id="q7v2as"
AAAAA
BBBBB
AAAAA
BBBBB
```

---

### ❌ Without Mutex (Problem)

```id="p3n6yt"
ABABABABA ❌
```

👉 Data gets mixed due to simultaneous access

---

## 🧠 Key Concepts

### 🔹 Mutex

* Special type of semaphore
* Used for **resource protection**
* Prevents race conditions

---

### 🔹 Task Synchronization

* Tasks coordinate access to shared hardware
* Ensures predictable system behavior

---

## 🛠️ Hardware Used

* STM32F407 Discovery Board
* UART (USART2 → PA2 TX)

---

## ⚙️ Software Used

* FreeRTOS
* STM32CubeIDE
* ARM GCC Toolchain

---

## 🚀 How to Run

1. Build project in STM32CubeIDE
2. Flash to STM32F407 board
3. Open UART terminal (115200 baud)
4. Observe clean alternating output

---

## ⚠️ Important Notes

* Both tasks have the same priority
* Mutex avoids data corruption
* Always release mutex after use

---

## 📈 Next Steps

* Add queue-based UART messaging
* Use binary semaphore for signaling
* Implement priority-based task handling

---

## 🧑‍💻 Author

**Muhammad Arshaq**
