#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "bsp.h"
#include "system_info.h"
#include "crc32.h"



#define normal               0u
#define update_into          1u
#define update_wait_check    2u
#define update_fail          3u
#define update_canle         4u
#define update_power_down    5u





void Jump_Process(void);
void System_Process(void);



#endif

