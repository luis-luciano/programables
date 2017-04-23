/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 04 de mayo de 2015, 08:26 PM
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
unsigned int c;
unsigned char estado,p,noche;
void setup()
{
    noche=0;
    ANSELAbits.ANSA0=0;
    ANSELAbits.ANSA1=0;
    ANSELAbits.ANSA2=0;
    TRISAbits.TRISA0=0;
    TRISAbits.TRISA1=0;
    TRISAbits.TRISA2=0; //ACTIVADO DE PINES DE SALIDA Y DIGITAL
    ANSELBbits.ANSB0=0;
    TRISBbits.TRISB0=1;
    ///configurar el registro para reloj interno
    OPTION_REGbits.T0CS=0;
    OPTION_REGbits.PSA=0;
    OPTION_REGbits.PS=0; //modifica el timer a una escala mayor o menor
    TMR0=8;
    c=0;
    p=0;
    PORTAbits.RA0=1; //INICIA EN VERDE
    PORTAbits.RA1=0; //AMARILLO
    estado=0;
    PORTAbits.RA2=0; //ROJO
    INTCONbits.GIE=1;  // Habilitar interrupciones
    INTCONbits.T0IE=1;
}
void parpadeo()
{
    while(1)
    {
        if(c==1250) //VERIFICA TIEMPO LIMITE DE COLOR VERDE PARPADEO -- 5 SEGUNDOS
        {
            p=0;   //DESACTIVA BANDERA DE PARPADEO
            break;
        }
    }
    estado=2;
    c=0;
    PORTAbits.RA0=0;  //APAGA VERDE
    PORTAbits.RA1=1; //ENCIENDE AMARILLO
}
void loop()
{
    while(1)//loop principal
    {
        if(c==7500&&estado==0) //VERIFICA LIMITE DE TIEMPO COLOR VERDE  -- 30 SEGUNDOS
        {
            PORTAbits.RA0=0;   //APAGA VERDE
            estado=1;
            p=1;              //IMPORTANTE PARA PARPADEO (ACTIVADO)
            c=0;
        }
        if(estado==1)         //ENTRA A REALIZAR PARPADEO
            parpadeo();
      
        if(c==1000&&estado==2) //VERIFICA LIMITE DE TIEMPO COLOR AMARILLO -- 4 SEGUNDOS
        {
            PORTAbits.RA1=0;  //APAGA AMARILLO
            PORTAbits.RA2=1;  //ENCIENDE ROJO
            estado=3;
            c=0;
        }
        if(c==3750&&estado==3) //VERIFICA LIMITE DE TIEMPO COLOR ROJO    -- 15 SEGUNDOS
        {
            PORTAbits.RA2=0;   //APAGA ROJO
            PORTAbits.RA0=1;   //ENCIENDE VERDE
            estado=0;
            c=0;
        }
    }
}
void interrupt miISR(void)
{
    INTCONbits.GIE=0;
    if(INTCONbits.T0IF)
    {
       INTCONbits.T0IF=0;
       TMR0=8;
       if(PORTBbits.RB0==1)
       {
           noche=1;
           PORTAbits.RA0=0;
           PORTAbits.RA2=0;
           PORTAbits.RA1=~PORTAbits.RA1;//parpadeo amarillo cuando detecta oscuridad
       }
       else if(PORTBbits.RB0==0&&noche==0)
       {
           if(p==1) //BANDERA ACTIVADA GENERA PARPADEO
              PORTAbits.RA0=~PORTAbits.RA0; //VERDE
           c++;
       }
       if(PORTBbits.RB0==0&&noche==1)
       {
           noche=0;
           c=0;
           PORTAbits.RA1=0;
           PORTAbits.RA0=1;
       }
    }
    INTCONbits.GIE=1;
}
void main(void)
{
    setup();
    loop();
    return;
}
