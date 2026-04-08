#ifndef _BSP_H_


#include "ciu32l051.h"
#include "ciu32L051_std.h"
#include "product_name.h"


void Bsp_Init(void);
void Bsp_Other_Gpio_Init(void);


void Bsp_Flash_Read_Bytes(uint32_t Address,uint16_t Length,uint8_t *Buff);
void Bsp_Write_Flash_Word(uint32_t Address,uint32_t *Buff,uint16_t length);
void Bsp_Erase_Page(uint16_t PageNumber,uint8_t length);
void Bsp_Write_Flash_Bytes(uint32_t Address,uint16_t length,uint8_t *Buff);

void Bsp_IWDG_Init(void);
void Bsp_IWDG_ReFresh(void);

#endif


