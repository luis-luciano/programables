/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 14 de abril de 2015, 02:47 AM
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
unsigned char c,nlets,i,ini,ant;
void setup()
{
    ANSELB=0x00;
    TRISB=0x00;
    PORTB=0;
    ANSELAbits.ANSA0=0;
    ANSELAbits.ANSA1=0;
    ANSELAbits.ANSA2=0;
    TRISA=0x07; 
    PORTA=0x00;
    i=1;
}
void loop()
{
    while(1)
    {
        if(PORTA!=0)
          break;
        PORTB=i;
        i=i<<1;
        i=i|1;
        __delay_ms(1000);
        if(PORTBbits.RB6)
        {
            PORTB=0;
            i=1;
            __delay_ms(1000);
        }
    }
    while(1)
    {
       if(PORTAbits.RA0||PORTAbits.RA1||PORTAbits.RA2)
        {
             for(c=1,nlets=1;c<PORTA;c++)
             {
                 nlets=nlets<<1;
                 nlets=nlets|1;
             }
             ini=nlets;

             while(1)
             {
                 ant=PORTA;
                 if(nlets<=0x3F)
                 {
                     PORTB=nlets;
                     nlets=nlets<<PORTA;
                     nlets=nlets|ini;
                     __delay_ms(1000);
                     if(ant!=PORTA)
                         break;
                 }
                 else
                {
                    PORTB=0;
                    nlets=ini;
                    __delay_ms(1000);
                }
             }
        }
        else
            PORTB=0;
    }
}
void main(void)
{
    setup();
    loop();
    return;
}