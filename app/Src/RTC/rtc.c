#include "system.h"

//****************************************************************//
//函数名称: void Rtc_Time_Cal(void)
//函数功能:  RTC时钟校准
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Rtc_Time_Cal(void){

   //每一天去校准一次时间
   if(System.wifi_hardware_is_init&&SystemInfo.system_state==normal&& Display.disp_wifi)
       Protocol_Cmd_Cache(CMD_TIME);
}

//****************************************************************//
//函数名称: Rtc_One_Sec_Process
//函数功能: 1Sec 处理
//参    数:
//返 回 值:
//说    明: 0.5S处理
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Rtc_One_Sec_Process(void){

    if(System_Mode_Read()>=Set_Current_Hours_Mode && System_Mode_Read()<=Set_Current_Week_Mode){
      if(!Key.release_delays&&!Key.Value)
        Current.Sec++;
      
    }else
      Current.Sec++;
    
   if(Current.Sec>59) {
      Current.Sec=0;
      Current.Minute++; 
      if(Current.Minute>59){
        Current.Minute=0;
        Current.Hours++;
        if( Current.Hours>23){
          Current.Hours=0;
          Current.Week<<=1;
          if(Current.Week==0x80)
            Current.Week=0x01;
          Rtc_Time_Cal();
          //一天存一次数据
          PowerDown_FroceSaveInfo();

        }
      }
      Timing_Action_Scan();
   }
}

//****************************************************************//
//函数名称: Rtc_Process
//函数功能: RTC
//参    数:
//返 回 值:
//说    明: 0.5S处理
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Rtc_Process(void){

    //按键按下不闪烁
    if(((System_Mode_Read()>Normal_Mode && System_Mode_Read()<Set_Timing_Mode)||(System_Mode_Read()==Set_Timing_Mode))&&(Key.release_delays||Key.Value))
       Display.lcd_flash_flag=0;
    else
        Display.lcd_flash_flag=~Display.lcd_flash_flag;
    
    System.one_sec_flag++;
    if(System.one_sec_flag>=2) {
        
      System.one_sec_flag=0;

      Rtc_One_Sec_Process();
      if(Key.release_delays)
        Key.release_delays--;   
       Protocol_Repet_Get_CurrentTime();
    }
    
    Lcd_disp_lock_flash_timer();
    
    Lcd_Channel_StateFlash_Timer(); 
    
    Display.update_lcd=1;
    
    Sleep.wakeup_type= wake_up_by_rtc;
    
    if(System.back_led_delays&&System_Mode_Read()!=Factory_Mode){
     
      if(--System.back_led_delays==0)
        System_Back_Led_Close();
    }
    if(System.power_on_init){
        
         if(Bsp_Power_Down_Scan()&&System.is_power_down){
             
            System.count_power_on++;
            
            if(System.count_power_on>6){
              System.count_power_on=0;
             //检测到电压恢复，且之前是掉电状态，则恢复背光    
             if(System.is_power_down) {
                 
                Power_Down_Restore();
                 
                Lcd_BackLight_Open();
                 
                if(!System.wifi_hardware_is_init){
                  //关闭所有按键的中断
                  Bsp_Key_Exit_Disable();
                  //配置掉电中断检测
                  System_PowerDown_Exit_Config();
                    
                  System.wifi_hardware_is_init=1;
                    
                  System_Connect_Wifi_Process();
                    
                }
             }
               Lcd_Display();
           }
         }else
       System.count_power_on=0; 
   }

}
//****************************************************************//
//函数名称: void Rtc_TimeOut_Process(void)
//函数功能: RTC 超时处理
//参    数:
//返 回 值:
//说    明: 0.5S处理
//修改记录: 2025.10.8 Whm创建函数
//***************************************************************//
void Rtc_TimeOut_Process(void){

      if(System.TimeOut){
          
          System.TimeOut--;
          
           if(System.TimeOut==0){
           
             if(System_Mode_Read()>Normal_Mode&&System_Mode_Read()<Select_Channel_Mode){
               
               System_Out_Current_TimeSet();
               
               if(System_Mode_Read()==Set_Timing_Mode)
                  Check_Near_CurrentTime_Arrary((TIMING_INFO*)&SystemInfo.time_channel[System.timing_channel_number-1]);   
               else     
                  Lcd_Channel_State_Change_Fast_Flash(6);
             }
             System_Mode_Set(Normal_Mode);
             Display.update_lcd=1;
           }
      
      }

}


//****************************************************************//
//函数名称: RTC_TAMP_IRQHandler
//函数功能: RTC中断
//参    数:
//返 回 值:
//说    明:    0.5S
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void RTC_TAMP_IRQHandler(void)
{      
    /* 2Hz周期中断处理流程 */
    if(std_rtc_get_wut_interrupt_enable(RTC_WUT_INTERRUPT_2HZ)
      && std_rtc_get_interrupt_flag(RTC_INTERRUPT_FLAG_2HZ))
    {
        /* 清除2Hz周期中断标志 */
        std_rtc_clear_flag(RTC_CLEAR_2HZ);
        
        Rtc_Process();
        
        Rtc_TimeOut_Process(); 
    }
}


