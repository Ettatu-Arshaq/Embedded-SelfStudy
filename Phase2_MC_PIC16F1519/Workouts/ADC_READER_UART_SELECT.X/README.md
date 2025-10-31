🔌 ADC Voltage to UART Display.X 🧠 Overview

This project reads analog voltage input from RA0 using the ADC module of the PIC16F1519, converts it into a digital value, calculates the corresponding voltage, and transmits the result via UART (9600 baud) to a serial monitor.

⚙️ Features

Reads analog voltage from AN0 (RA0)

Converts ADC value (10-bit) to voltage in volts

Transmits the result as a formatted floating-point value over UART

Displays voltage values like 4.87, 2.45, etc. on the serial terminal

Includes a custom uart_char() function for sending float values without using dtostrf()

🧩 Hardware Connections Component Pin Description ADC Input RA0 Analog input voltage (0–5V) UART TX RC6 Transmit pin connected to serial terminal RX UART RX RC7 Receive pin (not used in this project) MCU Clock INTOSC @ 4 MHz Internal oscillator 📘 Code Flow

Initialize UART – Configure serial communication at 9600 baud.

Initialize ADC – Set up ADC on channel AN0.

Read ADC value – Start conversion and wait until completion.

Compute Voltage –

𝑉 𝑖 𝑛
𝐴 𝐷 𝐶 × 5.0 1023.0 V in​

= 1023.0 ADC×5.0​

Display Result – Send voltage value via UART using the custom formatter.

🧪 Example Output 4.87
3.22
0.98

🧰 Tools Used

MPLAB X IDE

XC8 Compiler

Proteus 8 (Simulation)

PIC16F1519 Microcontroller

📡 Baud Rate

9600 bps

8-bit data, no parity, 1 stop bit (8N1)