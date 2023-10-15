#ifndef __UART_H
#define __UART_H

#include "main.h"

void UART_Init(void);
void transmitString( char * buffer );
void put_char(uint32_t ch);

#endif /* __UART_H */