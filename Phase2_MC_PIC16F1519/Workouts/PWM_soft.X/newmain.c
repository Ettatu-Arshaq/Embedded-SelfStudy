/*
 * File:   newmain.c
 * Author: arsha
 *
 * Created on October 6, 2025, 11:22 AM
 */

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = ON       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (VCAP pin function disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#define _XTAL_FREQ 4000000
void delay_us(unsigned int time){
    while(time--){
        __delay_us(1);
    }
}
void pwm_start(unsigned char duty){
    unsigned int on_time =(duty*1000)/100;
    unsigned int off_time=1000-on_time;
    LATAbits.LATA0=1;
    delay_us(on_time);
    LATAbits.LATA0=0;
    delay_us(off_time); 
    
}
void main() 
{
    OSCCON=0x6A;
    ANSELAbits.ANSA0=0;
    TRISAbits.TRISA0=0;
    LATAbits.LATA0=0;
    while(1){
     pwm_start(20);
     __delay_ms(1000);
     pwm_start(40);
     __delay_ms(1000);
//     pwm_start(60);
//     __delay_ms(1000);
     
    }
}

