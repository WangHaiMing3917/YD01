#ifndef _BSP_H_
#define _BSP_H_

#include "ciu32l051.h"


#include "bsp_lcd.h"
#include "stdlib.h"
#include "product_name.h"


void Bsp_Init(void);
void Bsp_Key_Gpio_Init(void);
void Bsp_SystemClock_Config(void);

void Bsp_IWDG_Init(void);
void Bsp_IWDG_ReFresh(void);

void Bsp_RTC_Init(void);

void Bsp_Disp_A(uint8_t pos);
void Bsp_Disp_B(uint8_t pos);
void Bsp_Disp_C(uint8_t pos);
void Bsp_Disp_D(uint8_t pos);
void Bsp_Disp_E(uint8_t pos);
void Bsp_Disp_F(uint8_t pos);
void Bsp_Disp_G(uint8_t pos);

void Bsp_Disp_Monday(void);
void Bsp_Disp_Tuesday(void);
void Bsp_Disp_Wednesday(void);
void Bsp_Disp_Thursday(void);
void Bsp_Disp_Friday(void);
void Bsp_Disp_Saturday(void);
void Bsp_Disp_Sunday(void);
void Bsp_Disp_Bluetooth(void);
void Bsp_Disp_TimingOpen(void);
void Bsp_Disp_TimingClose(void);
void Bsp_Disp_TimingAuto(void);
void Bsp_Disp_Lock(void);
void Bsp_Write_To_LCD_RAM(uint32_t *data);
void Bsp_Disp_All(void);
void Bsp_Clear_Lcd_Ram_Arrary(void);
void Bsp_Disp_Col(void);
void Bsp_Disp_ASCII_A(uint8_t Pos);
void Bsp_Disp_ASCII_B(uint8_t Pos);
void Bsp_Disp_ASCII_C(uint8_t Pos);
void Bsp_Disp_ASCII_D(uint8_t Pos);
void Bsp_Disp_ASCII_E(uint8_t Pos);
void Bsp_Disp_ASCII_F(uint8_t Pos);
void Bsp_Disp_ASCII_G(uint8_t Pos);
void Bsp_Disp_ASCII_H(uint8_t Pos);
void Bsp_Disp_ASCII_I(uint8_t Pos);
void Bsp_Disp_ASCII_J(uint8_t Pos);
void Bsp_Disp_ASCII_K(uint8_t Pos);
void Bsp_Disp_ASCII_L(uint8_t Pos);
void Bsp_Disp_ASCII_M(uint8_t Pos);
void Bsp_Disp_ASCII_N(uint8_t Pos);
void Bsp_Disp_ASCII_O(uint8_t Pos);
void Bsp_Disp_ASCII_P(uint8_t Pos);
void Bsp_Disp_ASCII_Q(uint8_t Pos);
void Bsp_Disp_ASCII_R(uint8_t Pos);
void Bsp_Disp_ASCII_S(uint8_t Pos);
void Bsp_Disp_ASCII_T(uint8_t Pos);
void Bsp_Disp_ASCII_U(uint8_t Pos);
void Bsp_Disp_ASCII_V(uint8_t Pos);
void Bsp_Disp_ASCII_W(uint8_t Pos);
void Bsp_Disp_ASCII_X(uint8_t Pos);
void Bsp_Disp_ASCII_Y(uint8_t Pos);
void Bsp_Disp_ASCII_Z(uint8_t Pos);


uint8_t Bsp_Hour_Key_Read(void);
uint8_t Bsp_Mode_Key_Read(void);
uint8_t Bsp_Timing_Key_Read(void);
uint8_t Bsp_Weeks_Key_Read(void);
uint8_t Bsp_Minutes_Key_Read(void);

void Bsp_Key_Exit_Disable(void);
void Bsp_Key_Exit_Enable(void);
 
void Bsp_Relays_Channel_Init(uint8_t Channel_Count);

void Bsp_Lptime1_Enable(void);
void Bsp_Lptime1_Disable(void);
void Bsp_LpTimer_Init(void);

void Bsp_Gpio_Init(void);
uint8_t Bsp_Power_Down_Scan(void);
void Bsp_Usart_Init(void);
void Bsp_Usart_DeInit(void);

void Bsp_Time8_Init(void);
void Bsp_Time8_Deinit(void);
void Bsp_Tim3_Init(void);
void Bsp_Time3_Deinit(void);

void Bsp_Erase_Page(uint8_t PageNumber,uint8_t length);
void Bsp_Write_Flash_Word(uint32_t Address,uint32_t *Buff,uint16_t length);

extern void Bsp_Wifi_Io_Init(void);
extern void Bsp_ChannelMode_Init(void);
extern uint8_t Bsp_ChannelMode_Detect(void);
extern void Bsp_Gpio_Init(void);
extern void Bsp_Back_Light_Open(void);
extern void Bsp_Back_Light_Close(void);
extern void Bsp_Relays_Channel_Init(uint8_t Channel_Count);


void Bsp_Relays_Open(GPIO_t* gpiox, uint32_t pin_mask);
void Bsp_Relays_Close(GPIO_t* gpiox, uint32_t pin_mask);

void Bsp_Back_Light_Close(void);
void Bsp_Back_Light_Open(void);

extern void Bsp_Power_Down_Exit_Init(void);
void Bsp_Power_Down_Exit_Deint(void);


#pragma anon_unions

#endif
