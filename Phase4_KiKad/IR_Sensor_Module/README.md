# 📡 IR Sensor Module – PCB Design (KiCad)

## 📌 Project Overview

This project is a custom-designed **Infrared (IR) Sensor Module PCB** created using **KiCad**. The module detects objects using IR transmission and reception, processes the signal using a comparator (op-amp), and provides a digital output.

This design is suitable for:

* Obstacle detection robots 🤖
* Line-following systems
* Proximity sensing applications

---

## ⚙️ Working Principle

The module works based on **IR reflection**:

1. **IR LED (Transmitter)** emits infrared light.
2. When an object is present, IR light is reflected back.
3. **Photodiode (Receiver)** detects the reflected IR signal.
4. The signal is converted into voltage and passed to an **Op-Amp Comparator**.
5. Comparator compares signal with a reference voltage (set via potentiometer).
6. Output is:

   * **HIGH** → Object detected
   * **LOW** → No object

---

## 🧩 Circuit Components

| Component | Description                          |
| --------- | ------------------------------------ |
| D3        | IR Transmitter LED                   |
| D2        | IR Receiver (Photodiode)             |
| U1A       | Op-Amp Comparator                    |
| R1        | Current limiting resistor for IR LED |
| R2        | Pull-down resistor                   |
| R3        | Output LED resistor                  |
| R4        | Potentiometer (Sensitivity control)  |
| D1        | Output Indicator LED                 |
| J1        | Output Header Pins                   |
| PWR_FLAG  | Power indication                     |
| GND_FLAG  | Ground reference                     |

---

## 🔌 Pin Configuration (J1)

| Pin | Function  |
| --- | --------- |
| 1   | VCC (+5V) |
| 2   | OUTPUT    |
| 3   | GND       |

---

## 🎛️ Features

* Adjustable sensitivity using potentiometer
* On-board output LED indicator
* Compact PCB design
* Simple digital output interface
* Easy integration with microcontrollers (STM32, Arduino, etc.)

---

## 🛠️ Design Tools

* **KiCad** (Schematic + PCB Design)

---

## 📷 Schematic

> *(Add your schematic screenshot here)*

---

## 🚀 Applications

* Line follower robot
* Obstacle avoidance robot
* Object counting systems
* Automation projects

---

## 📈 Future Improvements

* Add noise filtering capacitor
* Use LM393 comparator for better stability
* Add mounting holes for mechanical support
* Improve IR shielding for accuracy

---

## 🧠 Learning Outcomes

* Understanding IR sensing principles
* Comparator circuit design
* Analog-to-digital signal conversion
* PCB design workflow in KiCad

---

## 🔗 Author

**Muhammad Arshaq**
Embedded Systems Enthusiast

---
