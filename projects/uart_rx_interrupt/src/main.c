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
#include "uart.h"
#include "logger.h"

LogEntry infoLogBuffer[LOG_MAX_ENTRIES];
LogEntry warningLogBuffer[LOG_MAX_ENTRIES];
LogEntry errorLogBuffer[LOG_MAX_ENTRIES];
LogEntry criticalLogBuffer[LOG_MAX_ENTRIES];

uint8_t infoLogIndex = 0;
uint8_t warningLogIndex = 0;
uint8_t errorLogIndex = 0;
uint8_t criticalLogIndex = 0;

char logOutput[LOG_OUTPUT_LENGHT];

/*************************************************
* main code starts from here
*************************************************/
int main(void)
{
    UART_Init();

    logger(LOG_INFO, 1, "Jinx");
    logger(LOG_INFO, 2, "Hey Dude");

    while(1)
    {

    }
}
