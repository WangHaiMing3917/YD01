#ifndef _SLEEP_TYPEDEF_H_
#define _SLEEP_TYPEDEF_H_

#include "stdint.h"

typedef struct{
 
   uint8_t is_will_enable_lptime           :1u;
    uint8_t is_idle                        :7u;
   uint8_t wakeup_type;


}SLEEP_STRUCT;
extern SLEEP_STRUCT Sleep;








#endif
