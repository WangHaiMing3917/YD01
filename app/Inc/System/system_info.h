#ifndef _SYSTEM_INFO_H_
#define _SYSTEM_INFO_H_


#include "system_info_typedef.h"


#define  SYSTEM_INFO_ADDRESS     0x8001000
#define  SYSTEM_INFO_LENGTH      2048u
#define  SYSTEM_INFO_ENDADDRESS  0x80017FF

#define  UPDATE_ADDRESS          0x8008C00

#define  APP_START_ADDRESS       0x8001800

#define  APP_LENGHTH             0x7400

#define normal                   0u
#define update_into              1u
#define update_wait_check        2u
#define update_fail              3u
#define update_canle             4u
#define update_power_down        5u





#define MEMORY_MSP                 SYSTEM_INFO_ADDRESS     
#define MEMORY_CHANNEL_COUNT       MEMORY_MSP+1
#define MEMORY_STATE               MEMORY_CHANNEL_COUNT+1
#define MEMORY_ENDMSP              MEMORY_STATE+1


extern uint8_t SystemInfo_IsInitialized(void);
extern void SystemInfo_Memory_Init(void);
extern void SystemInfo_Save(void);
extern void System_Save_WriteToFlash(uint32_t addr,uint32_t *pdata,uint16_t length,erase_type_t erase_type);

extern void Check_Near_CurrentTime_Arrary(TIMING_INFO *Ch);
extern void SystemInfo_Init(void);

 
extern void SystemInfo_Relay_Count_Increase(uint8_t channel);




#endif
