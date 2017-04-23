/*
 * File:   lcdprincipal.c
 * Author: rherrera
 *
 * Created on 1 de febrero de 2015, 08:43 PM
 */


#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 500000
#include "lcd.h"

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

void setup(){
 Lcd_Init();                     //inicializamos el lcd
 Lcd_Cmd(LCD_CLEAR);     //limpiamos lcd
 Lcd_Cmd(LCD_CURSOR_OFF);
 ANSELA=0x00;
 TRISA=0x01;
 PORTA=0x00;
}

unsigned int i=0;
char buffer[30];
void loop(){
 Lcd_Out(1,1,"Iniciando pulsa");
 Lcd_Out(2,4,"<BOTON>");
 while(1){
     if(PORTAbits.RA0)
     {
         while(PORTAbits.RA0);
         i++;
         Lcd_Cmd(LCD_CLEAR);
         sprintf(buffer,"Contador=%d",i);
         Lcd_Out2(1,1,buffer);
     }
 }
}
void main(void) {
    setup();
    loop();
    return;
}
