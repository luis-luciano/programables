/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 30 de mayo de 2015, 03:01 PM
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

#define _XTAL_FREQ 1000000

void setup()
{
    OSCCONbits.IRCF=11; // Habilitar a 1 Mhz
    //Configurar como entradas analogicas RB0 Y RB1
    ANSELAbits.ANSA0=1; // Conf. ANSA0 con puerto analógico
    TRISAbits.TRISA0=1; // Conf. RA0 como puerto de input

    ANSELAbits.ANSA1=1;
    TRISAbits.TRISA1=1;
    PORTA=0x00;
    ANSELB=0x00;
    TRISB=0x00;
    PORTB=0x00;
    ADCON0bits.ADON=0; // Apagamos convertidor
    ADCON0bits.GO=0;  // Deshabilitamos convertidor
    ADCON1bits.ADFM=1; // Ajuste de resultado a la derecha
    ADCON1bits.ADCS=6; // Tiempo de conversión FOSC/64
    ADCON1bits.ADNREF=0; // Vref- conectado a tierra
    ADCON1bits.ADPREF=0; // Vref+ conectado a VCC

    ADRESL=0x00; // Inicializar registros
    ADRESH=0x00;
}

int convertir(int channel)
{
    int i=0;
    ADCON0bits.CHS=channel;//Seleciona el canal
    ADCON0bits.ADON=1; //Enciende convertidor ADC
    ADCON0bits.GO=1;  // Inicia la conversión
    __delay_ms(10);
    while(ADCON0bits.GO); // Sondeo de GO
    ADCON0bits.ADON=0; // Apagar convertidor ADC
    i=ADRESH;  // Recuperar resultado
    i=(i<<8)|ADRESL;
    return i;
}
int pos;
int neg;
float result;
void loop()
{
    while(1)
    {
        pos=convertir(0);
        neg=convertir(1);

       if(pos>neg)
           result=(pos-neg)/2f;
        else
             if(pos<neg)
                result=(neg-pos)/-2f;

       if(result>0f)
       {
           if(result>40f)
               PORTB=0b11111111;
           else
               PORTB=0b00000011;
       }
       else
           if(result<=0f)
           {
               if(result==0f)
                   PORTB=0;
               else
                   PORTB=0x80;
           }
    }
}

void main(void)
{
    setup();
    loop();
    return;
}