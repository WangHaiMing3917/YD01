#ifndef _SYSTEM_INFO_H_
#define _SYSTEM_INFO_H_


#include "system_info_typedef.h"


#define  SYSTEM_INFO_ADDRESS     0x8001000
#define  SYSTEM_INFO_LENGTH      2048u
#define  SYSTEM_INFO_ENDADDRESS  0x80017FF

#define  UPDATE_ADDRESS          0x8008C00

#define  APP_START_ADDRESS       0x8001800

#define  APP_LENGHTH             0x7400




uint8_t SystemInfo_IsInitialized(void);

void System_Save_WriteToFlash(uint32_t addr,uint32_t *pdata,uint16_t length,erase_type_t erase_type);
void System_Memory_Init(void);

void SystemInfo_Save(void);









#endif
