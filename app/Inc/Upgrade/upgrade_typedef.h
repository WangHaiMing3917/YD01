#ifndef _UPGRADE_TYPEDEF_H_
#define _UPGRADE_TYPEDEF_H_


#include "stdint.h"

#define MAX_REPECT_TIMES  

typedef struct{

  uint8_t  head;                      //头
  uint8_t  serialnumber;              //序号
  uint8_t  serialnumber_complement;   //序号补码     
  uint8_t  data[128];
    
  uint8_t  crc_h;
  uint8_t  crc_l;
  uint8_t  idle[3]; 
}XMODEM_STRUCT;



typedef struct{

  uint8_t  pack_number;
  uint8_t  pack_number_complement;
  uint8_t  pack_number_error;
  uint8_t  time_out_error; 
    
  uint8_t  crc_error;
  uint8_t  wait_send_eot_end;
  uint8_t  repet_count;
  uint8_t  wait_send_can_update   :1u;      //取消升级标志位
  uint8_t  is_idle                :7u;
    
  uint8_t  idle;  
  uint8_t  boot_fail_send_count;   
  uint16_t packs_count;  
    
  uint16_t time_out;                        //串口超时
  uint16_t wait_send_can_update_delays;
    
}UPDATE_STRUCT;

extern UPDATE_STRUCT Update;




#endif
