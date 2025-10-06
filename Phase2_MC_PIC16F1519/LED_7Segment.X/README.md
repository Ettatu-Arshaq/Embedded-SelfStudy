📚 LED_7Segment.X (Phase 2)
📌 Project Overview

A PIC microcontroller program to drive a 7-segment display using GPIO pins.
This is part of Phase 2 mini projects from my Embedded Systems self-study roadmap.

🛠 Features

Display numbers on a 7-segment display

Use bit manipulation to control individual segments

Understand GPIO output and digital patterns

Learn multiplexing for multiple digits (if extended)

📂 Data Structure
uint8_t segment[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                       0x6D, 0x7D, 0x07, 0x7F, 0x6F};

TRISA = 0;   // Set PORTA as output
ANSELA = 0;  // Set PORTA as digital


Each element of segment[] corresponds to a number 0–9 on the display.

💻 Technologies Used

Language: Embedded C

Concepts: GPIO, Bit manipulation, Multiplexing

IDE: MPLAB X IDE

Compiler: XC8

▶ How to Run

Clone the repository:

git clone https://github.com/Ettatu-Arshaq/Embedded-SelfStudy.git


Navigate to the project folder:

cd Embedded-SelfStudy/Phase2_PIC/LED_7Segment.X


Open the project in MPLAB X IDE.

Compile and program the PIC16F1519 / PIC16F877A.

The 7-segment display will show numbers 0–9 or a fixed number depending on the code.

📸 Sample Output
7-segment display shows numbers sequentially or fixed value
Segments light up according to the number

📌 Future Improvements

Display multiple digits using multiplexing

Add scrolling numbers or animations

Use Timer interrupts for precise display refresh

🏆 Author

Muhammad Arshaq
📅 Completed: October 2025
Part of Phase 2 – PIC Microcontroller Projects in my Embedded Systems self-study roadmap.