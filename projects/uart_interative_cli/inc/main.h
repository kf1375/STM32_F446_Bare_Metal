#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"

#define __setbit(___reg, ___bit)      ((___reg) |= (1U << (___bit)))
#define __clearbit(___reg, ___bit)    ((___reg) &= (~(1U << (___bit))))
#define __togglebit(___reg, ___bit)   ((___reg) ^= (1U << (___bit)))
#define __getbit(___reg, ___bit)      (((___reg) & (1U << (___bit))) >> (___bit))

/*************************************************
* function declarations
*************************************************/
int main(void);

#endif /* __MAIN_H */