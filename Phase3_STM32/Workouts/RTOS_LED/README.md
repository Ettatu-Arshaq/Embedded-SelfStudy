# 🔁 FreeRTOS Multi-Task LED Blinking (STM32F407)

## 📌 Overview

This project demonstrates **basic multitasking in FreeRTOS** using the STM32F407 microcontroller.

Two independent tasks toggle two LEDs at different time intervals, showing how an RTOS schedules tasks concurrently.

---

## 🎯 Objective

* Understand FreeRTOS task creation
* Learn task scheduling using `vTaskDelay()`
* Demonstrate concurrent execution of multiple tasks

---

## ⚙️ How It Works

### 🔹 Task 1

* Toggles **LED (PD12)**
* Runs every **500 ms**

### 🔹 Task 2

* Toggles **LED (PD13)**
* Runs every **1500 ms**

---

## 🧠 System Behavior

Both tasks run independently under the FreeRTOS scheduler:

```id="v7p3y9"
Task1 → Fast blinking (500 ms)
Task2 → Slow blinking (1500 ms)
```

👉 Even though there's a single CPU, FreeRTOS switches between tasks to create **concurrent behavior**

---

## 💡 Key Concepts

### 🔹 Task Creation

```c id="c2p8jg"
xTaskCreate(Task1_Handler, "Task1", 128, NULL, 1, NULL);
xTaskCreate(Task2_Handler, "Task2", 128, NULL, 1, NULL);
```

---

### 🔹 Task Delay

```c id="9r6y3k"
vTaskDelay(pdMS_TO_TICKS(500));
```

👉 Converts milliseconds → RTOS ticks

---

### 🔹 Scheduler Start

```c id="h5u2nf"
vTaskStartScheduler();
```

👉 Starts the RTOS kernel

---

## 🖥️ Hardware Used

* STM32F407 Discovery Board
* LED PD12 (Green)
* LED PD13 (Orange)

---

## 🛠️ Software Used

* FreeRTOS
* STM32CubeIDE
* ARM GCC Toolchain

---

## 🚀 How to Run

1. Build project in STM32CubeIDE
2. Flash to STM32F407 board
3. Observe LEDs:

   * PD12 → fast blink
   * PD13 → slow blink

---

## 🧠 Key Learning

* RTOS allows multiple tasks to run “simultaneously”
* Timing control is achieved without blocking the CPU
* Each task behaves independently

---

## ⚠️ Note

* Both tasks have the **same priority**
* Scheduler uses **time slicing** to switch between them

---

## 📈 Next Steps

* Add task priorities
* Use queues for communication
* Replace `vTaskDelay` with software timers

---

## 🧑‍💻 Author

Muhammad Arshaq