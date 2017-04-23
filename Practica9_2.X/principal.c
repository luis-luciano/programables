/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 1 de junio de 2015, 09:05 PM
 */


#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "eusart.h"
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

void setup()
{
    OSCCONbits.IRCF=11;
    openEUSART();
    TRISAbits.TRISA6=0;
    TRISAbits.TRISA7=0;
    ANSELA=0;
    PORTA=0x00;
}
unsigned char buffer[80];
unsigned int num;
void leerEusart()
{
    unsigned char c,i=0;
    do{
        while(!dataRdyEUSART());
        c=readEUSART();
        if(c=='\n')
            break;
        buffer[i++]=c;
    }while(1);
    buffer[i]=0;
    num=atoi(buffer);
}
int act=0;
void loop()
{
    while(1)
    {
        while(busyEUSART());
        putsEUSART(buffer);
        leerEusart();

        if(num==1&&act!=1)//derecha
        {
            act=1;
           PORTAbits.RA6=1;
           PORTAbits.RA7=0;
        }
        else
            if(num==2&&act!=2)//izquierda
            {
                act=2;
                PORTAbits.RA6=0;
                PORTAbits.RA7=1;
            }
            else
                if(num==3&&act!=3)//parar
            {
                PORTAbits.RA6=0;
                PORTAbits.RA7=0;
            }
    }
}

void main(void)
{
    setup();
    loop();
    return;
}