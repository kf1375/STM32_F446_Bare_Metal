#include "systick.h"

void Systick_Init(uint32_t s)
{
    // Clear CTRL register
    SysTick->CTRL = 0x00000;
    // Main clock source is running with HSI by default which is at 16 mhz.
    // SysTick clock source can be set with CTRL register (Bit 2)
    // 0: Processor clock/8 (AHB/8)
    // 1: Processor clock (AHB)
    __setbit(SysTick->CTRL, 2);
    // Enable callback (bit 1)
    __setbit(SysTick->CTRL, 1);
    // Load the value
    SysTick->LOAD = (uint32_t)(s - 1);
    // Set the current value to 0
    SysTick->VAL = 0;
    // Enable SysTick (bit 0)
    __setbit(SysTick->CTRL, 0);
}

//ISR implementation
void SysTick_Handler(void)
{
    ++tick;
}

uint32_t get_tick(void)
{
    __disable_irq();
    _tick = tick;
    __enable_irq();
    return _tick;
}

//Delay generation
void delay_ms(uint32_t m_seconds)
{
    uint32_t temp = get_tick();
    while((get_tick() - temp) < m_seconds){} 
}
