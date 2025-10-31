#pragma config FOSC = INTOSC
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config BOREN = OFF
#pragma config CLKOUTEN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config WRT = OFF
#pragma config VCAPEN = OFF
#pragma config STVREN = ON
#pragma config BORV = LO
#pragma config LPBOR = OFF
#pragma config LVP = ON


#include <xc.h>
#define _XTAL_FREQ 4000000
volatile int intr=0;
void init_timer2(){
    OSCCON=0x6A;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.TMR2IE=1;
    PIR1bits.TMR2IF=0;
    T2CON=0x7E;
    PR2=255;
    TMR2=0;
}
void main() 
{   
    ANSELAbits.ANSA0=0;
    TRISAbits.TRISA0=0;
    LATAbits.LATA0=0;
    init_timer2();
    
    while(1);

}
void __interrupt() isr()
{
    if(PIR1bits.TMR2IF==1)
        {
        TMR2=0;
        intr +=1;
        PIR1bits.TMR2IF=0;
        if(intr==15)
            
        {
            
            LATAbits.LATA0=~LATAbits.LATA0;
            intr=0;
        }
}
}