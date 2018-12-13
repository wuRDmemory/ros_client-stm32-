#ifndef __USART3_H__
#define __USART3_H__

#include <stdint.h>

void Usart_Configuration(long baud);
char Usart_DataAvailable();
uint8_t Usart_Getch();
char Usart_FreeSpace();
char Usart_Putch(uint8_t data);


#endif
