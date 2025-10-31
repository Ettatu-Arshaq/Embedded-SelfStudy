/*
 * File:   newmain.c
 * Author: arsha
 *
 * Created on October 6, 2025, 11:22 AM
 */


#include <xc.h>
#define _XTAL_FREQ  4000000

void eep_write(unsigned char addr,unsigned char data){
    EEADR=addr;
    EEDATA=data;
    EECON1bits.WREN=1;
    INTCONbits.GIE=0;
    EECON2=0x55;
    EECON2=0xAA;
    EECON1bits.WR=1;
    INTCONbits.GIE=1;
    while(EECON1bits.WR);
    EECON1bits.WREN=0;
    }
unsigned char eep_read(unsigned char addr){
    EEADR=addr;
    EECON1bits.RD=1;
    while(EECON1bits.RD);
    return(EEDATA);
    }

void main(void) {
//    ADCON1=0x07;
    TRISB=0;
    eep_write(0x00,0xAA);
    __delay_ms(10);
    unsigned char val=eep_read(0x00);
    PORTB=val;
    while(1);
}
