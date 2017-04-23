/*
 * File:   usart.c
 * Author: gustavo
 *
 * Created on 14 de mayo de 2014, 10:16
 */

#include <xc.h>
#include "eusart.h"

void openEUSART(){  // Abre puerto para enviar y recibir datos
    TXSTA=0;
    RCSTA=0;
    TXSTAbits.SYNC=0;
    TXSTAbits.BRGH=1;
    BAUDCONbits.BRG16=1;
    RCSTAbits.RX9D=0;
    SPBRG=25;
    PIR1bits.RCIF=0;
    PIR1bits.TXIF=0;
    RCSTAbits.SPEN=1;
    TXSTAbits.TXEN=1;
    RCSTAbits.CREN=1;
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
}

void closeEUSART(){
    RCSTAbits.SPEN=0;RCSTAbits.CREN=0;
    TXSTAbits.TXEN=0;
}

char busyEUSART(){
    if(!TXSTAbits.TRMT)
        return 1;
    return 0;
}

char readEUSART(){
    char data;
    data=RCREG;
    return data;
}

void writeEUSART(char data){
    TXREG=data;
}

void putsEUSART(char * buffer){
    do{
       while(busyEUSART());
       writeEUSART(*buffer);
    }while(*buffer++);
}

char dataRdyEUSART(){
    return PIR1bits.RCIF;
}
