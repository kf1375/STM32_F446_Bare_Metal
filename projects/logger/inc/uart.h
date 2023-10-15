#ifndef __UART_H
#define __UART_H

#include "main.h"

void UART_Init(void);
void UART_Transmit_String( char * buffer );
void put_char(uint32_t ch);

#endif /* __UART_H */