#ifndef _BSP_LCD_TYPEDEF_H_
#define _BSP_LCD_TYPEDEF_H_

#include "stdint.h"
#include "system_extern.h"




typedef struct 
{
   uint32_t RAM0;
   uint32_t RAM1;
   uint32_t RAM2;
   uint32_t RAM3;
   
}LCD_RAM_ARRAY;
extern LCD_RAM_ARRAY LCD_ARRAY;


typedef struct{
   
   uint32_t ordef_number;     //ÐòºÅ
   GPIO_t*  port_t;
   en_gpio_pin_t   pin;
   
}LCD_SEG_COM_STRUCT;






#endif
