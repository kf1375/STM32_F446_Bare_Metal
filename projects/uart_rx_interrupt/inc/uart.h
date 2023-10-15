#ifndef __UART_H
#define __UART_H

#include "main.h"

void initUSART(void);
void put_char(uint32_t ch); 
void transmitString( char * buffer );

#endif /* __UART_H */