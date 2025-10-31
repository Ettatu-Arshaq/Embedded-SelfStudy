/*
 * File:   eep_uart.c
 * Author: Arsha
 * Target: PIC16F877A @ 4MHz
 */

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 4000000

// CONFIG
#pragma config FOSC = HS        // High Speed Oscillator
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

// ===== EEPROM FUNCTIONS =====
void eep_write(unsigned char addr, unsigned char data) {
    EEADR = addr;
    EEDATA = data;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    while (EECON1bits.WR);
    EECON1bits.WREN = 0;
}

unsigned char eep_read(unsigned char addr) {
    EEADR = addr;
    EECON1bits.RD = 1;
    while (EECON1bits.RD);
    return (EEDATA);
}

// ===== UART FUNCTIONS =====
void uart_init() {
    TRISC6 = 0;  // TX
    TRISC7 = 1;  // RX
    SPBRG = 25;  // Baud rate 9600 @4MHz
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;
}

void uart_tx(char data) {
    while (!TXSTAbits.TRMT);
    TXREG = data;
}

void uart_send_string(const char *s) {
    while (*s) {
        uart_tx(*s++);
    }
}

char uart_rx() {
    while (!PIR1bits.RCIF);
    return RCREG;
}
unsigned char read_hex() {
    char h = uart_rx();
    char l = uart_rx();
    unsigned char hi = (h <= '9') ? h - '0' : (h - 'A' + 10);
    unsigned char lo = (l <= '9') ? l - '0' : (l - 'A' + 10);
    return (hi << 4) | lo;
}


// ===== MAIN =====
void main(void) {
    unsigned char cmd, addr, data, value;
    char hexstr[10];

    uart_init();
    uart_send_string("\r\nEEPROM UART Ready\r\n");

    while (1) {
        cmd = uart_rx();

        if (cmd == 'W' || cmd == 'w') {       // Write Command
            uart_rx(); // space
            addr=read_hex();
            uart_rx(); // space
            data=read_hex();
            eep_write(addr, data);
            uart_send_string("\r\nW OK\r\n");
        }

        else if (cmd == 'R' || cmd == 'r') {  // Read Command
            uart_rx(); // space
            addr=read_hex();
            value = eep_read(addr);
            sprintf(hexstr, "\r\nDATA: %02X\r\n", value);
            uart_send_string(hexstr);
        }
    }
}
