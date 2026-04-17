# 🚀 STM32F407 FreeRTOS Button Event System

## 📌 Overview

This project demonstrates a **real-time embedded firmware architecture** using **FreeRTOS** on the STM32F407 microcontroller.

It implements an **event-driven system** where a button press triggers an interrupt, which is safely processed using RTOS mechanisms like **queues, tasks, mutexes, and software timers**.

---

## 🎯 Features

* ✅ External Interrupt (EXTI) based button input
* ✅ Software debouncing using FreeRTOS Timer
* ✅ Queue-based ISR → Task communication
* ✅ Task separation (Processing + UART)
* ✅ UART communication with mutex protection
* ✅ Button press counter
* ✅ Heartbeat LED using software timer

---

## 🧠 System Architecture

```
[ Button Press (EXTI ISR) ]
            ↓
        (Queue)
            ↓
 [ Processing Task ]
            ↓
        (Queue)
            ↓
   [ UART Task (Mutex) ]

 + Software Timer (LED Heartbeat)
 + Debounce Timer (50–100 ms)
```

---

## 🔧 How It Works

### 🔘 1. Button Interrupt (ISR)

* Triggered on rising edge (PA0)
* Sends event to `buttonQueue`
* Disables interrupt temporarily
* Starts debounce timer

---

### ⏱️ 2. Debounce Timer

* One-shot timer (~100 ms)
* Re-enables EXTI interrupt
* Prevents multiple triggers from button bounce

---

### 🔄 3. Processing Task

* Waits for button event
* Increments press counter
* Formats message
* Sends to `uartQueue`

---

### 📤 4. UART Task

* Receives message from queue
* Uses mutex for safe UART access
* Sends data over USART2

---

### 💡 5. LED Timer

* Toggles LED every 1 second
* Acts as system heartbeat indicator

---

## 🖥️ Output Example

```
Button Pressed: 1
Button Pressed: 2
Button Pressed: 3
```

---

## 🛠️ Hardware Requirements

* STM32F407 Discovery Board
* Push Button (connected to PA0)
* LED (on GPIOD Pin 12)
* UART (USART2 → PA2 TX)

---

## ⚙️ Software Requirements

* STM32CubeIDE
* FreeRTOS
* ARM GCC Toolchain

---

## 📂 Project Structure

```
Src/
 └── main.c       # Complete implementation

FreeRTOS/
 ├── include/
 ├── portable/
 └── source files
```

---

## 🚀 Build & Run

1. Import project into STM32CubeIDE
2. Build the project
3. Flash to STM32F407 board
4. Open UART terminal (115200 baud)
5. Press button → observe output

---

## 🔥 Key Concepts Demonstrated

* RTOS Task Scheduling
* ISR-safe APIs (`xQueueSendFromISR`)
* Inter-task Communication (Queues)
* Mutual Exclusion (Mutex)
* Software Timers
* Embedded System Design Patterns

---

## 📈 Future Improvements

* ⏳ Long Press Detection
* 🔁 Double Click Detection
* 📦 Event Struct-based Messaging
* 📊 Heap Monitoring Task
* ⚡ Interrupt Priority Optimization

---

## 🧑‍💻 Author

**Your Name**

Muhammad Arshaq

## 📜 License

This project is open-source and available under the MIT License.

---

## ⭐ Acknowledgment

This project is built as a learning step toward **real-world embedded systems design using FreeRTOS**.
