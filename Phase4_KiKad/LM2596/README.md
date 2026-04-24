# ⚡ LM2596 Buck Converter – PCB Design (KiCad)

## 📌 Project Overview

This project is a **DC-DC Buck Converter PCB** designed using **KiCad**, based on the widely used **LM2596** switching regulator.

The circuit efficiently steps down a higher DC input voltage to a stable lower output voltage, making it ideal for embedded and IoT applications.

---

## ⚙️ Working Principle

The **LM2596** operates as a **switching regulator (buck converter)**:

1. Input DC voltage is applied through a barrel jack.
2. The IC switches internally at high frequency (~150 kHz).
3. Energy is stored in the inductor during ON time.
4. During OFF time, energy is released through the Schottky diode.
5. Output is filtered using capacitors to provide a stable DC voltage.
6. Feedback (FB pin) maintains constant output voltage.

---

## 🧩 Circuit Components

| Component | Description                   |
| --------- | ----------------------------- |
| U1        | LM2596S-ADJ Buck Converter IC |
| J3        | Barrel Jack (DC Input)        |
| C1        | Input Capacitor (680µF)       |
| L1        | Inductor (33µH)               |
| D1        | Schottky Diode (1N5822)       |
| C2        | Output Capacitor (220µF)      |
| J2        | Output Connector              |
| PWR_FLAG  | Power indication              |
| GND       | Ground reference              |

---

## 🔌 Input / Output

### Input:

* Voltage: **7V – 35V DC** (typical)
* Connector: Barrel Jack

### Output:

* Adjustable DC Output (based on feedback network)
* Connector: 2-pin header

---

## 🎛️ Features

* High efficiency (up to ~90%)
* Wide input voltage range
* Adjustable output voltage
* Compact and robust design
* Suitable for embedded systems power supply

---

## 🛠️ Design Tools

* **KiCad** (Schematic + PCB)

---

## 📷 PCB

<img width="720" height="480" alt="Screenshot 2026-04-24 193104" src="https://github.com/user-attachments/assets/f6d2b321-857b-4d1a-aade-1db706e41665" />


---

## 🚀 Applications

* Power supply for **STM32 / Arduino / ESP modules**
* Battery-powered systems
* IoT devices
* Robotics projects

---

## ⚠️ Important Design Notes

* Use **low ESR capacitors** for stability
* Keep **switching loop (IC + diode + inductor)** as short as possible in PCB
* Use **thick traces** for high current paths
* Proper grounding is critical for noise reduction

---

## 🔧 Future Improvements

* Add output voltage adjustment potentiometer (feedback divider)
* Include heatsink provision for high load
* Add LED power indicator
* Add reverse polarity protection

---

## 🧠 Learning Outcomes

* Understanding **switching regulators**
* Buck converter design fundamentals
* Power electronics basics
* PCB layout considerations for power circuits

---

## 🔗 Author

**Muhammad Arshaq**
Embedded Systems & IoT Enthusiast

---
