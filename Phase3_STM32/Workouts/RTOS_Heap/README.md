# 🧠 FreeRTOS Heap Monitoring (STM32F407)

## 📌 Overview

This is a simple FreeRTOS example that demonstrates how to monitor **dynamic memory usage (heap)** in a real-time embedded system.

The system periodically prints the available heap size over UART.

---

## 🎯 Objective

* Learn how to use:

  * `xPortGetFreeHeapSize()`
  * FreeRTOS task scheduling
* Monitor system memory usage in real-time

---

## ⚙️ How It Works

### 🔹 Heap Task

* A FreeRTOS task runs every 1 second
* Calls:

  ```c
  xPortGetFreeHeapSize();
  ```
* Sends the value via UART

---

## 🖥️ Output Example

```id="9v7g5a"
Heap: 8120
Heap: 8120
Heap: 8120
```

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

## 📂 Code Highlights

### Heap Monitoring

```c
sprintf(buffer, "Heap: %lu\r\n", xPortGetFreeHeapSize());
```

### Periodic Task

```c
vTaskDelay(pdMS_TO_TICKS(1000));
```

---

## 🚀 How to Run

1. Build project in STM32CubeIDE
2. Flash to board
3. Open UART terminal (115200 baud)
4. Observe heap values every second

---

## 🧠 Key Concept

👉 `xPortGetFreeHeapSize()`
Returns the **currently available heap memory** in bytes.

---

## ⚠️ Note

* If heap becomes **0**, system may fail to create tasks/queues
* Useful for debugging memory issues in embedded systems

---

## 📈 Next Steps

* Use:

  ```c
  xPortGetMinimumEverFreeHeapSize();
  ```

  👉 To track **lowest heap ever available**

---

## 🧑‍💻 Author

Muhammad Arshaq