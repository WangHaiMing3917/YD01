#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "stdint.h"
#include "system_extern.h"


void Channel_ALL_OFF(void);
void Channel_Control(uint8_t index,uint8_t state,uint8_t flag);
void Channel_ALL_ON(void);
void Channel_Mode_Changed(void);

typedef struct{
   
   GPIO_t*  port_t;
   uint16_t   pin;
   
}RELAY_STRUCT;


#endif
