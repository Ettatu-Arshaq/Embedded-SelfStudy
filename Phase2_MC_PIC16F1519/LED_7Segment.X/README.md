# 🔢 LED 7-Segment Display (PIC)

## 📌 Project Overview
This project demonstrates how to interface a **7-segment display** with a PIC microcontroller using **GPIO control**.

It is part of **Phase 2 (PIC Microcontroller Projects)** in my Embedded Systems self-study roadmap, focusing on low-level hardware control and digital output patterns.

---

## 🎯 Objective
- Drive a 7-segment display using GPIO pins  
- Represent digits (0–9) using binary patterns  
- Understand how hardware-level control translates into visible output  

---

## ⚙️ Hardware & Tools
- **Microcontroller:** PIC16F1519 / PIC16F877A  
- **IDE:** MPLAB X IDE  
- **Compiler:** XC8  
- **Language:** Embedded C  

---

## 🧠 Concepts Covered
- GPIO configuration and control  
- Bit manipulation for segment control  
- Digital output mapping  
- Introduction to multiplexing (scalable to multi-digit displays)  

---

## 🔧 Implementation Details

### Segment Mapping

uint8_t segment[10] = {
  0x3F, 0x06, 0x5B, 0x4F, 0x66,
  0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

Each value represents the ON/OFF pattern of segments to display digits 0–9.

GPIO Configuration
TRISA = 0;   // Configure PORTA as output
ANSELA = 0;  // Set PORTA as digital

The microcontroller sends binary patterns to the display pins to illuminate the correct segments.

---
▶️ How to Run
git clone https://github.com/Ettatu-Arshaq/Embedded-SelfStudy.git
cd Embedded-SelfStudy/Phase2_PIC/LED_7Segment.X
Open the project in MPLAB X IDE
Build using XC8 compiler
Flash to the PIC microcontroller
Observe the 7-segment display output

---
📸 Output

<img width="400" height="200" alt="Screenshot 2026-04-18 123511" src="https://github.com/user-attachments/assets/c8a7ac38-ade1-4730-9a22-4ea5313b986c" />

<img width="400" height="200" alt="Screenshot 2026-04-18 123522" src="https://github.com/user-attachments/assets/483e70fc-0f72-42d3-a756-44cc9f498d74" />


Displays digits (0–9) sequentially or a fixed number
Segments illuminate according to binary patterns

---
💡 Why This Project Matters

This project demonstrates:

Low-level hardware control using GPIO
Understanding of how binary data maps to physical output
Foundation for display systems used in:
Digital clocks
Measurement devices
Embedded UI systems

---
🚀 Future Improvements
Multi-digit display using multiplexing
Timer-based refresh for stable display
Scrolling numbers / animation effects

---
🏁 Learning Outcome
Strong understanding of GPIO-based device control
Ability to convert logic into hardware behavior
Foundation for advanced display interfacing

---
🏆 Author

Muhammad Arshaq
📅 Completed: October 2025
📚 Phase 2 – PIC Microcontroller Projects
