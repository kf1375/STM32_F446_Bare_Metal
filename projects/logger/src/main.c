/*
@author:    Kazem

@descp:     This Program implement a simple logging modudle and 
            configures Systick and USART2 for streaming logs.
*/

/**************************************************************
REQUIREMENTS:
    1. 9600 baud rate
    2. 8-bits data bits
    3. 1 start/stop bits
    4. No Parity    
***************************************************************/

/*  
    Web Link: https://github.com/kf1375/STM32_F446_Bare_Metal/tree/main/projects/logger
*/

/*************************************************************
STEPS:
    1. Configure Systick to have milisecond timestamp
    2. Configure UART
    3. Set various logs and stream them over UART
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
