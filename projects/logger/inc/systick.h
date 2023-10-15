#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "main.h"

void Systick_Init(uint32_t s);
uint32_t get_tick(void);
void delay_ms(uint32_t);


static volatile uint32_t tick;
static volatile uint32_t _tick;

#endif