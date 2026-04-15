#ifndef _FACTORY_TYPEDEF_H_
#define _FACTORY_TYPEDEF_H_

#include "stdint.h"


typedef struct{

    uint8_t  will_connect_wifi;         //wifi测试链接
    uint8_t  item;                      //工厂测试项目
    uint8_t  disp_item;                 //工厂显示测试项目
    uint8_t  key_item;                  //工厂按键测试项目
    uint16_t delays;
    uint16_t factory_check_net_delays; //
    uint16_t relays_count;
    
    uint8_t  channel;
    uint8_t  idle;
}FACTORY_STRUCT;
extern FACTORY_STRUCT factory;















#endif

