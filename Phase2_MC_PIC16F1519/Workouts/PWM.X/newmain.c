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
#include <pic16f1519.h>
#define _XTAL_FREQ 4000000
volatile int intr=0;
void init_pwm(){
    OSCCON=0x6A;
    T2CON=0x05;
    PR2=249;
    TMR2=0;
    CCP1CONbits.CCP1M=0b1111;
    ANSELCbits.ANSC2=0;
    TRISCbits.TRISC2=0;

}
void pwm_start(unsigned int duty){
    unsigned int pwm_val=(duty*4*(PR2+1))/100;
    CCP1CONbits.DC1B=pwm_val&0x03;
    CCPR1L=pwm_val>>2;
}
void main() 
{   

    init_pwm();
    
    while(1){
     pwm_start(20);
     __delay_ms(1000);
     pwm_start(40);
     __delay_ms(1000);
     pwm_start(60);
     __delay_ms(1000);
     
    }

}
