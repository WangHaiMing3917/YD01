#ifndef _PROTOCOL_TYPEDEF_H_
#define _PROTOCOL_TYPEDEF_H_



#include "stdint.h"

enum{

   Tx_Idle=0,
   Tx_Request,
   Tx_Delayed,
   Tx_WaitAck,
   Tx_WaitComplete,
   Tx_Repeat,

};


typedef struct{

  uint8_t   Rx_Start             :1u;
  uint8_t   Rx_Complete          :1u;
  uint8_t   wait_send_start      :1u;
//  uint8_t   use_cache_data       :1u;
  uint8_t   idle                 :5u;
  uint8_t   Tx_State;
  uint8_t   Rx_State;
  uint8_t   idle3;
  
  uint8_t   send_max;
  uint8_t   send_count; 
  uint8_t   Tx_Delays;
  uint8_t   Rx_Delays; 
    
  uint16_t  length;
  uint16_t  tx_count;
    
  uint16_t  rx_count; 
  uint8_t   DataGoroupsNumber;
  
  uint8_t   wait_feedback_type;
  uint8_t   wait_feedback_type_cache;
  uint16_t  connect_wifi_time_out;
  uint16_t  lengthcache;

  char      TxBuf[512];
  char      RxBuf[520];
  char      TxBufCache[512];
}SEARIL_STRUCT;
extern SEARIL_STRUCT  Searil;

enum{
  
  none=0,
  Set_Properties,
  Get_Properties,


};







#endif
