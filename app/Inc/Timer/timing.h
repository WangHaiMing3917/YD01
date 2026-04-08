#ifndef _TIMING_H_
#define _TIMING_H_



#include "timing_typedef.h"





uint8_t Timing_Week_Mode_Selcet(uint8_t Num);
uint8_t Timing_Week_Mode_To_Number(uint8_t Mode);
void Timing_Action_Scan(void);
void Time_1ms_poll(void);




#endif


