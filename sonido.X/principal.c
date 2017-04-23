/*
 * File:   principal.c
 * Author: luis luciano
 *
 * Created on 21 de abril de 2015, 09:12 PM
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
#define LIMITE_10 65521
#define DO 0
#define DOS 1
#define REB 1
#define RE 2
#define RES 3
#define MIB 3
#define MI 4
#define FA 5
#define FAS 6
#define SOLB 6
#define SOL 7
#define SOLS 8
#define LAB 8
#define LA 9
#define LAS 10
#define SIB 10
#define SI 11


int notas[]={
15289, // DO
14430, // DO#
13620, // RE
12856, // RE#
12134, // MI
11453, // FA
10810, // FA#
10204, // SOL
9631,  // SOL#
9090,  // LA
8580,  // LA#
8099   // SI
};
unsigned int timer1;
unsigned long veces;
void setup(){
    OSCCONbits.IRCF=15;
    ANSELAbits.ANSA0=0;
    TRISAbits.TRISA0=0;
    PORTAbits.RA0=0;
    T1CONbits.TMR1CS=0;
    T1CONbits.T1CKPS=0;
    T1GCONbits.TMR1GE=1;
    T1CONbits.TMR1ON=0;
    PIR1bits.TMR1IF=0;
}



void play(unsigned char nota,unsigned char octava,unsigned int tiempoms){
    unsigned int tmp=notas[nota]>>octava;
    timer1=LIMITE_10-(tmp-10)*4;
    veces=((unsigned long)tiempoms*1000)/tmp;
    TMR1L=timer1&0x00ff;
    TMR1H=(timer1&0xff00)>>8;
    PIR1bits.TMR1IF=0;
    T1CONbits.TMR1ON=1;
    while(veces>0){
        if(PIR1bits.TMR1IF){
            PORTAbits.RA0=~PORTAbits.RA0;
            veces--;
            TMR1L=timer1&0x00ff;
            TMR1H=(timer1&0xff00)>>8;
            PIR1bits.TMR1IF=0;
        }
    }
    T1CONbits.TMR1ON=0;
    PORTAbits.RA0=0;
}
void loop(){
    unsigned char i;
    while(1)
    {
        play(MI,4,500); //TETRIS THEME 
        play(SI,3,250);
        play(DO,4,250);
        play(RE,4,250);

        play(MI,4,125);
        play(RE,4,125);
        play(DO,4,250);
        play(SI,3,250);
        play(LA,3,500);//9
        play(LA,3,250);
        play(DO,4,250);
        play(MI,4,500);//12

        play(RE,4,250);
        play(DO,4,250);
        play(SI,3,500);

        play(SI,3,250);
        play(DO,4,250);
        play(RE,4,500);

        play(MI,4,500);

        play(DO,4,500);

        play(LA,3,500);

        play(LA,3,1000);

        play(RE,4,500);

        play(RE,4,250);
        play(FA,4,250);
        play(LA,4,500);

        play(SOL,4,250);
        play(FA,4,250);
        play(MI,4,500);

        play(MI,4,250);
        play(DO,4,250);
        play(MI,4,500);

        play(RE,4,250);
        play(DO,4,250);
        play(SI,3,500);

        play(SI,3,250);
        play(DO,4,250);
        play(RE,4,500);

        play(MI,4,500);

        play(DO,4,500);

        play(LA,3,500);

        play(LA,3,1000);
    }
}
void main(void) {
    setup();
    loop();
    return;
}
