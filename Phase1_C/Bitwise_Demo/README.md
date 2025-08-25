# 🧮 Bitwise Register Simulator (C)

## 📌 Overview
This project simulates an **8-bit microcontroller register** using C bitwise operators.  
It allows the user to **set, clear, toggle, read, and print** individual bits in a register.  
This mimics how embedded engineers interact with **hardware registers** (GPIO, timers, peripherals).

---

## 🎯 Features
- **Set a bit** (`reg |= (1 << bit)`)
- **Clear a bit** (`reg &= ~(1 << bit)`)
- **Toggle a bit** (`reg ^= (1 << bit)`)
- **Read a bit** (`(reg >> bit) & 1`)
- **Print the register** in binary format

---

## 📂 File Structure
```
Phase1_C/
 └── BitwiseDemo/
      ├── bitwise_register.c   # Main source code
      └── README.md            # Project documentation
```

---

## 🖥️ Example Run
```
--- 8-Bit Register Simulator ---
1. Set Bit
2. Clear Bit
3. Toggle Bit
4. Read Bit
5. Print Register
6. Exit
Choose: 1
Enter bit position (0-7): 2
Register: 00000100

Choose: 3
Enter bit position (0-7): 0
Register: 00000101

Choose: 4
Enter bit position (0-7): 0
Bit 0 = 1
```

---

## 📘 Embedded Context
In real microcontrollers:
- **Registers** are special memory locations controlling peripherals.  
- For example, on an **ARM Cortex-M MCU**:  
  - `GPIOA->ODR |= (1 << 5);` sets Pin A5 high (LED ON).  
  - `GPIOA->ODR &= ~(1 << 5);` clears Pin A5 (LED OFF).  
- This project helps you **understand how low-level register manipulation works** before moving to real hardware.

---

## ✅ Skills Learned
- Bitwise operators in C (`|`, `&`, `^`, `~`, `<<`, `>>`)
- Simulating embedded hardware registers
- Menu-driven program structure in C
