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
#define _XTAL_FREQ  4000000
uint16_t result=0;
float Vin=0;

void uart_init(){
    //if using ISR() and use PIR1bits.RCIF/TXIF for checking)
//    PIE1bits.RCIE = 1;   // Enable UART receive interrupt
//    INTCONbits.PEIE = 1;  // Enable Peripheral Interrupts
//    INTCONbits.GIE = 1;   // Enable Global Interrupts

    OSCCON = 0x6A; // 4 MHz internal oscillator
    ANSELC=0;
    TRISCbits.TRISC6=0; //tx
    TRISCbits.TRISC7=1; //rx
    BAUDCONbits.SCKP=0;     //clock select polarity(non inv data)
    BAUDCONbits.BRG16=0;    //16 bit baudrate no->0
    RCSTAbits.SPEN=1;   // serial port enable Rx
    TXSTA=0x24;         // 0,0,TXEN=1,SYNC=0, 0,BRGH=1,0,0
    SPBRG=25;
}
void adc_init(){
    ANSELAbits.ANSA0=1; 
    TRISAbits.TRISA0=1;
    ADCON0=0x01;    //(0,CHS=00000,GO=0,ADON=1)
    ADCON1=0xF0;    //(ADFM=1,ADCS=1111,0,0,ADPREF=00)
}

void uart_write(char buffer[]){
    int len=0;
    while(buffer[len] != '\0') len++;
    
    for (int i=len-1;i>=0;i--){
//    PIR1bits.TXIF = 0;
    while(TXIF==0); 
    TXREG=buffer[i];
    }
    while(TXIF==0); 
    TXREG=32;
}

void uart_char(float v){
    char sndchar[20];
    int vint=v; 
    int vfloat=((v-vint)*100);
    int i=0;
    if (vfloat==0){
        sndchar[i]='0';
        i++;
        sndchar[i]='0';
        i++;
    }
    else{
        int vfl=vfloat;
        while(vfl>0){
        sndchar[i]=vfl%10 + 48;
        vfl/=10;
        i++ ;
        }
    }
    sndchar[i]='.';
    i++;    
    if (vint==0){
        sndchar[i]='0';
        i++;
    }
    else{
        int vintf=vint;
        while(vintf>0){
        sndchar[i]=vintf%10 + 48;
        vintf/=10;
        i++;
    }
    }

    sndchar[i]='\0';
    uart_write(sndchar);

}
void main(void) {
    adc_init();
    uart_init();
    ADCON0bits.GO=1;
    while(ADCON0bits.GO);
    result=((ADRESH<<8)|ADRESL);
//  Voltage Reading From ADC
    Vin=(result*5.0)/1023.0 ;
    uart_char(Vin);

    __delay_ms(500);
}
