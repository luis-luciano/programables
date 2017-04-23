/* 
 * File:   eusart.h
 * Author: rherrera
 *
 * Created on 15 de abril de 2014, 05:56 PM
 */

#ifndef EUSART_H
#define	EUSART_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

void openEUSART(void);

void closeEUSART(void);

char busyEUSART(void);

char readEUSART(void);

void writeEUSART(char data);

void putsEUSART(char * buffer);

char dataRdyEUSART();

#endif	/* EUSART_H */

