#include "system.h"

CURRENT_TIME_STRUCT Current __attribute__ ((aligned (4u)));

const uint8_t WeekModeTable[15] = {
    
    MonDay|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday,  // 0
    MonDay,    //1
    Tuesday,   //2
    Wednesday, //3
    Thursday,  //4
    Friday,    //5
    Saturday,  //6
    Sunday,    //7
    MonDay|Tuesday|Wednesday|Thursday|Friday,  //8
    Sunday|Saturday,                            //9
    MonDay|Tuesday|Wednesday|Thursday|Friday|Saturday, //10
    MonDay|Wednesday|Friday,                   //11
    Tuesday|Thursday|Saturday,                //12
    MonDay|Tuesday|Wednesday,                  //13
    Thursday|Friday|Saturday                   //14
};

volatile uint32_t uwTick;
//****************************************************************//
//函数名称: void TIM8_IRQHandler(void)
//函数功能: 定时器8定时
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void TIM8_IRQHandler(void)
{
    /* TIM8更新中断处理流程 */
    if ((std_tim_get_interrupt_enable(TIM8, TIM_INTERRUPT_UPDATE)) && (std_tim_get_flag(TIM8, TIM_FLAG_UPDATE)))
    {
        std_tim_clear_flag(TIM8, TIM_FLAG_UPDATE);
        uwTick++; 
        System_Factory_Disp_Timer();  
        System_1ms_Timer();
        Protocol_1ms_Timer();
    }
}
//****************************************************************//
//函数名称: void Current_Clock_Init(void)
//函数功能: 当前时间初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Current_Clock_Init(void){
           
   Current.Hours  = 0x00;
   Current.Minute = 0x00;
   Current.Sec    = 0x00;
   Current.Week   = MonDay; 
   Current.channel= SystemInfo.Current_Channel;
   Current.Mode   = SystemInfo.time_channel[SystemInfo.Current_Channel-1].Mode;
   for(uint8_t i=0;i<SystemInfo.ChannelCount;i++){
       
     System.timer_Enable_Count[i]=SystemInfo.time_enable_count[i];
     Protocol_Change_Mode( SystemInfo.time_channel[i].Mode,i);
       
   }
   Display.update_lcd=1;   
   
}    

