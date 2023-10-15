/*
@author:    Kazem

@descp:     This Program configures USART2 for asynchronous
            communication with 9600 baudrate.
            PA2 ----> Tx
            PA3 ----> Rx
            
@Method:    Interrupt based reception

@warrenty:  void
*/
/**************************************************************
REQUIREMENTS:
    1. 9600 baud rate
    2. 8-bits data bits
    3. 1 start/stop bits
    4. No Parity    
***************************************************************/

/*  
    Web Link: 
*/

/*************************************************************
STEPS:
    1. Configure GPIOs to have alternate function
    2. Configure UART
    3. In ISR transmit back Data
*************************************************************/
#include "main.h"
#include "systick.h"
#include "uart.h"
#include "logger.h"

/*************************************************
* main code starts from here
*************************************************/
int main(void)
{
    Systick_Init(SystemCoreClock/1000);

    UART_Init();

    logger(LOG_INFO, 1, "This is an Info");
    logger(LOG_INFO, 2, "This is another Info");
    delay_ms(1000);
    logger(LOG_WARNING, 1, "This is a Warning");
    logger(LOG_WARNING, 2, "This is another Warning");
    delay_ms(1000);
    logger(LOG_ERROR, 1, "This is a Error");
    logger(LOG_ERROR, 2, "This is another Error");
    delay_ms(1000);
    
    while(1)
    {

    }
}
