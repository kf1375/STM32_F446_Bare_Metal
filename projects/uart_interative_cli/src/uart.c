#include "uart.h"

void UART_Init(void)
{
    /*
        USART2 Pins:
            PA2 ----> Tx
            PA3 ----> Rx
    */

    // Before we can use Port.A (PA) clock must be enable to it. 
    __setbit(RCC->AHB1ENR, 0);   

    // Pins Output Type: Push Pull
    __clearbit(GPIOA->OTYPER, 10);
    __clearbit(GPIOA->OTYPER, 11);
    
    // Set Pins speed to medium.
    /* ------ for PA2 ------ */
    __setbit(GPIOA->OSPEEDR, 4);
    __clearbit(GPIOA->OSPEEDR, 5);
    /* ------ for PA3 ------ */
    __setbit(GPIOA->OSPEEDR, 6);
    __clearbit(GPIOA->OSPEEDR, 7);

    // Idle state is high in UART so enabling the internal pull_up
    /* ------ for PA2 ------ */
    __setbit(GPIOA->PUPDR, 4);
    __clearbit(GPIOA->PUPDR, 5);
 
    /* ------ for PA3 ------ */
    __setbit(GPIOA->PUPDR, 6);
    __clearbit(GPIOA->PUPDR, 7);


    /*
        Now GPIO module and Pins states are set according to UART, 
        next thing is to connect GPIO pins to UART as an alternate function
    */

    // Configure GPIO Pins as alternate function
    /* ------ for PA2 ------ */
    __clearbit(GPIOA->MODER, 4);
    __setbit(GPIOA->MODER, 5);
 
    /* ------ for PA3 ------ */
    __clearbit(GPIOA->MODER, 6);
    __setbit(GPIOA->MODER, 7);

    // Connect PA2 Pin to USART. AF7 (UART2 Function)
    __setbit(GPIOA->AFR[0], 8);
    __setbit(GPIOA->AFR[0], 9);
    __setbit(GPIOA->AFR[0], 10);    
    __clearbit(GPIOA->AFR[0], 11);

    // Connect PA3 Pin to USART. AF7 (UART2 Function)
    __setbit(GPIOA->AFR[0], 12);
    __setbit(GPIOA->AFR[0], 13);
    __setbit(GPIOA->AFR[0], 14);
    __clearbit(GPIOA->AFR[0], 15);

    /*
        Now GPIO state is set and connected to USART Module
        The final step is to Configure USART Moduele
    */

    // Before we can use UART2, clock must be enable to it.  
    __setbit(RCC->APB1ENR, 17);

    /*
        By default the clock to USART2 is High Speed Internal clock 
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
    USART2->BRR = 0x683;

    // Disable Hardware Flow Control
    __clearbit(USART2->CR2, 8);
    __clearbit(USART2->CR2, 9);

    // 1-start bit, 8-bit data
    __clearbit(USART2->CR1 , 12);

    // 1-stop bit
    __clearbit(USART2->CR2 , 12);
    __clearbit(USART2->CR2 , 13);
    
    // No Parity bit
    __clearbit(USART2->CR1 , 10);
    
    // Enable both data Transmission and Reception
    __setbit(USART2->CR1 , 2);
    __setbit(USART2->CR1 , 3);

    // Finally powerup USART2 module
    __setbit(USART2->CR1 , 13);  

    // enable Rx interrupt
    __setbit(USART2->CR1,5);
    
    // Allow NVIC to acknowledge USART2 interrupt
    NVIC_EnableIRQ(USART2_IRQn);
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
    USART2->DR = ch;
    
    // Wait until the data is transmitted
    while ( __getbit(USART2->SR, 7) != 1); 
}

void USART2_IRQHandler (void)
{  
  
}