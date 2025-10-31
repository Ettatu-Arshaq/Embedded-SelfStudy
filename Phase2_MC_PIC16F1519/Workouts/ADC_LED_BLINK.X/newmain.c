/*
 * 
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
#define led LATAbits.LATA1
#define _XTAL_FREQ  4000000
uint16_t result=0;
void blink(){
    led=!led;
}
void adc_init(){
    ANSELAbits.ANSA0=1; 
    TRISAbits.TRISA0=1;
    ADCON0=0x01;    //(0,CHS=00000,GO=0,ADON=1)
    ADCON1=0xF0;    //(ADFM=1,ADCS=1111,0,0,ADPREF=00)
}

void main(void) {
    adc_init();
    ANSELAbits.ANSA1=0;
    TRISAbits.TRISA1=0;
    ADCON0bits.GO=1;
    while(ADCON0bits.GO);
    result=((ADRESH<<8)|ADRESL);
    if (result>500){
        blink();
    }
    __delay_ms(100);

}
