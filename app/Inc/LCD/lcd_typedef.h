#ifndef _LCD_TYPDEF_H_
#define _LCD_TYPDEF_H_

#include "stdint.h"


typedef struct{

    uint8_t  channel_fast_flash_enable          :1u; //通道快速闪烁使能
    uint8_t  channel_fast_flash_flag            :1u; //通道快速闪烁标志位
    uint8_t  relay_state_flash_enable           :1u; //继电器状态闪烁使能
    uint8_t  relay_state_flash_flag             :1u; //继电器状态闪烁标志位
    uint8_t  update_lcd                         :1u; //更新液晶
    uint8_t  lcd_flash_flag                     :1u; //液晶闪烁标志位
    uint8_t  col_not_flash                      :1u; //col常显
    uint8_t  not_disp_mode                      :1u; //不显示模式

    uint8_t  lock_flash_flag                    :1u;
    uint8_t  lock_flash_enable                  :1u;
    uint8_t  disp_wifi                          :1u;
    uint8_t  idle                               :5u;

    uint8_t  fast_disp_channel_times ;               //显示次数
    uint8_t  locked_flash_times;
    uint16_t Fast_disp_channel_Delays;     
    
    uint8_t  releay_state_change_times;              //继电器状态改变闪烁次数

    
}LCD_STRUCT;

extern LCD_STRUCT Display;







#endif
