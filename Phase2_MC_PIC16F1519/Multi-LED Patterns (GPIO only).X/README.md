# 💡 Multi-LED Patterns (GPIO Only) – PIC16F1519

## 📌 Overview
This project demonstrates multi-LED control patterns on the PIC16F1519 microcontroller using GPIO and software delays (no hardware timers yet).

It covers:
- Independent LED blinking at different rates  
- Running light (Knight Rider effect)  
- Custom pattern playback with button pause/resume  

This is part of the **Phase 2 – PIC Microcontroller Practice** series.

---

## ⚡ Features

### 🔹 Two LEDs, Independent Rates
- RB0 blinks every 200 ms  
- RB1 blinks every 500 ms  
- Controlled with software counters in the main loop  

### 🔹 Running Light (Knight Rider)
- A single ON LED shifts across RB0 → RB3 → back  
- Implemented using bit-shifts (`mask <<= 1`)  

### 🔹 Custom Pattern Player
Predefined array of patterns:

uint8_t pat[] = {0b0001, 0b0010, 0b0100, 0b1000};

Each step shown for 500 ms

Button on RA1 used to pause/resume playback

---
🛠️ Hardware Setup (Proteus Simulation)

🔹 LED Wiring
RB0–RB3 → 330 Ω → LED → GND

🔹 Buttons
RA0 → Running Light
RA1 → Independent Blinkers (200 ms & 500 ms)
RA2 → Pattern Player

🔹 Register Setup
ANSELB = 0x00;   // PORTB as digital  
TRISB  = 0x00;   // PORTB as output  
LATB   = 0x00;   // Clear LEDs  

ANSELA = 0x00;   // PORTA as digital  
TRISA  = 0xFF;   // PORTA as input (buttons)  

---

📂 Project Structure

Phase2_PIC/
 └── Multi-LED Patterns (GPIO only).X/
     ├── main.c
     ├── Multi-LED Patterns_GPIO.pdsprj
     └── README.md

 ---
▶️ Behavior

🔹 Case 1: RA0 Pressed → Running Light

LEDs move left-to-right and back:

0001 → 0010 → 0100 → 1000 → 0100 → 0010 → …

🔹 Case 2: RA1 Pressed → Independent Blinkers
RB0 toggles every 200 ms
RB1 toggles every 500 ms

🔹 Case 3: RA2 Pressed → Pattern Player
Displays array sequence
Playback pause/resume with RA1

---
📸 Demo
<img width="400" height="200" alt="Screenshot 2026-04-18 132351" src="https://github.com/user-attachments/assets/5a998101-a216-457a-a5c2-ba52d8a9d2ad" /> 

<img width="400" height="200" alt="Screenshot 2026-04-18 132404" src="https://github.com/user-attachments/assets/9e115b83-5527-452c-9055-525c27e2a751" /> 

<img width="400" height="200" alt="Screenshot 2026-04-18 132429" src="https://github.com/user-attachments/assets/69963c15-fa32-4698-a5d0-ac207ef50605" />

---
📖 Learning Outcomes

Controlled multiple GPIO outputs with PIC
Used software counters to simulate timers
Practiced bitwise operations for LED sequences
Integrated button input control for real-time interaction

---
