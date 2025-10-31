/*
 * File:   newmain.c
 * Author: arshaq
 *
 * Created on October 5, 2025, 11:11 AM
 */
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
void uart_init(){
    OSCCON = 0x6A; // 4 MHz internal oscillator
    BAUDCONbits.SCKP=0;     //clock select polarity(non inv data)
    BAUDCONbits.BRG16=0;    //16 bit baudrate no->0
    RCSTAbits.SPEN=1;   // serial port enable Rx
    RCSTAbits.CREN = 1;  // Enable receiving Continuously
    TXSTA=0x24;         // 0,0,TXEN=1,SYNC=0, 0,BRGH=1,0,0
    SPBRG=25;



}
void uart_write(char a){
//        PIR1bits.TXIF = 0;
        while(TXIF==0); 
        TXREG=a;
    }

char uart_read(void){ 
    while(RCIF == 0);   // Wait until data is received
    return RCREG;        // Read and return received byte
}


void main(void) {
    uart_init();
    ANSELC=0;
    TRISCbits.TRISC1=0; //LED
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
#define led LATCbits.LATC1  //LED
    while(1){
    char a;
    a=uart_read() ;
    uart_write(a);
    if (a=='1'){
        led=1;
    }
    else led=0;
    }
}
