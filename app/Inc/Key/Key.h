#ifndef _KEY_H_
#define _KEY_H_

#include "stdint.h"

#define KEY_MINUTES          0x01
#define KEY_TIMING           0x02
#define KEY_WEEKS            0x04
#define KEY_MODE             0x08
#define KEY_HOURS            0x10

#define HOLD_DELAYS_100Ms     100u
#define HOLD_DELAYS_200Ms     200u
#define HOLD_DELAYS_300Ms     300u
#define HOLD_DELAYS_400Ms     400u
#define HOLD_DELAYS_500Ms     500u
#define HOLD_DELAYS_600Ms     600u
#define HOLD_DELAYS_700Ms     700u
#define HOLD_DELAYS_800Ms     800u
#define HOLD_DELAYS_900Ms     900u
#define HOLD_DELAYS_1000Ms    1000u
#define HOLD_DELAYS_2000Ms    2000u



typedef struct{

  uint16_t Value;
  uint16_t Trg;
    
  uint16_t Release;
  uint16_t Delays;
    
  uint16_t Cache; 
  uint16_t CycPress_StartDelays;
    
  uint8_t  HoldFlag;
  uint8_t  Will_Check_Key;
  uint8_t  Key_Config_PuDown;
  uint8_t  Fast_Cnt;
    
  uint8_t  Cnt[5];    
  uint8_t  release_delays; 
}KEY_STRUCT;
extern KEY_STRUCT Key;

enum{

   hold_0=0,
   hold_start_100,
   hold_already_100,
   hold_start_300,
   hold_already_300,
   hold_start_500,
   hold_already_500,
   hold_start_600,
   hold_already_600,
   hold_start_1000,
   hold_already_1000,
   hold_start_2000,
   hold_already_2000,
   hold_start_3000,
   hold_already_3000,
   hold_start_9000,
   hold_already_9000,
   hold_start_other,
   hold_already_other,

};

void Key_Timer(void);
uint16_t Key_State_Read(void);
void Key_Value_Process(void);
void Is_Key_Press(void);
void Key_Scan(void);
void Key_Out_Sleep_Config(void);
void Key_Process(void);

uint8_t  Key_is_Locked(void);


#endif
