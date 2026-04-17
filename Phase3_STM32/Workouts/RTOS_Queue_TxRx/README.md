# ⚡ FreeRTOS ISR → Queue → Task Communication (STM32F407)

## 📌 Overview

This project demonstrates **interrupt-driven communication in FreeRTOS** using:

* External Interrupt (EXTI)
* Queue (ISR → Task)
* UART output

An interrupt (button press) sends data to a queue, and a task processes it.

---

## 🎯 Objective

* Learn **ISR to Task communication**
* Use **xQueueSendFromISR()**
* Handle real-time external events
* Understand **deferred interrupt processing**

---

## ⚙️ How It Works

### 🔹 Step 1: External Interrupt (EXTI0)

* Triggered on **PA0 (button press)**
* Falling edge detection

---

### 🔹 Step 2: ISR (Interrupt Handler)

```c
void EXTI0_IRQHandler(void)
{
    uint8_t receivedByte = 'X';

    xQueueSendFromISR(uartRxQueue, &receivedByte, &xHigherPriorityTaskWoken);

    EXTI_PR |= (1 << 0); // clear flag
}
```

👉 ISR sends data to queue instead of doing heavy work

---

### 🔹 Step 3: UART Task

```c
xQueueReceive(uartRxQueue, &data, portMAX_DELAY);
UART_SendChar(data);
```

👉 Task receives data and processes it safely

---

## 🔁 System Flow

```text
Button Press (PA0)
        ↓
     Interrupt
        ↓
     ISR (EXTI0)
        ↓
   Queue Send (ISR)
        ↓
   FreeRTOS Queue
        ↓
   UART Task
        ↓
   Serial Output ('X')
```

---

## 📤 Output

```text
X
X
X
...
```

👉 Each button press prints `'X'` on UART

---

## 🧠 Key Concepts

### 🔹 ISR vs Task

| ISR                 | Task                   |
| ------------------- | ---------------------- |
| Fast, minimal work  | Can handle heavy logic |
| No blocking allowed | Blocking allowed       |
| Uses special APIs   | Uses normal APIs       |

---

### 🔹 ISR Safe API

```c
xQueueSendFromISR()
```

👉 Must be used inside interrupts
👉 Different from `xQueueSend()`

---

### 🔹 Context Switching

```c
portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
```

👉 Forces scheduler to switch immediately if needed

---

## ⚠️ Important Notes

* Never use `printf()` inside ISR
* Keep ISR execution very short
* Always clear interrupt flag
* Use `FromISR` APIs only

---

## 🛠️ Hardware Used

* STM32F407 Discovery
* Push Button (PA0)

---

## ⚙️ Software Used

* FreeRTOS
* STM32CubeIDE
* ARM GCC

---

## 🚀 How to Run

1. Build and flash
2. Open serial terminal (115200 baud)
3. Press button (PA0)
4. Observe UART output

---

## 📈 Advanced Improvements

* Replace `'X'` with real UART RX data
* Add debounce logic
* Use binary semaphore instead of queue
* Add multiple interrupt sources
* Prioritize real-time tasks

---

## 🧠 What You Just Achieved

✔ Tasks
✔ Delay
✔ Queue
✔ Mutex
✔ Timer
✔ UART
✔ Interrupts
✔ ISR-safe APIs

👉 This is **core RTOS mastery level**

---

## 🧑‍💻 Author

**Muhammad Arshaq**
