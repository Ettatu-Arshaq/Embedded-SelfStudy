📚 Timer_tick_2_LED.X (Phase 2)
📌 Project Overview

A PIC microcontroller project to blink two LEDs at different rates using Timer0 and a software tick counter.
This is part of Phase 2 mini projects from my Embedded Systems self-study roadmap.

🛠 Features

Use Timer0 with prescaler and preload to generate a 1 ms software tick

Blink two LEDs at different intervals:

LED1: 500 ms

LED2: 200 ms

Implement interrupt-driven timing (non-blocking)

Learn preload, prescaler, and ISR handling

Foundation for RTOS-style scheduling

📂 Data Structure
#define LED1 LATAbits.LATA0
#define LED2 LATAbits.LATA1

volatile unsigned long ms_tick = 0;
unsigned long last_toggle1 = 0;
unsigned long last_toggle2 = 0;


ms_tick increments every millisecond in Timer0 ISR. LEDs toggle based on software counters.

💻 Technologies Used

Language: Embedded C

Concepts: Timer0, Prescaler, Preload, Interrupts, Non-blocking LED control

IDE: MPLAB X IDE

Compiler: XC8

▶ How to Run

Clone the repository:

git clone https://github.com/Ettatu-Arshaq/Embedded-SelfStudy.git


Navigate to the project folder:

cd Embedded-SelfStudy/Phase2_PIC/Timer_tick_2_LED.X


Open the project in MPLAB X IDE.

Compile and program the PIC16F1519 / PIC16F877A.

Observe:

LED1 (RA0) blinks every 500 ms

LED2 (RA1) blinks every 200 ms

📸 Sample Output
Time(ms): 0    LED1: ON   LED2: ON
Time(ms): 200  LED1: ON   LED2: OFF
Time(ms): 400  LED1: ON   LED2: ON
Time(ms): 500  LED1: OFF  LED2: ON


LEDs toggle based on independent software counters.

📌 Future Improvements

Add pause/resume button functionality

Extend to more LEDs or different patterns using the same software tick

Move to Timer1 for longer delays or higher resolution

Implement software clock or pulse counter

🏆 Author

Muhammad Arshaq
📅 Completed: October 2025
Part of Phase 2 – PIC Microcontroller Projects in my Embedded Systems self-study roadmap.