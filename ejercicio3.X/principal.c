/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 29 de marzo de 2015, 10:10 PM
 */
#include <xc.h>
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

#define _XTAL_FREQ 500000 //CICLOS POR SEGUNDO, ES OBLIGATORIO CUANDO SE HACE DELAY
unsigned char i,select,ban;
/*
   Programa que lea los push button conectados al puerto A,
 * si lee el puerto RA0 avanzaran los leds de izquerda a derecha,
 * si lee el puerto RA1 avanzaran los leds de derecha a izquierda,
 * y si lee el puerto RA2 harán lo que se hizo en el programa anterior.
 */
void setup()
{
    ANSELB=0x00;
    TRISB=0x00;
    PORTBbits.RB0=0;
    PORTBbits.RB2=0;
    PORTBbits.RB3=0;
    //ENTRADA DE DATOS A TRAVES DEL PUERTO A
    ANSELAbits.ANSA0=0;
    ANSELAbits.ANSA1=0;
    ANSELAbits.ANSA2=0;

    TRISAbits.TRISA0=1; //
    TRISAbits.TRISA1=1;
    TRISAbits.TRISA2=1;
    PORTAbits.RA0=0;
    PORTAbits.RA1=0;
    PORTAbits.RA2=0;
    i=1;
    ban=0;
    select=0;
}

void loop()
{
    while(1)
    {
        if(PORTAbits.RA0||select==1) //Cuando se oprime el push button los lets van de izquierda a derecha
        {
           select=1;
           PORTB=i;
           i=i<<1;
           __delay_ms(50);
           if(i==0)
              i=1;
           if(PORTAbits.RA1)
              select=2;
           if(PORTAbits.RA2)
              select=3;
        }
        if(PORTAbits.RA1||select==2)//Cuando se oprime el push button los lets van de derecha a izquierda
        {
            select=2;
            PORTB=i;
            i=i>>1;
            __delay_ms(50);
            if(i==0)
               i=0x80;
            if(PORTAbits.RA0)
               select=1;
            if(PORTAbits.RA2)
               select=3;
        }
        if(PORTAbits.RA2||select==3)//Cuando se oprime el push button los lets van de izquierda a derecha >> derecha a izquierda
        {                              //(REBOTES)
            select=3;
            PORTB=i; //
            if(i==0x80)
               ban=1;
            else
               if(i==1)
               ban=0;

            if(ban==0)
               i=i<<1;
              else
               if(ban==1)
                  i=i>>1;
            __delay_ms(50);
            if(PORTAbits.RA0)
                select=1;
            if(PORTAbits.RA1)
                select=2;
        }
    }
}

void main(void)
{
    setup();
    loop();
    return;
}