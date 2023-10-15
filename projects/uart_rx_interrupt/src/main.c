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

/*************************************************
* main code starts from here
*************************************************/
int main(void)
{
    /* Each module is powered separately. In order to turn on a module
     * its relevant clock needs to be enabled first.
     * The clock enables are located at RCC module in the relevant bus registers
     * STM32F4-Discovery board LEDs are connected to GPIOD pins 12, 13, 14, 15.
     * All the GPIO are connected to AHB1 bus, so the relevant register for the
     * clocks is AHB1ENR.
     * More info in Chapter 7 - RCC in RM0090
     */

    /* Enable GPIOD clock (AHB1ENR: bit 3) */
    // AHB1ENR: XXXX XXXX XXXX XXXX XXXX XXXX XXXX 1XXX
    // RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    initUSART();
    put_char(100);
    // Note: |= means read the contents of the left operand, or it with
    //   the right operand and write the result back to the left operand

    // Another way to write a 1 to a bit location is to shift it that much
    // Meaning shift number 1, 3 times to the left. Which would result in
    // 0b1000 or 0x8
    // RCC->AHB1ENR |= (1U << 3);

    // We can also use the predefined directives from stm header to do the same thing.
    // RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    // RCC_AHB1ENR_GPIODEN here will expand to (1 << 3)

    /* Make Pin 12 output (MODER: bits 25:24) */
    // Each pin is represented with two bits on the MODER register
    // 00 - input (reset state)
    // 01 - output
    // 10 - alternate function
    // 11 - analog mode

    // We can leave the pin at default value to make it an input pin.
    // In order to make a pin output, we need to write 01 to the relevant
    // section in MODER register
    // We first need to AND it to reset them, then OR it to set them.
    //                     bit31                                         bit0
    // MODER register bits : xx xx xx 01 XX XX XX XX XX XX XX XX XX XX XX XX
    //                      p15      p12                                  p0

    // GPIOA->MODER &= 0xFCFFFFFF;   // Reset bits 25:24 to clear old values
    // GPIOA->MODER |= 0x01000000;   // Set MODER bits 25:24 to 01
    
    // GPIOA->MODER  &= ~(0x3 << (LED_PIN*2));
    // GPIOA->MODER  |=  (0x1 << (LED_PIN*2));
    // GPIOA->OTYPER &= ~(1 << LED_PIN);
    // We could also use a more systematic approach by shifting to bits
    // GPIOD->MODER &= ~(3U << 24);
    // GPIOD->MODER |=  (1U << 24);

    // Since each pin is represented with two bits, we needed to shift 24 times
    // to write to the bits related to pin 12 (times 2). We could change our code to
    // auto-calculate the relevant bit location.
    // GPIOD->MODER &= ~(3U << 2*12);
    // GPIOD->MODER |=  (1U << 2*12);

    // As a side note:
    // First AND operations to clear the bits is not really important for first
    // boot up setup, but if we ever want to change the pin behavior in the middle
    // of the code, we need to make sure it is cleared before writing it.

    /* We do not need to change the speed of the pins, leave them floating
     * and leave them as push-pull, so no need to touch OTYPER, OSPEEDR, and OPUPDR
     * However, if we want to use a open-drain required protocol (i.e. I2C), we need
     * to declare the pin as open-drain from OTYPER register
     */

    /* Set or clear pins (ODR: bit 12) */
    // Set pin 12 to 1 to turn on an LED
    // ODR: xxx1 XXXX XXXX XXXX
    // GPIOA->ODR |= (1U << LED_PIN);

    // With shifting
    // GPIOD->ODR |= (1U << 12);

    // the code should never leave its master loop, hence while(1) or for(;;)
    while(1)
    {
        // GPIOA->ODR ^= (1 << LED_PIN);
    }
}