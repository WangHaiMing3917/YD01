#ifndef _TIMING_TYPEDEF_H_
#define _TIMING_TYPEDEF_H_


#include "stdint.h"


    



typedef struct{

  uint8_t  Week;
  uint8_t  Hours;
  uint8_t  Minute;
  uint8_t  Sec;
  uint8_t  channel;
  uint8_t  Mode;  
}CURRENT_TIME_STRUCT;
extern CURRENT_TIME_STRUCT Current;




#endif

