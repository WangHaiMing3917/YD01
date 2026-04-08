#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include <stdio.h>
#include <string.h>

#include "protocol_typedef.h"

extern const char cmd_model[];
extern const char cmd_ble_config[];
extern const char cmd_mcu_version[];
extern const char cmd_get_down[];
extern const char cmd_result[];
extern const char cmd_error[];
extern const char cmd_properties_changed[];
extern const char cmd_event_occured[];
extern const char cmd_set_properties[];
extern const char cmd_get_properties[];
extern const char cmd_action[];
extern const char cmd_miio_net_change[];
extern const char cmd_update_fw[];
extern const char cmd_echo[];
extern const char cmd_reboot;
extern const char cmd_restore[];
extern const char cmd_factory[];
extern const char cmd_net[];
extern const char cmd_time[];
extern const char cmd_mac[];
extern const char cmd_version[];
extern const char cmd_hellp[];


void Protocol_SerialTxCommProcess(void);
void Protocol_SerialRxCommProcess(void);

void Protocol_Process(void);
void Protocol_1ms_Timer(void);
//void Protocol_Timer_SendCmd(void);
void Protocol_Switch_Status(uint8_t On_Off,uint8_t channel);
void Protocol_TimingGroup_Set(char *temp,uint8_t ch);
void Protocol_Change_Mode(uint8_t mode,uint8_t channel);
//void Protocol_Send_Msg(char*data,uint16_t length,uint8_t send_times,uint8_t type);
void Protocol_Down_Set_Properties_Process(uint8_t group);

uint16_t Protocol_Start_Number(char *data);
void Protocol_Send_Boot_Fail(void);
void Protocol_Send_Restor(void);
void Protocol_Send_Cmd_Too_Long(void);
void Protocol_Send_Factory(void);
void Protocol_TxBuf_Fill(uint16_t length,uint8_t type);
void Protocol_Repet_Get_CurrentTime(void);
void Protocol_Msg_Send(void);
void Protocol_Send_Update_Ready(void);
void Protocol_Update_SendConfig(uint8_t sendcount,uint8_t sendmax,uint8_t tx_state);
void Protocol_Send_GetTime(void);
void Protocol_Cmd_Cache(uint8_t CmdCache);
void Protocol_Send_Properties_Changed(void);
void Protocol_Properties_Changed_Scan(void);
void Protocol_Cmd_Clear(void);
#endif
