#ifndef MYUSART_H
#define MYUSART_H

#include "stm32f10x.h"

void myUsartWrite(USART_TypeDef * usart, char s);
void myUsartInit(USART_TypeDef * usart);

#endif
