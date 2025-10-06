/*
 * File:   newmain.c
 * Author: arshaq
 *
 * Created on August 27, 2025, 4:55 PM
 */
// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF      // Watchdog Timer Enable (WDT disabled)
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
#define _XTAL_FREQ 100000
void main(void) {
    // Setup
    ANSELA=0;
    TRISA=0xFF;
    ANSELB = 0;  
    TRISB = 0; 
    LATB= 0;     // Start LED OFF
    LATA=0;
    while(1){
        if(PORTAbits.RA0==1){
            for(int i=7;i>=0;i--){
                LATB=(1<<(7-i));
               __delay_ms(500);
            }
        }
        if(PORTAbits.RA1==1){
            int c1=0,c2=0;
            while(PORTAbits.RA1==1) {
                __delay_ms(1);   // 1ms tick
                c1++;
                c2++;

                if(c1 >= 200) {          // every 200ms
                    LATBbits.LATB0 = !LATBbits.LATB0;  // toggle LED
                    c1 = 0;
                }

                if(c2 >= 500) {          // every 500ms
                    LATBbits.LATB1 = !LATBbits.LATB1;  // toggle LED
                    c2 = 0;
                }
            }

        }
        if(PORTAbits.RA2==1){
            uint8_t pat[] = {0b0001,0b0010,0b0100,0b1000};
            for(int i=0;i<4;i++){
                LATB=pat[i];
                __delay_ms(500);
            }
            
        }
    }
}
