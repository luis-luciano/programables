/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 31 de marzo de 2015, 01:11 AM
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
unsigned char i,c;
void setup()
{
   ANSELB=0x00; //Analogico selecto
   TRISB =0x00; //direccion de datos iniciado en 0 o salida del puerto Registra en los datos
   i=0x3;
}
void loop()
{
    while(1)
    {
        PORTB=i;
        i=i<<2;
        i=i|3;
        __delay_ms(700);
        if(PORTBbits.RB7)
        {
           PORTB=0;
           __delay_ms(700);
           i=0x3;
        }
    }
}
void main(void)
{
    setup();
    loop();
    return;
}