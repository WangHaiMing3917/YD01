#ifndef _SYSTEM_TYPEDEF_H_
#define _SYSTEM_TYPEDEF_H_

#include "stdint.h"

#define  Mode_Change         0x01
#define  Switch_Change       0x02
#define  Group_Change        0x04
#define  Group_Time_Change   0x08
#define  Lock_Change         0x10

#define  Channel1_Changed    (uint32_t)(Mode_Change|Switch_Change|Group_Change|Group_Time_Change|Lock_Change)
#define  Channel2_Changed    (uint32_t)((Mode_Change|Switch_Change|Group_Change|Group_Time_Change)<<5)
#define  Channel3_Changed    (uint32_t)((Mode_Change|Switch_Change|Group_Change|Group_Time_Change)<<10)
#define  ALL_Change          (Channel3_Changed|Channel1_Changed|Channel2_Changed)

typedef struct{
    //0
    uint8_t wait_into_factory                :1u;  //等待进入工厂
    uint8_t idle2                            :1u;  //按键已经被锁住
    uint8_t lptime_is_enable                 :1u;  //低功耗是否使能
    uint8_t uart_is_init                     :1u;  //串口已初始化
    
    uint8_t is_power_down                    :1u;  //掉电
    uint8_t will_interactive_model           :1u;  //wifi模块交互
    uint8_t wifi_hardware_is_init            :1u;  //wifi硬件初始化
    uint8_t idle_2                           :1u;

    uint8_t send_get_down_enable             :1u;  //允许发射get_down
    uint8_t send_update_fail_enable          :1u;  //发射升级失败使能
    uint8_t idle4                            :1u;  
    uint8_t back_led_state                   :1u;  //背光灯状态
    
    uint8_t power_on_init                    :1u;  //系统上电初始化
    uint8_t power_down_exit_is_config        :1u;  //掉电中断已配置  
    uint8_t current_time_is_updated          :1u;  //当前时间已经更新
    uint8_t is_need_factory_wifi             :1u;
    
    uint8_t ack_mcu_ver                      :1u;
    uint8_t wait_restor                      :1u;
    uint8_t not_process_release              :1u;
    uint8_t is_not_allow_send_changed        :1u;
    
    uint8_t is_power_on_send_changed         :1u;
    uint8_t is_idle                          :3u;
    uint8_t mode;                                  //系统当前模式
    //1
  //  uint8_t channel;                               //当前通道
    uint8_t idle;
    uint8_t timing_index;                          //定时序号0-55
    uint8_t timing_channel_number;                 //定时组号
    uint8_t timing_week_number;                    //定时星期数值
    
    uint8_t one_sec_flag;                          //达到1秒标志位
    uint8_t Model_Interactive_Step;                //上电模块交互步骤
    uint8_t timer_Enable_Count[5];
    uint8_t update_fail_send_times;                //发射次数
    
    uint16_t update_fail_send_delays;              //延迟发射boot fail 
    uint16_t wait_connect_wifi_delays;             //等待连接wifi延时
    
    uint8_t back_led_delays;
    uint8_t count_power_on; 
    uint16_t TimeOut;                              //系统退出时间

    uint16_t get_down_delays; 
    uint16_t wait_to_update_delays; 
    
    uint8_t Cmd;
    uint8_t Cmd_Cache;
    uint8_t Cmd_Cache2;
    uint8_t Cmd_Cache3;

    uint8_t Properties_Change_Scan_Delays;
    uint8_t receive_channel;
    uint16_t power_on_send_properties_delays;

    uint32_t Properties_Change;                     //属性更改

}SYSTEM_STRUCT;
extern SYSTEM_STRUCT System;

enum{

   Normal_Mode=0,
   Set_Current_Hours_Mode,
   Set_Current_Minutes_Mode,
   Set_Current_Week_Mode,
   Set_Timing_Mode,
   Select_Channel_Mode,
   Factory_Mode,
};
enum{

