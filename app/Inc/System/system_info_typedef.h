#ifndef _SYSTEM_INFO_TYPEDEF_H_
#define _SYSTEM_INFO_TYPEDEF_H_

#include "stdint.h"


typedef union{
    
   uint8_t Buf[3];
    struct{
    
      uint8_t enable        :1u;  
      uint8_t week          :4u;
      uint8_t disp_none     :1u;
      uint8_t close         :1u;
      uint8_t idle          :1u;
        
      uint8_t hour;
        
      uint8_t minutes; 
    };
}TIMING_BASE_STRUCT;


typedef union{
  
    uint8_t Buf[169]; 
    struct{
      uint8_t Index              :3u;  //序号1-7
      uint8_t Timing_is_Valid    :1u;  //定时有效
      uint8_t Mode               :3u;  //模式开，关 自动
      uint8_t Relays_States      :1u;  //继电器状态
        
      TIMING_BASE_STRUCT  timing[56];  //56*3
    };

}TIMING_INFO;

typedef union{
    
   uint8_t Buf[1024u];
   struct{
       
      uint8_t     index;                     //0   0
      uint8_t     is_request_save;           //    1
      uint16_t    save_crc;                  //    2  3
    
      uint8_t     Msp;                       //1   4
      uint8_t     ChannelCount;              //    5
      uint8_t     system_state;              //    6
      uint8_t     wifi_in_factory;           //    7
    
      uint16_t    upgrade_pack_number;       //2   8  9
      uint16_t    crc16;                     //    10 11
       
      TIMING_INFO time_channel[5u];          //3   12 13 14 15
                                             //..........
                                             //213          855
                                             //    
                                             //    856   
      uint8_t     Current_Channel;           //    857
      uint8_t     update_count;              //    858
      uint8_t     keylocked;                 //214 859  
      uint8_t     time_enable_count[5];      //
      uint8_t     idle[138];                //..........   
      uint32_t    channel_count_index[5];   //256 1020 1021 1022
      uint8_t     endMsp;                    //    1023
   };

}SYSTEM_INFO_STRUCT;
 


extern SYSTEM_INFO_STRUCT SystemInfo;

typedef enum {

     ERASE_NONE = 0u,
     ERASE_SYSTEM_INFO,

} erase_type_t;




#endif
