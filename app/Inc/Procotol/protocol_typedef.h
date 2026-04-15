#ifndef _PROTOCOL_TYPEDEF_H_
#define _PROTOCOL_TYPEDEF_H_



#include "stdint.h"

typedef enum {
    
    INDEX_CMD_MODEL = 0,
    INDEX_CMD_BLE_CONFIG,
    INDEX_CMD_MCU_VERSION,
    INDEX_CMD_GET_DOWN,
    INDEX_CMD_RESULT,
    INDEX_CMD_ERROR,
    INDEX_CMD_PROPERTIES_CHANGED,
    INDEX_CMD_EVENT_OCCURED,
    INDEX_CMD_SET_PROPERTIES,
    INDEX_CMD_GET_PROPERTIES,
    INDEX_CMD_ACTION,
    INDEX_CMD_MIIO_NET_CHANGE,
    INDEX_CMD_UPDATE_FW,
    INDEX_CMD_ECHO,
    INDEX_CMD_BOOT_FAIL,
    INDEX_CMD_NET,
    INDEX_CMD_TIME,
    INDEX_CMD_MAC,
    INDEX_CMD_VERSION,
    INDEX_CMD_HELP,
    INDEX_CMD_TRUE,
    INDEX_CMD_FALSE,
    INDEX_CMD_RESTORE,
    INDEX_CMD_FACTORY,
    INDEX_CMD_RESULT_READY,
    INDEX_CMD_MAX_COUNT 
} CmdIndex;



enum{

   INFO_modle = 0,
   INFO_SerialNum,
    
};


typedef struct{

  uint8_t   Rx_Start             :1u;
  uint8_t   Rx_Complete          :1u;
  uint8_t   wait_send_start      :1u;
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
