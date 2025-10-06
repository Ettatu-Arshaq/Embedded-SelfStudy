// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = ON       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON      // Brown-out Reset Enable (Brown-out Reset disabled)
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
uint16_t result=0;
#define _XTAL_FREQ 1000000
void main() 
{   
    OSCCONbits.IRCF=0xD;
    ANSELAbits.ANSA0=0;
    TRISAbits.TRISA0=0;
    INTCON=0xA0; //1010 0000 (GIE,TMROIE,TMROIF=0)
    OPTION_REG=0x97; // 1001 0111 (WPUEN,TMR0SE->HIGH TO LOW CLK ,TMROCS=0 ,PSA=0,PS=111)
    TMR0=0; //START FROM 0-> 255
    
    while(1)
    {
        LATAbits.LATA0=0;
        
    }
    return;
}
void __interrupt() isr()
{
    if(TMR0IF==1)
        {
            TMR0IF=0;
            LATAbits.LATA0=1;
            
           
            
        }
}