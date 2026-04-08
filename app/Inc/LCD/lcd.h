#ifndef _LCD_H_
#define _LCD_H_


#include "lcd_typedef.h"

void Lcd_PowerOn_Display(void);
void Lcd_Display(void);
void Lcd_Channel_Fast_Flash_Timer(void);
void Lcd_Disp_Channel(uint8_t channel);
void Lcd_Fast_Disp_Channel_Into(uint8_t times,uint16_t delays);
void Lcd_Fast_Disp_Channel_Out(void);
void Lcd_Fast_Disp_Channel_Delays_Set(uint16_t delays);
void Lcd_disp_lock_flash_timer(void);
void lcd_disp_flash(uint8_t times);
void Lcd_Disp_Wifi_state(uint8_t state);
void Lcd_Channel_State_Change_Fast_Flash(uint8_t times );
void Lcd_Channel_StateFlash_Timer(void);
void Lcd_Wifi_disp_set(uint8_t on_off);
 void Lcd_BackLight_Open(void);











#endif



