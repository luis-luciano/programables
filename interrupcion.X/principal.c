/*
 * File:   principal.c
 * Author: toshiba
 *
 * Created on 14 de abril de 2015, 08:35 AM
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
void setup()
{
    ANSELBbits.ANSB0=0;
    ANSELBbits.ANSB1=0;
    TRISBbits.TRISB0=1;
    TRISBbits.TRISB1=0;
    INTCONbits.GIE=1; //se habilita interrupcion general
    INTCONbits.INTE=1; //se habilita la interrucion externa
}

void loop()
{
    while(1);
}
void interrupt myISR()//manejador de interrupcion se ejecuta cada vez que una interrupcion sea activada
{
    INTCONbits.GIE=0;//deshabilitar la interrupcion general indica que no atendera a ninguna interrupcion
    //sondeo si la interrupcion del puerto ocurrio
    if(INTCONbits.INTF)
    {
        PORTBbits.RB1=~PORTBbits.RB1;
        INTCONbits.INTF=0; //regresar la bandera a 0
    }
    INTCONbits.GIE=1;//se activa
}
void main(void)
{
    setup();
    loop();
    return;
}
