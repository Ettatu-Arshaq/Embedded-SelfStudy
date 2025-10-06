/*
 * File:   newmain.c
 * Author: arshaq
 *
 * Created on August 27, 2025, 4:55 PM
 */

// CONFIG1
#pragma config FOSC = HS        // HS Oscillator
#pragma config WDTE = OFF       // Watchdog Timer disabled
#pragma config PWRTE = ON       // Power-up Timer enabled
#pragma config MCLRE = ON       // MCLR pin enabled
#pragma config CP = OFF         // Flash Program Memory Code Protection disabled
#pragma config BOREN = ON       // Brown-out Reset enabled
#pragma config CLKOUTEN = OFF   // CLKOUT disabled

// CONFIG2
#pragma config WRT = OFF        // Flash write protection disabled
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor off
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset enabled
#pragma config BORV = LO        // Brown-out Reset Voltage (low trip point)
#pragma config LVP = OFF        // Low-Voltage Programming disabled



#include <xc.h>
#define _XTAL_FREQ 4000000

void main(void) {
    // Setup
    ANSELAbits.ANSA0 = 0;   // RA0 digital
    ANSELAbits.ANSA1 = 0;   // RA1 digital
    TRISAbits.TRISA0 = 0;   // RA0 output (LED)
    TRISAbits.TRISA1 = 1;   // RA1 input (Button)

    LATAbits.LATA0 = 0;     // Start LED OFF
    unsigned char led_state = 0;

    while(1){
        if (PORTAbits.RA1 == 1) {       // Button pressed
            __delay_ms(50);             // Debounce delay
            if (PORTAbits.RA1 == 1) {   // Confirm still pressed
                led_state = !led_state; // Toggle
                LATAbits.LATA0 = led_state;
                while(PORTAbits.RA1 == 1); // Wait until button released
            }
        }
    }
}