//****************************************************************//
//函数名称: void Check_Near_CurrentTime_Arrary(CHANNEL_STRUCT *Ch)
//函数功能: 退出定时后，打开关闭相应继电器，并且赋值为自动
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Check_Near_CurrentTime_Arrary(TIMING_INFO *Ch){

   uint8_t enable_count = 0;
   uint8_t save_count[56] = {0};
   uint8_t save_number = 0;

   // 筛选有效定时
   for(uint8_t i = 0; i < 56; i++){
       
      TIMING_BASE_STRUCT* t = &Ch->timing[i];
      if(t->enable){
          
        enable_count++;
          
        if((WeekModeTable[t->week] & Current.Week) != 0){
            
            if( (t->hour < Current.Hours) || 
                (t->hour == Current.Hours && t->minutes <= Current.Minute) ){
                    
                save_count[save_number++] = i + 1;
            }
        }
      }
   }

   // 排序 + 去重处理
   if(save_number > 0 || enable_count){
    // 冒泡排序（从早到晚）
    if(save_number > 1){
        uint8_t cache;
        for(uint8_t j = save_number; j > 0; j--){
            
            for(uint8_t p = 1; p < j; p++){
                
                TIMING_BASE_STRUCT* t_prev = &Ch->timing[save_count[p-1]-1];
                
                TIMING_BASE_STRUCT* t_curr = &Ch->timing[save_count[p]-1];
                
                if( (t_prev->hour > t_curr->hour) || 
                    (t_prev->hour == t_curr->hour && t_prev->minutes > t_curr->minutes) ){
                    cache = save_count[p];
                    save_count[p] = save_count[p-1];
                    save_count[p-1] = cache;
                }
            }
        }
    }

    uint8_t error = 0;
    // 去重逻辑
    if(save_number >= 2){
        
        while(save_number){
            
            error = 0;
            
            uint8_t last_idx = save_count[save_number-1] - 1;
            
            TIMING_BASE_STRUCT* t_last = &Ch->timing[last_idx];
            
            for(uint8_t i = 0; i < save_number; i++){
                
                uint8_t curr_idx = save_count[i] - 1;
                
                TIMING_BASE_STRUCT* t_curr = &Ch->timing[curr_idx];
                
                if(t_last->hour == t_curr->hour && t_last->minutes == t_curr->minutes){
                    
                    if( (save_count[save_number-1] % 2) != (save_count[i] % 2) ){
                        
                        save_count[i] = 0;
                        
                        save_count[save_number-1] = 0;
                        
                        error = 1;
                    }
                }
            }

            if(error){
                
                uint8_t cache[56] = {0};
                
                uint8_t cnt = 0;
                
                for(uint8_t i = 0; i < save_number-1; i++){
                    
                    if(save_count[i] > 0){
                        
                        cache[cnt++] = save_count[i];
                    }
                }
                
                memcpy(save_count, cache, cnt);
                
                save_number = cnt;
                
                if(save_number <= 1) break;
                
            }else{
                break;
            }
        }
    }

    // 自动模式控制
    if(save_number || enable_count){
        
        if(Ch->Mode != AUTO_STATE){
            
            System_Properties_Change_Cal(Ch->Index, Mode_Change);
            
            Ch->Mode = AUTO_STATE;
        }
        if((Ch->Index + 1) == Current.channel){
            
            Current.Mode = Ch->Mode;
            
            Lcd_Channel_State_Change_Fast_Flash(6);
        }
        Ch->Timing_is_Valid = 1;
    }else{
        
        Ch->Timing_is_Valid = 0;
        
        if(Current.Mode == AUTO_STATE){
            
            Channel_Control(Ch->Index, RELAY_OFF, change_flag);
            
            Ch->Mode = CLOSE_STATE;
            
            System_Properties_Change_Cal(Ch->Index, Mode_Change);
            
            if((Ch->Index + 1) == Current.channel){
                Current.Mode = Ch->Mode;
            }
        }
    }

    // 执行最终开关
    if(!error && save_number){
        uint8_t last = save_count[save_number-1];
        Channel_Control(Ch->Index, (last % 2 == 0) ? RELAY_OFF : RELAY_ON, change_flag);
    }else if(!error && enable_count)
        Channel_Control(Ch->Index, RELAY_OFF, change_flag);
   
   }

   // 使能组计数 + disp_none 处理
   uint8_t Group_Enable_Cache = 0;
   
   for(uint8_t c = 0; c < 28; c++){
       
    TIMING_BASE_STRUCT* t0 = &Ch->timing[2*c];
       
    TIMING_BASE_STRUCT* t1 = &Ch->timing[2*c+1];
    
    if(t0->enable || t1->enable) Group_Enable_Cache++;
    
    if(t0->enable == 1 && t1->enable == 0){
        
        t0->disp_none = 0;
        
        t1->disp_none = 1;
        
    }else if(t0->enable == 0 && t1->enable == 1){
        
        t0->disp_none = 1;
        
        t1->disp_none = 0;
        
    }
   }

   // 组数量变化上报
   if(SystemInfo.time_enable_count[Ch->Index] != Group_Enable_Cache){
       
    SystemInfo.time_enable_count[Ch->Index] = Group_Enable_Cache;
       
    System.timer_Enable_Count[Ch->Index] = Group_Enable_Cache;
       
    System_Properties_Change_Cal(Ch->Index, Group_Change);
       
   }

   // CRC校验 定时内容变化
   if(SystemInfo.crc16 != Crc16_Cal((uint8_t*)&SystemInfo.time_channel, 845u)){
       
    System_Properties_Change_Cal(Ch->Index, Group_Time_Change);
       
   }

   Display.update_lcd = 1;

   // 无定时强制关闭
   if(Group_Enable_Cache == 0){
       
    if(Current.Mode == AUTO_STATE){
        
        if(SystemInfo.time_channel[Ch->Index].Relays_States)
           Channel_Control(Ch->Index, RELAY_OFF, change_flag);
        
        Ch->Mode = CLOSE_STATE;
        
        Ch->Timing_is_Valid = 0;
        
        System_Properties_Change_Cal(Ch->Index, Mode_Change);
        
        if((Ch->Index + 1) == Current.channel)
           Current.Mode = Ch->Mode;
        
    }
   }
}

