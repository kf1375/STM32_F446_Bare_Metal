/*
@author:    Kazem

@descp:     This Program implement a interactive command-line
            over UART2.
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
#include "parser.h"

char rxBuffer[MAX_INPUT_SIZE];
volatile uint8_t line_received = 0;
/*************************************************
* main code starts from here
*************************************************/
int main(void)
{
    Systick_Init(SystemCoreClock/1000);

    UART_Init();
    
    while(1)
    {
        if(line_received)
        {
            line_received = 0;
            process_command(rxBuffer);
        }
    }
}
