#include "uart.h"
#include "parser.h"

extern char rxBuffer[MAX_INPUT_SIZE];
extern volatile uint8_t line_received;

uint16_t rxIndex = 0;

void UART_Init(void)
{
    /*
        UART4 Pins:
            PA0 ----> Tx
            PA1 ----> Rx
    */

    // Before we can use Port.A (PA) clock must be enable to it. 
    __setbit(RCC->AHB1ENR, 0);   

    // Pins Output Type: Push Pull
    __clearbit(GPIOA->OTYPER, 0);
    __clearbit(GPIOA->OTYPER, 1);
    
    // Set Pins speed to medium.
    /* ------ for PA2 ------ */
    __setbit(GPIOA->OSPEEDR, 0);
    __clearbit(GPIOA->OSPEEDR, 1);
    /* ------ for PA3 ------ */
    __setbit(GPIOA->OSPEEDR, 2);
    __clearbit(GPIOA->OSPEEDR, 3);

    // Idle state is high in UART so enabling the internal pull_up
    /* ------ for PA2 ------ */
    __setbit(GPIOA->PUPDR, 0);
    __clearbit(GPIOA->PUPDR, 1);
 
    /* ------ for PA3 ------ */
    __setbit(GPIOA->PUPDR, 2);
    __clearbit(GPIOA->PUPDR, 3);


    /*
        Now GPIO module and Pins states are set according to UART, 
        next thing is to connect GPIO pins to UART as an alternate function
    */

    // Configure GPIO Pins as alternate function
    /* ------ for PA2 ------ */
    __clearbit(GPIOA->MODER, 0);
    __setbit(GPIOA->MODER, 1);
 
    /* ------ for PA3 ------ */
    __clearbit(GPIOA->MODER, 2);
    __setbit(GPIOA->MODER, 3);

    // Connect PA2 Pin to USART. AF7 (UART4 Function)
    __clearbit(GPIOA->AFR[0], 0);
    __clearbit(GPIOA->AFR[0], 1);
    __clearbit(GPIOA->AFR[0], 2);    
    __setbit(GPIOA->AFR[0], 3);

    // Connect PA3 Pin to USART. AF7 (UART4 Function)
    __clearbit(GPIOA->AFR[0], 4);
    __clearbit(GPIOA->AFR[0], 5);
    __clearbit(GPIOA->AFR[0], 6);
    __setbit(GPIOA->AFR[0], 7);

    /*
        Now GPIO state is set and connected to USART Module
        The final step is to Configure USART Moduele
    */

    // Before we can use UART4, clock must be enable to it.  
    __setbit(RCC->APB1ENR, 19);

    /*
        By default the clock to UART4 is High Speed Internal clock 
        HSI = 16Mhz
        
        Baudrate =  Fclk/ 8 x ( 2 - Over8 ) x USARTDIV
        
        OR

        USARTDIV =  Fclk/ 8 x ( 2 - Over8 ) x Baudrate

        Fclk = 16000000Hz
        
        Over8 = 0
        
        Required BR = 9600
        
        USARTDIV =  16000000 / 8 x ( 2 - 0 ) x 9600
        
        USARTDIV =  104.1666
        
        Fraction Part:  16 x 0.1666 = 2.656 ~= 3
        Mantissa:       104 = 0x68
        
        USART_BRR = Mantissa << 4 | Fraction
        
        USART_BRR = 0x683
        
        USART_BRR = 11010000011
    */
    UART4->BRR = 0x683;

    // Disable Hardware Flow Control
    // __clearbit(UART4->CR2, 8);
    // __clearbit(UART4->CR2, 9);

    // 1-start bit, 8-bit data
    __clearbit(UART4->CR1 , 12);
    
    // No Parity bit
    __clearbit(UART4->CR1 , 10);
    
    // Enable both data Transmission and Reception
    __setbit(UART4->CR1 , 2);
    __setbit(UART4->CR1 , 3);

    // Finally powerup UART4 module
    __setbit(UART4->CR1 , 13);  

    // enable Rx interrupt
    __setbit(UART4->CR1, 5);
    
    // Allow NVIC to acknowledge UART4 interrupt
    NVIC_EnableIRQ(UART4_IRQn);
}

void UART_Transmit_String( char * buffer )
{
    volatile int i = 0;
    
    // Check Size 
    while ( buffer[i] != '\0' ) {
      put_char(buffer[i]);
      ++i;
    }
}

void put_char(uint32_t ch) 
{  
    UART4->DR = ch;
    
    // Wait until the data is transmitted
    while ( __getbit(UART4->SR, 7) != 1); 
}

void UART4_IRQHandler (void)
{
    if(UART4->SR & USART_SR_RXNE)
    {
        char received_char = (char) UART4->DR;
        if(received_char == '\n')
        {
            rxBuffer[rxIndex] = '\0';
            rxIndex = 0;
            line_received = 1;
        }
        else
        {
            rxBuffer[rxIndex] = received_char;
            rxIndex++;
        }
    }
}