//****************************************************************//
//函数名称: uint8_t Timing_Week_Mode_To_Number(uint8_t Mode)
//函数功能: 星期转换成睡
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Timing_Week_Mode_To_Number(uint8_t Mode){

    
    uint8_t Number = 0;

    for (uint8_t i = 0; i < 15; i++) {
       if (Mode == WeekModeTable[i]) {
        Number = i;
        break;
       }
    }
    return Number;
}
//****************************************************************//
//函数名称: void Timing_Action_Scan(void)
//函数功能: 定时动作扫描
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Timing_Action_Scan(void){
    
    
    for(uint8_t i=0u;i<SystemInfo.ChannelCount;i++){
    
        if(SystemInfo.time_channel[i].Mode==AUTO_STATE){
            
            
           uint8_t Open_Count=0,Close_Count=0;
           for(uint8_t j=0u;j<56u;j++){
     
              if(SystemInfo.time_channel[i].timing[j].enable){
                   //定時的星期包含当前WeekModeTable[Ch->timing[i].week]
                  if(WeekModeTable[SystemInfo.time_channel[i].timing[j].week]&Current.Week){
                  
                      if(SystemInfo.time_channel[i].timing[j].hour==Current.Hours){
                                                                          
                          if(SystemInfo.time_channel[i].timing[j].minutes==Current.Minute){
                              
                             if((j+2)%2 ==0)
                               Open_Count++;
                             else
                               Close_Count++; 
                          }
                      }
                  }
              }
              if(j==55){
                  
                if(Open_Count>0&&Close_Count==0){
                    
                  Channel_Control(SystemInfo.time_channel[i].Index,RELAY_ON,change_flag);
                    
                  if(Current.channel==(i+1))
                    Lcd_Channel_State_Change_Fast_Flash(6);   
                  
                }else  if(Open_Count==0&&Close_Count>0){
                    
                  Channel_Control(SystemInfo.time_channel[i].Index,RELAY_OFF,change_flag);
                    
                  if(Current.channel==(i+1))  
                    Lcd_Channel_State_Change_Fast_Flash(6);  
                }
              }
           }
        }  
    }
}
//****************************************************************//
//函数名称: void Time_1ms_poll(void)
//函数功能: 定时1ms循环
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Time_1ms_poll(void){

     SystemInfo_Save();
     //低电压返回
     if(System.is_power_down)
      return ;
   
     static uint32_t OldTick;

     //判断当前滴答与上次是否相同
     if (OldTick == uwTick)
        return;
     //把当前时钟滴答赋值给上次滴答
     OldTick = uwTick;
     //需要将这个放到1ms循环

     Searil_Timer();

     if(Update.wait_send_eot_end&&Searil.Tx_State==Tx_Idle){
       
       Update.wait_send_eot_end=0;
     
       Jump_Process();
     }
     Protocol_Properties_Changed_Scan();
     
     X_Modem_Timer();
  
     if(System.send_update_fail_enable){
       
       if(System.update_fail_send_delays){
           
          if(--System.update_fail_send_delays==0){
          
                 if(System.update_fail_send_times<10){
                   //一直收不到模块反馈OK，则最多发10，然后退出  
                   Protocol_Cmd_Cache(CMD_UPDATE_FAIL);
                   System.update_fail_send_times++;
                   System.update_fail_send_delays=1000;  

                }else{
                   //持续失败，重新连接
                   System.send_update_fail_enable=0;  
                   SystemInfo.system_state=normal;
                   SystemInfo.is_request_save=1;
//                   SystemInfo_Save();
                   System.wait_connect_wifi_delays=200;

                }
          }
       }
    }
    if(System.power_on_send_properties_delays){
    
        if(--System.power_on_send_properties_delays==0)
            System.Properties_Change=ALL_Change;
    }

}