   wake_up_by_hour_key=1,
   wake_up_by_minute_key,
   wake_up_by_mode_key,
   wake_up_by_timing_key,
   wake_up_by_week_key,    
   wake_up_by_rtc,
   wake_up_by_lptime,

};
enum{

   factory_disp_ver_name=0,
   factory_disp_current_channel,
   factory_disp_number,
   factory_control_relays,
   factory_test_key,
   factory_disp_relay_count,

    
};
enum{
    wait_none=0,
    wait_feedback_set_model,          //等待设置模组反馈
    wait_feedback_ble_config,         //等待设置ble反馈
    wait_feeback_send_mcu_vesrion,    //等待发送版本反馈
    wait_feeback_current_time,
    wait_feedback_get_down,           //等待发送get_down反馈
    wait_feedback_result,             //等待上传结果反馈
    wait_feedback_update_start,       //等待接收更新开始
    wait_feedback_error_code,         //等待上传错误代码反馈
    wait_feedback_properties_changed, //等待属性改变反馈
    wait_feedback_event_occured,      //等待事件发送反馈
    wait_feedback_boot_fail_ok,       //等待收到模块成功收到mcu失败反馈
    wait_feeback_only_mcu_vesrion,
    wait_feeback_restor,              //等待复位模块
    wait_feeback_factory,             //等待工厂测试
    wait_feeback_cal_time,            //校准时间
    wait_feeback_check_net,
};
enum{
    
   None=0,
   Send_Model,
   Send_Ble_config,
   Send_Mcu_Version, 
   Complete,

};
enum{

   Factory_Auto_disp_Step_1=0,
   Factory_Auto_disp_Step_2,
   Factory_Auto_disp_Step_3, 
   Factory_Auto_disp_Step_4, 
   Factory_Auto_disp_Step_5,
   Factory_Auto_disp_Step_6,
   Factory_Auto_disp_Step_7,
   Factory_Auto_disp_Step_8,
   Factory_Auto_disp_Step_All,
};

enum{
   Factory_Key_Step_None=0,
   Factory_Key_Step_1,
   Factory_Key_Step_2,
   Factory_Key_Step_3,
   Factory_Key_Step_4,
   Factory_Key_Step_5,
};

enum{
   ASCII_0=0,
   ASCII_1, 
   ASCII_2, 
   ASCII_3,
   ASCII_4,
   ASCII_5,
   ASCII_6,
   ASCII_7,
   ASCII_8,
   ASCII_9,    
   ASCII_A=65,
   ASCII_B,
   ASCII_C,
   ASCII_D, 
   ASCII_E,
   ASCII_F,
   ASCII_G,
   ASCII_H, 
   ASCII_I,
   ASCII_J,
   ASCII_K,
   ASCII_L,
   ASCII_M, 
   ASCII_N,
   ASCII_O,
   ASCII_P,
   ASCII_Q, 
   ASCII_R,
   ASCII_S,
   ASCII_T, 
   ASCII_U, 
   ASCII_V,
   ASCII_W,
   ASCII_X, 
   ASCII_Y,
   ASCII_Z,
    
    
};

#define CMD_GET_DOWN              0x01
#define CMD_ERROR                 0x02
#define CMD_TIME                  0x03
#define CMD_PROPERTIES_CHANGED    0x04
#define CMD_MCU_VER               0x05
#define CMD_GET_NET               0x06
#define CMD_RESTORE               0x07
#define CMD_UPDATE_FAIL           0x08
#define CMD_SET_PROPERTIES_RPS    0x09
#define CMD_GET_PROPERTIES        0x0A
#define CMD_ACTION                0x0B
#define CMD_TOO_LONG              0x0C
#define CMD_UPDATE_READY          0x0D
#define CMD_MEMORY_ERROR          0x0E
#define CMD_INTO_UPDATE           0x0F

#endif


