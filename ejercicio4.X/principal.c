/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 31 de marzo de 2015, 10:11 AM
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
/*
 * Programa que encienda el led conectado al puerto RB0
 * si un número en el sistema es múltiplo del 3, el número
 * se leerá en el puerto A, Puedes sustituir los push button
 * con dip switch, el número leído será de 4 bits.
 */
void setup()
{
    ANSELB=0x00;
    TRISB=0x00;
    PORTBbits.RB0=0;
    PORTBbits.RB2=0;
    PORTBbits.RB3=0;
    //ENTRADA DE DATOS A TRAVES DEL PUERTO A
    //TRISA >>Configuracion de las lineas del puerto A si se pone 0 indica salida, 1 indica entrada
    ANSELAbits.ANSA0=0;//configuracion 0 digital, 1 analogico
    ANSELAbits.ANSA1=0;
    ANSELAbits.ANSA2=0;
    ANSELAbits.ANSA3=0;

    TRISA=0x0F; //Indica los pines se son entradas
    PORTA=0x00;
}
void loop()
{
    while(1)
    {
         if(PORTAbits.RA0||PORTAbits.RA1||PORTAbits.RA2||PORTAbits.RA3)
        {
            if(PORTA%3==0)
               PORTB=1;
            else
               PORTB=0;
        }
    }
}
void main(void)
{
    setup();
    loop();
    return;
}