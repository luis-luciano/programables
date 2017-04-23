/*
 * File:   Control.c
 * Author: Viper
 *
 * Created on 22 de abril de 2015, 08:20 AM
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
signed char lugar;
unsigned char bandera;
unsigned char num[]={0x3,0x9F,0x25,0xD,0x99,0x49,0x41,0x1F,0x1,0x19};
void setup()
{
    lugar=9;
    ANSELB=0x00;
    TRISB=0x00;
    PORTB=num[lugar];//Inicia representando contador en 9

    //ENTRADA DE DATOS A TRAVES DEL PUERTO A
    //TRISA=0x00;
    TRISAbits.TRISA0=1;//boton de decremento ENTRADA
    TRISAbits.TRISA1=1;//boton de incremento ENTRADA
    TRISAbits.TRISA2=0; //SALIDA
    TRISAbits.TRISA3=0; //SALIDA
    TRISAbits.TRISA4=0;
    TRISAbits.TRISA5=0;
    TRISAbits.TRISA6=0;
    TRISAbits.TRISA7=0;
    ANSELA=0;
      
    PORTAbits.RA0=0;
    PORTAbits.RA1=0;
    PORTAbits.RA2=1;//Indica q hay espacios verde
    PORTAbits.RA3=0;
    PORTAbits.RA4=0;
    PORTAbits.RA5=0;
    PORTAbits.RA6=0;
    PORTAbits.RA7=0;
    bandera=0;
}

void loop()
{
    while(1)
    {
        if(PORTAbits.RA0&&lugar>=1 && lugar<=9)
        {
            PORTAbits.RA2=0;
            PORTAbits.RA3=1;
            PORTAbits.RA6=1;
            PORTAbits.RA7=0;
            __delay_ms(3000);
                
            PORTAbits.RA2=1;
            PORTAbits.RA6=0;
            PORTAbits.RA7=1;
            __delay_ms(3000);

            PORTAbits.RA6=0;
            PORTAbits.RA7=0;
            PORTAbits.RA3=0;
            PORTB=num[--lugar]; //Actualiza num en el display
        }

        if(lugar==0) //Si hay cero prende led rojo
        {
            PORTAbits.RA2=0;
            PORTAbits.RA3=1;
        }
        else
        {
            PORTAbits.RA2=1;
            PORTAbits.RA3=0;
        }

        if(PORTAbits.RA1&&lugar>=0 && lugar<=8)
        {
            PORTB=num[++lugar];
            PORTAbits.RA2=1;
            PORTAbits.RA3=0;
            PORTAbits.RA6=1;
            PORTAbits.RA7=0;
            __delay_ms(3000);

            PORTAbits.RA2=0;
            PORTAbits.RA6=0;
            PORTAbits.RA7=1;
            __delay_ms(3000);

            PORTAbits.RA6=0;
            PORTAbits.RA7=0;
            PORTAbits.RA3=1;
        } 
    }
}

void main(void)
{
    setup();
    loop();
    return;
}