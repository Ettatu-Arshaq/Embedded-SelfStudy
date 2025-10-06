/*
 * File:  counter using timer
 * 
 *
 * Created on September 27, 2025, 11:52 AM
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
//MS TICK -TIMER COUNT
#define _XTAL_FREQ 4000000   // 1 MHz internal clock

#include <xc.h>
#define LED LATAbits.LATA0
volatile unsigned long ms_tick=0;
void main(void) {
    ANSELA=0;
    TRISA=0;
    LED=1;
    OSCCONbits.IRCF = 0b1101; // 4 MHz internal clock
    OSCCONbits.SCS = 0b10;    // Select internal oscillator
    OPTION_REGbits.T0CS=0;  //CLOCK SELECT -> INTERNAL
    OPTION_REGbits.PSA=0;   //Prescaler select
    OPTION_REGbits.PS=0b010;    //prescaler assign -> 1:8
    INTCONbits.TMR0IF=0;    //timer-0 flag
    INTCONbits.GIE=1;   //global interrupt
    INTCONbits.TMR0IE=1;    //timer0 enable
    INTCONbits.PEIE=1;  //peripheral interupt->here enabled but not used
    TMR0=131;   //timer0 starts from 131 -> 255(124 counts)
    unsigned long last_toggle=0;
    while(1){
        if (ms_tick-last_toggle>500){
            LED=~LED;
            last_toggle=ms_tick;
        }
    }
}
void __interrupt() ISR(void){
    if (TMR0IF){

        TMR0IF=0;
        TMR0=131;
        ms_tick++;
    }
}

/*
4 MHz / 4 = 1 MHz ? 1 µs per instruction cycle
With prescaler = 8 ? each Timer0 tick = 8 µs
 1ms=1000us
 1000/8 =125
 255-125=131  -> tmr0=131
124 ticks × 8 µs ? 992 µs ? 1 ms
So every overflow = ~1 ms tick.    
 
*/