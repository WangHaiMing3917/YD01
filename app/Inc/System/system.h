#ifndef _SYSTEM_H_
#define _SYSTEM_H_



#include "bsp.h"
#include "lcd.h"
#include "Key.h"
#include "Channel.h"
#include "timing.h"
#include "lptimer.h"
#include "protocol.h"
#include "upgrade.h"
#include "usart.h"
#include "Sleep.h"
#include "factory.h"
#include "system_const.h"
#include "system_info.h"
#include "system_typedef.h"

extern const uint8_t file_name[16u];
extern const char model_name[50];
extern const uint16_t VERSION ;



void System_PowerOn_Process(void);
void System_Mode_Set(uint8_t mode);
uint8_t System_Mode_Read(void);

void Current_Clock_Init(void);
void System_TimeOut_Clear(void);

void System_TimeOut_Set(uint16_t times);

void System_Out_Current_TimeSet(void);

void System_PowerOn_Voltage_Detect(void);
void System_PowerOn_ConfigModel(void);

void Searil_Timer(void);

char System_Number_To_ASSIIC(uint8_t number);

uint8_t System_Char_To_Number(char data);

uint16_t Crc16_Cal(uint8_t *data, uint16_t length);

void Jump_Process(void);
void System_1ms_Timer(void);
void System_Enable_Send_Get_Down(void);
void System_Disable_Send_Get_Down(void);
void System_Factory_Disp_Timer(void);
void System_Connect_Wifi_Process(void);
void System_PowerDown_Exit_Config(void);
void System_PowerDown_Exit_Deint(void);

void Power_Down_State_Process(void);
void Power_Down_Restore(void);

void System_Back_Led_Close(void);
void System_Back_Led_Open(void);
void PowerDown_FroceSaveInfo(void);
void System_PowerState_Change_HardwareProcess(void);
uint8_t Zeller(int years,int month,int day);
void System_Wifi_Connect_DeInit(void);
void System_PowerDown_UpdateStateProcess(void);
void System_Properties_Change_Cal(uint8_t Index,uint8_t state);
#endif



