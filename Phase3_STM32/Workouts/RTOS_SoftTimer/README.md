# ⏱️ FreeRTOS Software Timer (STM32F407)

## 📌 Overview

This project demonstrates the use of a **FreeRTOS Software Timer** to periodically toggle an LED without creating a dedicated task.

The timer runs in the background and executes a callback function at fixed intervals.

---

## 🎯 Objective

* Learn **FreeRTOS Software Timers**
* Avoid unnecessary tasks for periodic actions
* Understand **callback-based execution**
* Implement lightweight scheduling

---

## ⚙️ How It Works

### 🔹 Timer Creation

```c
myTimer = xTimerCreate(
    "LED Timer",
    pdMS_TO_TICKS(500),
    pdTRUE,
    NULL,
    TimerCallback
);
```

* Period: 500 ms
* Auto-reload: Enabled (`pdTRUE`)
* Callback: `TimerCallback()`

---

### 🔹 Timer Callback Function

```c
void TimerCallback(TimerHandle_t xTimer)
{
    GPIOD_ODR ^= (1 << 12);
}
```

👉 Executes every 500 ms
👉 Toggles LED (PD12)

---

### 🔹 Start Timer

```c
xTimerStart(myTimer, 0);
```

👉 Timer starts before scheduler runs

---

## 🔁 System Flow

```text
FreeRTOS Scheduler
        ↓
 Timer Service Task
        ↓
 Software Timer Expiry
        ↓
 Callback Function
        ↓
 LED Toggle
```

---

## 💡 Behavior

* LED blinks every 500 ms
* No task created for blinking
* Efficient CPU usage

---

## 🧠 Key Concepts

### 🔹 Software Timer

* Runs in **Timer Service Task**
* Executes callback periodically
* Managed by FreeRTOS kernel

---

### 🔹 Auto-Reload Timer

| Mode      | Description     |
| --------- | --------------- |
| `pdTRUE`  | Repeats forever |
| `pdFALSE` | Runs once       |

---

### 🔹 Timer Callback Rules

* Must be short and fast
* Should NOT block
* Avoid heavy operations

---

## ⚠️ Important Notes

* Timer depends on **Timer Service Task**
* Ensure `configUSE_TIMERS = 1` in FreeRTOSConfig.h
* Timer queue length must be sufficient
* No `vTaskDelay()` inside callback

---

## 🛠️ Hardware Used

* STM32F407 Discovery
* LED (PD12)

---

## ⚙️ Software Used

* FreeRTOS
* STM32CubeIDE
* ARM GCC

---

## 🚀 How to Run

1. Build project
2. Flash to STM32F407
3. Observe LED blinking every 500 ms

---

## 🧠 Why Use Software Timers?

| Feature       | Task     | Timer  |
| ------------- | -------- | ------ |
| Memory usage  | Higher   | Lower  |
| Simplicity    | Medium   | Easy   |
| Periodic jobs | Possible | ✅ Best |

👉 Use timers for **periodic lightweight operations**

---

## 📈 Advanced Ideas

* Multiple timers (multi-LED control)
* One-shot timers (delayed execution)
* Timer + Queue communication
* Timer + ISR integration

---

## 🧠 What You Learned

✔ Timer creation
✔ Callback execution
✔ Periodic scheduling
✔ Kernel-managed timing

---

## 🧑‍💻 Author

**Muhammad Arshaq**
