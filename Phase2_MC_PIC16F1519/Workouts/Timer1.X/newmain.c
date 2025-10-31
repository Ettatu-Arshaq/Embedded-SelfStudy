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
void init_timer1(){
    OSCCON=0x6A;
    INTCONbits.GIE=1;
    INTCONbits.PEIE=1;
    PIE1bits.TMR1IE=1;
    PIR1bits.TMR1IF=0;
    T1CONbits.TMR1CS=0;
    T1CONbits.T1CKPS=0x03;
    T1CONbits.TMR1ON=1;
    TMR1=0;
}
void main() 
{   
    ANSELAbits.ANSA0=0;
    TRISAbits.TRISA0=0;
    LATAbits.LATA0=0;
    init_timer1();
    
    while(1);

}
void __interrupt() isr()
{
    if(PIR1bits.TMR1IF==1)
        {
        PIR1bits.TMR1IF=0;
        TMR1=0;
        LATAbits.LATA0=~LATAbits.LATA0;
        }
}