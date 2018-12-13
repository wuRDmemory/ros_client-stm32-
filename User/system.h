#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <stdint.h>

extern uint32_t runtime;

void System_Init(void);
void delay_ms(uint16_t msec);
uint32_t System_GetTime(void);

#endif
