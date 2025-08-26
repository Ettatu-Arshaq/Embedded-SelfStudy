# 💡 LED Blinker Config Simulator (Phase 1 Project)

This project simulates an **8-bit LED Blinker** using C.  
It allows users to configure an LED pattern (binary), set delay time, save/load configuration to file, and simulate the blinking sequence.  

📍 Developed as part of **Phase 1: C Programming for Embedded Systems** in my self-study roadmap.

---

## 🚀 Features
- Configure an **8-bit LED pattern** (`1 = ON`, `0 = OFF`)
- Set custom delay time (in milliseconds)
- Save configuration to a binary file (`config.bin`)
- Load configuration on program start
- Simulate blinking with delay and repeat cycles
- Uses **bitwise operations**, **structs**, and **file handling** → embedded-friendly concepts

---

## 🛠️ Technologies Used
- **C Programming**
- File handling (`fopen`, `fwrite`, `fread`)
- Bitwise operators for LED simulation
- Windows API `Sleep()` for delay (use `usleep()` on Linux)

---

## 📂 Project Structure
```
LEDBlinkerSim/
│── main.c         # Source code
│── config.bin     # Saved configuration (auto-generated)
│── README.md      # Project documentation
```

---

## ⚡ How It Works
1. On start, program tries to **load saved config**.  
   - If found → loads values.  
   - If not found → uses defaults (`pattern = 1010`, `delay = 500 ms`).
2. Menu Options:
   - `1` → Set new config (pattern + delay)
   - `2` → Save config to file
   - `3` → Simulate blinking sequence
   - `4` → Exit

---

## 🖥️ Example Output
```
===== LED Blinker Config Menu =====
1. Set Config
2. Save Config
3. Simulate Blinking
4. Exit
Choice: 3

LED1: OFF
LED2: ON
LED3: OFF
LED4: ON
--- Cycle 1 Complete ---
```

---

## 🎯 Learning Outcome
This project strengthens:
- Bit manipulation (`<<`, `>>`, `&`, `|`, `^`, `~`)
- Structs + persistent storage (like EEPROM in MCUs)
- Simulated GPIO handling
- Building **modular embedded-style C programs**

---

👤 Author: Muhammad Arshaq  
📌 Repository: [Embedded-SelfStudy](../..)
