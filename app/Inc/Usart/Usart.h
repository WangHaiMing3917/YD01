#ifndef _USART_H_
#define _USART_H_


#include "stdint.h"

#define REPETE_MAX_TIMES    1u



void Usart_Init(void);
void Usart_DeInit(void);
void Usart_DMA_Send(char *source,uint32_t number);





#endif
