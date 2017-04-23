/*
 * File:   ledrgb.c
 * Author: toshiba
 *
 * Created on 8 de mayo de 2015, 01:37 PM
 */


#include <xc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is digital input)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 500000

void setup(){
    ANSELA=0x00;
    TRISA=0x00;
    PORTA=0x00;
    PORTAbits.RA0=0;
    PORTAbits.RA1=1;
    PORTAbits.RA2=1;
    PORTAbits.RA3=1;
    OPTION_REGbits.T0CS=0;
    OPTION_REGbits.PSA=0;
    OPTION_REGbits.PS=0;
    TMR0=6;
}
void loop(){
    while(1){
       /* PORTAbits.RA0=0; //Rojo
        __delay_ms(500);
        PORTAbits.RA0=1;
        __delay_ms(1500);
        PORTAbits.RA2=0; //Verde
        __delay_ms(500);
        PORTAbits.RA2=1;
        __delay_ms(1500);
        //PORTAbits.RA3=0;//Amarillo
        //PORTAbits.RA2=0;
        PORTAbits.RA0=0;
        PORTAbits.RA2=0;
        PORTAbits.RA3=0;
        __delay_ms(500);
        PORTAbits.RA2=1;
        PORTAbits.RA3=1;
        __delay_ms(1500);*/
        /* if(INTCONbits.T0IF)
        {
           INTCONbits.T0IF=0;
           TMR0=6;
           PORTAbits.RA0=~PORTAbits.RA0; //VERDE
        }*/
       /* PORTAbits.RA2=~PORTAbits.RA2;
        __delay_ms(1000);
    }
}
void main(void) {
    setup();
    loop();
    return;
}
