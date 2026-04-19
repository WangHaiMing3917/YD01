#include "system.h"

KEY_STRUCT Key __attribute__ ((aligned (4u)));


//****************************************************************//
//函数名称: EXTI4_15_IRQHandler
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void EXTI4_15_IRQHandler(void)
{
    /* 读取EXTI通道中断挂起状态 */
    if (std_exti_get_pending_status(KEY_MINUTE_EXTI_LINE))
    {
        /* 清除EXTI通道中断挂起状态 */
        std_exti_clear_pending(KEY_MINUTE_EXTI_LINE);
        
        Sleep.wakeup_type= wake_up_by_minute_key;
        
    }
   if (std_exti_get_pending_status(KEY_HOURS_EXTI_LINE))
    {
        /* 清除EXTI通道中断挂起状态 */
        std_exti_clear_pending(KEY_HOURS_EXTI_LINE);
        
        Sleep.wakeup_type= wake_up_by_hour_key;

    }
}
//****************************************************************//
//函数名称: EXTI2_3_IRQHandler
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void EXTI2_3_IRQHandler(void)
{
    /* 读取EXTI通道中断挂起状态 */
    if (std_exti_get_pending_status(KEY_TIMING_EXTI_LINE))
    {
        /* 清除EXTI通道中断挂起状态 */
        std_exti_clear_pending(KEY_TIMING_EXTI_LINE);
          Sleep.wakeup_type= wake_up_by_timing_key;
    }
}
//****************************************************************//
//函数名称: EXTI0_1_IRQHandler
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void EXTI0_1_IRQHandler(void)
{
    /* 读取EXTI通道中断挂起状态 */
    if (std_exti_get_pending_status(KEY_WEEKS_EXTI_LINE))
    {
        /* 清除EXTI通道中断挂起状态 */
        std_exti_clear_pending(KEY_WEEKS_EXTI_LINE);
        if(!System.power_down_exit_is_config)
          Sleep.wakeup_type= wake_up_by_week_key;
        else{
            
          System.count_power_on=0;
            
          Power_Down_Process();
            
          Protocol_Cmd_Clear();
          System.Properties_Change_Scan_Delays=0;
          System.Properties_Change=0;  
          System.wifi_hardware_is_init=0;  
          //失能掉电中断检测 
          System_PowerDown_Exit_Deint(); 
          //打开按键中断
          Bsp_Key_Exit_Enable();
          
          LpTime1_Enable();
          //关闭wifi显示
          Lcd_Wifi_disp_set(0);
          
          Lcd_Display();
          
          System_Wifi_Connect_DeInit(); 
          //系统处于升级过程中，将直接变成upadate_down 状态并停止发射
          System_PowerDown_UpdateStateProcess();
          
          System_Disable_Send_Get_Down(); 
          
          if(System.power_on_init){
              
            SystemInfo.is_request_save=1u;
             //将数据写入Flash的第一行
           // SystemInfo_Save(); 
          }  
            Into_Sleep_Mode(); 
        }
       
    }
       /* 读取EXTI通道中断挂起状态 */
    if (std_exti_get_pending_status(KEY_MODE_EXTI_LINE))
    {
        /* 清除EXTI通道中断挂起状态 */
        std_exti_clear_pending(KEY_MODE_EXTI_LINE);
        Sleep.wakeup_type= wake_up_by_mode_key;
       
    } 
    
    
   
}
//****************************************************************//
//函数名称: uint16_t Key_State_Read(void)
//函数功能: 按键状态读取
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint16_t Key_State_Read(void){
    

    uint16_t Value=0;
    
    if(!Bsp_Hour_Key_Read())
       Value|=KEY_HOURS;
    if(!Bsp_Mode_Key_Read())
       Value|=KEY_MODE;
    if(!Bsp_Timing_Key_Read())
       Value|=KEY_TIMING;  
    if(!Bsp_Weeks_Key_Read())
       Value|=KEY_WEEKS;
    if(!Bsp_Minutes_Key_Read())
       Value|=KEY_MINUTES; 

    return Value;

}
//****************************************************************//
//函数名称: Key_Scan
//函数功能: 按键扫描
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Scan(void){
    
    volatile uint16_t x=0;
    
    x=Key_State_Read();
    
    if(x!=Key.Cache){
    
          Key.Trg        =x&(x^Key.Cache);
          Key.Release    =(x^Key.Trg)^Key.Cache;
          Key.Value      =x;
          Key.Cache      =x;

    }
}
//****************************************************************//
//函数名称: Key_Trg_Process
//函数功能: 按键按下处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Trg_Process(void){

   if(Key.Trg){
       
      Key.HoldFlag=0;
       
      Lcd_BackLight_Open();
      
      if(Key_is_Locked())
       return;
      switch(Key.Trg){
          
         case KEY_MODE:

         break;
         case KEY_MINUTES:
          if(System_Mode_Read()==Factory_Mode){
                
                if(factory.item==factory_disp_relay_count){
                    
                   factory.start_channel++;
                    
                   if( factory.start_channel>=SystemInfo.ChannelCount)
                        factory.start_channel =0;
                   
                   factory.relays_count  = SystemInfo.channel_count_index[factory.start_channel];
                   factory.channel = factory.start_channel+1;                                        
                }
                
            }
          break;
         default:
          break;
      }
      Key.Trg=0;
   }


}

//****************************************************************//
//函数名称: Key_Value_Inc_Cyc(uint8_t type)
//函数功能: 按鍵循環增加
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Value_Inc_Cyc(uint8_t Key_Type,uint8_t is_hold){
 
     switch(Key_Type){
     
         case KEY_HOURS:
            if(System_Mode_Read()==Set_Current_Hours_Mode){        
             Current.Hours++;
             if(Current.Hours>23) 
                Current.Hours=0; 
             Current.Sec=0;
            } else if(System_Mode_Read()==Set_Timing_Mode)  {
            
              if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable) {
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].hour++;
                 if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].hour>23u)
                   SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].hour=0u;
              }else{
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable=1;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].hour=1u;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].minutes=0u; 
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].week=0u;
                 System.timing_week_number= 0u;
              }
            
            }
           break;
         case KEY_MINUTES:
             if(System_Mode_Read()==Set_Current_Minutes_Mode){     
                Current.Minute++;
                if(Current.Minute>59)
                  Current.Minute=0;
                Current.Sec=0; 
            }else if(System_Mode_Read()==Set_Timing_Mode){
                
               if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable) {
                   
                  SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].minutes++;
                  if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].minutes>59)
                     SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].minutes=0u;
              }else{
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable=1;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].hour=0u;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].minutes=1u; 
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].week=0u;
                 System.timing_week_number= 0u;
              
              }
            }
           break; 
         case KEY_WEEKS:
           if(System_Mode_Read()==Set_Current_Week_Mode){  
              Current.Week<<=1;
              if(Current.Week==0x80)
                Current.Week=0x01;
               Current.Sec=0; 
           }else if(System_Mode_Read()==Set_Timing_Mode){
               
              if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable) {  
                 System.timing_week_number++;
                 if(System.timing_week_number>14u)
                   System.timing_week_number=0u;  
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].week=System.timing_week_number;
          
              }else{

                 System.timing_week_number=0u;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable=1;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].hour=0u;
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].minutes=0u; 
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].week=System.timing_week_number;
              
              }
           } 
           break;
         default:
           break;
     
     }
     if(is_hold){
         
       Key.CycPress_StartDelays-=1u;
                    
       Key.HoldFlag=hold_start_other;
        
       if(Key.Delays<5u) {
         Key.Delays=2;
         Key.CycPress_StartDelays=2U;
        
       }
       Key.Delays=Key.CycPress_StartDelays;
       Display.update_lcd=1;
     }else{
       Key.HoldFlag=hold_start_other;
       Key.CycPress_StartDelays=20;
       Key.Delays=Key.CycPress_StartDelays;
       Display.update_lcd=1;
       Key.Fast_Cnt=1;
     }


}
//****************************************************************//
//函数名称: Key_Value_Process
//函数功能: 按键按下处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Value_Process(void){


  if(Key.Value){
      
    Lcd_BackLight_Open();
      
    if(System_Mode_Read()>Normal_Mode && System_Mode_Read()<Factory_Mode)
      System_TimeOut_Set(20u);
    if(Key.HoldFlag==hold_0){
        
      switch(Key.Value){
    
        case KEY_MINUTES:
           if(System_Mode_Read()==Normal_Mode){
               
              Display.not_disp_mode=0u;
               
              Current.channel++;
               
              if(Current.channel>SystemInfo.ChannelCount)
                Current.channel=1;
              
              Current.Mode=SystemInfo.time_channel[Current.channel-1].Mode;
              
              Key.HoldFlag=hold_start_other;
              
              Key.Delays=15u;
              
              Lcd_Fast_Disp_Channel_Into(6u,2u);
              
              Display.update_lcd=1;
              
           } else if((System_Mode_Read()==Set_Current_Hours_Mode)  || (System_Mode_Read()==Set_Current_Week_Mode)||
                System_Mode_Read()==Set_Current_Minutes_Mode ||  System_Mode_Read()==Set_Timing_Mode){
                    
                if((System_Mode_Read()==Set_Current_Hours_Mode)||(System_Mode_Read()==Set_Current_Week_Mode)){
                    
                   System_Mode_Set(Set_Current_Minutes_Mode);
                    
                   Current.Sec=0;
                    
                }
                 Key_Value_Inc_Cyc(KEY_MINUTES,0);

           }else if(System_Mode_Read()==Factory_Mode){
  
                if(factory.item==factory_test_key){
                   
                   factory.key_item=Factory_Key_Step_2;
                   Display.update_lcd=1;
                    
                   Key.HoldFlag=hold_start_1000;
              
                   Key.Delays=15u;    
                    
                }
           } 
         break;
        case KEY_TIMING:

           if(System_Mode_Read()==Normal_Mode){
           
              Display.col_not_flash=0u;            //恢复显示冒号闪烁
              Display.not_disp_mode=0u;            //恢复显示模式
              Display.update_lcd=1;
              System_Mode_Set(Select_Channel_Mode); 
              System.timing_channel_number=Current.channel;
              Key.HoldFlag=hold_start_3000;
              Key.Delays=60u; 
              //延时10秒
              System_TimeOut_Set(20u);
           }
          else if(System_Mode_Read()==Select_Channel_Mode){
               
              Key.HoldFlag=hold_start_2000;
              Key.Delays=40u;  
           }

          else if(System_Mode_Read()==Set_Timing_Mode){
              Key.HoldFlag=hold_start_2000;
              Key.Delays=40u;  
              Display.lcd_flash_flag=0;
              System.timing_index++;
              if(System.timing_index>55)
                 System.timing_index=0;
               Display.update_lcd=1;
              System.timing_week_number=(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].week);    
  
           }else if(System_Mode_Read()>Normal_Mode&& System_Mode_Read()<=Set_Current_Week_Mode){
              //清除延时
              System_TimeOut_Clear(); 
              System_Out_Current_TimeSet(); 
              System_Mode_Set(Normal_Mode); 
               Display.update_lcd=1;
              Key.HoldFlag=hold_start_1000;
              Key.Delays=20u;    
           }else if(System_Mode_Read()==Factory_Mode){
  
                if(factory.item==factory_test_key){
                   factory.key_item=Factory_Key_Step_3;
                   Display.update_lcd=1;  
                }
            }
         break;
        case KEY_WEEKS:
            
            if(System_Mode_Read()==Normal_Mode){
                
                System_Mode_Set(Set_Current_Hours_Mode);
                Display.col_not_flash=1u;
                Display.not_disp_mode=1u;
                Display.update_lcd=1;
                                
                Key.HoldFlag=hold_start_1000;
                
                Key.Delays=20u;  
                //延时10秒
                System_TimeOut_Set(20u);
            }else if((System_Mode_Read()==Set_Current_Hours_Mode)||(System_Mode_Read()==Set_Current_Minutes_Mode)){
                
               System_Mode_Set(Set_Current_Week_Mode); 
               Key_Value_Inc_Cyc(KEY_WEEKS,0);
                

                
            }else if(System_Mode_Read()==Set_Current_Week_Mode||System_Mode_Read()==Set_Timing_Mode){
            
               Key_Value_Inc_Cyc(KEY_WEEKS,0);
                
            }else if(System_Mode_Read()==Factory_Mode){
  
                if(factory.item==factory_test_key){
                    
                   factory.key_item=Factory_Key_Step_4;
                   Display.update_lcd=1;
                }
            }
         break;
        case KEY_MODE:
          //开始计时模式
   
          if(System_Mode_Read()==Normal_Mode){
               //通道快闪
               Key.HoldFlag=hold_start_600;
               Key.Delays=12;
           //    Lcd_Fast_Disp_Channel_Into(6u,3u);
               Display.update_lcd=1;
          }
        else   if(System_Mode_Read()==Select_Channel_Mode){
              
               Key.HoldFlag=hold_start_600;
               Key.Delays=12;
               System.timing_channel_number++;
               if(System.timing_channel_number>SystemInfo.ChannelCount)
                  System.timing_channel_number=1; 
               Display.update_lcd=1;
          }

          else if(System_Mode_Read()>Normal_Mode && System_Mode_Read()<=Set_Current_Week_Mode){  
               Display.update_lcd=1;
               Current.Sec=0u;
          }else if(System_Mode_Read()==Set_Timing_Mode){
               Key.HoldFlag=hold_start_600;
               Key.Delays=12;
               uint8_t data;
               if( SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable){
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable=0u;
                 data=(System.timing_index+1)%2;
                 //当前是关
                 if(!data){
                    //上一个是开
                    if(!SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index-1].enable){
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index-1].disp_none=0;
                    }
                     
                 }else{//当前是开
                     //判断关的状态
                    if(!SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index+1].enable){
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index+1].disp_none=0;
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                    }   
                 
                 }
               }else{
                 SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].enable=1u;
                 data=(System.timing_index+1)%2;
                 //当前是关
                 if(!data){
                    //上一个是开
                    if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index-1].enable){
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index-1].disp_none=0;
                    }
                     
                 }else{//当前是开
                     //判断关的状态
                    if(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index+1].enable){
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index+1].disp_none=0;
                         SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].disp_none=0;
                    }   
                 
                 }
               }
      
               Display.update_lcd=1;
          }else if(System_Mode_Read()==Factory_Mode){
  
                if(factory.item==factory_test_key){
                   factory.key_item=Factory_Key_Step_5;
                   Display.update_lcd=1;

                }
          }

         break;
        case KEY_HOURS:
            
            if((System_Mode_Read()==Set_Current_Minutes_Mode)||(System_Mode_Read()==Set_Current_Week_Mode)){
            
                  System_Mode_Set(Set_Current_Hours_Mode);
                  Key_Value_Inc_Cyc(KEY_HOURS,0);
                  Current.Sec=0;

                
            }else if(System_Mode_Read()==Set_Current_Hours_Mode||System_Mode_Read()==Set_Timing_Mode){
                
                 Key_Value_Inc_Cyc(KEY_HOURS,0);
            }else if(System_Mode_Read()==Factory_Mode){
  
                if(factory.item==factory_test_key){
                   factory.key_item=Factory_Key_Step_1;
                   Display.update_lcd=1;
                }
            }
         break;
         case (KEY_HOURS+KEY_MINUTES):
             
            if(System_Mode_Read()==Normal_Mode){
               
               Key.HoldFlag=hold_start_1000;
               Key.Delays=20;  
            
            } 
         break;
        default:
         break;
      }
    }else if(Key.HoldFlag==hold_already_100){
    
        
    
    }else if(Key.HoldFlag==hold_already_600){
        
      switch(Key.Value){
          
       case  KEY_MODE:
       /*    
        if(System_Mode_Read()==Normal_Mode){
            //不显示模式
           // Display.not_disp_mode=1u;
            //通道不闪烁
            Lcd_Fast_Disp_Channel_Out();
            //0.3S后切换到下一个通道
            Key.HoldFlag=hold_start_1000;
           
            Key.Delays=8u;
           
            Display.update_lcd=1;
        }      */
       break;
       default:
        break;
      }
    }else if(Key.HoldFlag==hold_already_1000){
        
      switch(Key.Value){

       case  KEY_MODE:
         //通道+1，允许显示模式，通道开始闪烁
       /*
        if(System_Mode_Read()==Normal_Mode){
            Display.not_disp_mode=0u;
            Current.channel++;
            if(Current.channel>SystemInfo.ChannelCount)
              Current.channel=1;
            Current.Mode=SystemInfo.time_channel[Current.channel-1].Mode;
            Key.HoldFlag=hold_start_other;
            Key.Delays=15u;
            Lcd_Fast_Disp_Channel_Into(6u,2u);
            Display.update_lcd=1;
        }
       */
       break;
       case KEY_MINUTES:
             if(System_Mode_Read()==Factory_Mode){
                
               if(factory.item==factory_test_key){
                   
                  factory.item =  factory_disp_relay_count;
                   
                  Display.update_lcd=1; 
                   
                 factory.start_channel =0;
                   
                 factory.relays_count  = SystemInfo.channel_count_index[factory.start_channel];
                   
                 factory.channel = factory.start_channel+1; 
               }
            
            }
        break;

      case  (KEY_HOURS+KEY_MINUTES):
           if(SystemInfo.keylocked)
             SystemInfo.keylocked=0;
           else
              SystemInfo.keylocked=1; 
           System_Properties_Change_Cal(0,Lock_Change);
           Display.update_lcd=1;  
           if(!System.is_power_down){
            Key.HoldFlag= hold_start_9000;     //加9秒
            Key.Delays=180u;
           }else{
             Key.HoldFlag= hold_start_other;     //加9秒
             Key.Delays=4u;
           }
         break;
       default:
         break;
      }
                                  
    } else if(Key.HoldFlag==hold_already_2000){
         switch(Key.Value){
             
           case KEY_TIMING:
            /*
            #if CHANNEL_NUMBER >= 2    
               if(System_Mode_Read()==Select_Channel_Mode){
                   
                  Key.HoldFlag=hold_start_3000;
                  Key.Delays=8u;
                  System_Mode_Set(Set_Timing_Mode);
                  System.timing_index  =0;
                  Display.update_lcd=1;
                  Display.col_not_flash=1u;
                  System.timing_week_number=(SystemInfo.time_channel[System.timing_channel_number-1].Timing[System.timing_index].week);
                   
               }else if(System_Mode_Read()==Set_Timing_Mode){
                   
                    Key.HoldFlag=hold_start_3000;
                    Key.Delays=8u;
                    System_Mode_Set(Normal_Mode);
                    Display.col_not_flash=0u;
                    Display.update_lcd=1;  
                    //通道定时更改扫描，
                    Check_Near_CurrentTime_Arrary((TIMING_INFO*)&SystemInfo.time_channel[System.timing_channel_number-1].Index);
               }
            #else
            */
              if(System_Mode_Read()==Set_Timing_Mode){
                   
                    Key.HoldFlag=hold_start_3000;
                    Key.Delays=60u;
                    System_Mode_Set(Normal_Mode);
                    Display.col_not_flash=0u;
                    Display.update_lcd=1;  
                    //通道定时更改扫描，
                    Check_Near_CurrentTime_Arrary((TIMING_INFO*)&SystemInfo.time_channel[System.timing_channel_number-1]);
                    Current.channel =System.timing_channel_number;

               }else if(System_Mode_Read()==Select_Channel_Mode){
               
                    Key.HoldFlag=hold_start_3000;
                    Key.Delays=60u;
                    System_Mode_Set(Normal_Mode);
                    Display.col_not_flash=0u;
                    Display.update_lcd=1;  
                    Current.channel =System.timing_channel_number;

               }
              /*
            #endif
               */
              break;
         }             
    
    }else if(Key.HoldFlag==hold_already_3000){
       switch(Key.Value){
             
           case KEY_TIMING:
              if(System_Mode_Read()==Select_Channel_Mode){
               
                    Key.HoldFlag=hold_start_3000;
                    Key.Delays=60u;
                    System_Mode_Set(Normal_Mode);
                    Display.col_not_flash=0u;
                    Display.update_lcd=1;  
                    Current.channel =System.timing_channel_number;
               }

              break;
           }
    }
    else if(Key.HoldFlag==hold_already_9000){
        
        Key.HoldFlag= hold_start_other;     //加9秒
        Key.Delays=4;  
    
    }else if(Key.HoldFlag==hold_already_other){
    
        switch(Key.Value){
        
           case KEY_HOURS:
             if(System_Mode_Read()==Set_Current_Hours_Mode||System_Mode_Read()==Set_Timing_Mode)
                Key_Value_Inc_Cyc(KEY_HOURS,1);
             break;
           case KEY_WEEKS:
             if(System_Mode_Read()==Set_Current_Week_Mode||System_Mode_Read()==Set_Timing_Mode)
                Key_Value_Inc_Cyc(KEY_WEEKS,1);
             break;
           case KEY_MINUTES:
             if(System_Mode_Read()==Set_Current_Minutes_Mode||System_Mode_Read()==Set_Timing_Mode) 
                Key_Value_Inc_Cyc(KEY_MINUTES,1);
             break; 
           case  KEY_MODE:
             if(System_Mode_Read()==Normal_Mode){
                //不显示模式
                //Display.not_disp_mode=1u;
                //通道不闪烁
                Lcd_Fast_Disp_Channel_Out();
                //0.3S后切换到下一个通道
                Key.HoldFlag=hold_0;
                
                System.not_process_release=1;
                 
                Key.Delays=8u;
           
                Display.update_lcd=1;
             }
             break;
           default:
             break;
        }
    }
  }

}




//****************************************************************//
//函数名称: Key_Release_Process
//函数功能: 按键按下处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Release_Process(void){

    if(Key.Release){
       Key. release_delays=1;
        switch(Key.Release){
        
          case KEY_MODE:
               if(System_Mode_Read()==Factory_Mode)
                Factory_Key_Release_ConnectWifi(); 
               else if(System_Mode_Read()==Normal_Mode){  
                   
                  Display.not_disp_mode=0u;
                  if(Key.HoldFlag==hold_start_600&&!System.not_process_release)
                    Channel_Mode_Changed();   
               }   
       
           break;
          case KEY_TIMING:
             if(System_Mode_Read()==Factory_Mode)
                Factory_Key_Release_ConnectWifi();
             else if(System_Mode_Read()==Select_Channel_Mode){
                //通道选择界面  
                 
                if( Key.HoldFlag==hold_start_2000){
                
                  Key.HoldFlag=hold_start_1000;
                  Key.Delays=20u;
                  System_Mode_Set(Set_Timing_Mode); 
                  System.timing_index  =0;
                  Display.update_lcd=1;
                  Display.col_not_flash=1u;
                  System.timing_week_number=(SystemInfo.time_channel[System.timing_channel_number-1].timing[System.timing_index].week);
                }
             }
              break;
          case KEY_WEEKS:
          case KEY_HOURS:
          case KEY_MINUTES:
             if(System_Mode_Read()==Factory_Mode)
                Factory_Key_Release_ConnectWifi();
           break;
          default:
            break;
        }
     System.not_process_release=0;
     Key.HoldFlag=0;
     Key.Delays=0;
     Key.Release=0;
    }


}
//****************************************************************//
//函数名称: uint8_t  Key_is_Locked(void)
//函数功能: 按键是否上锁
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t  Key_is_Locked(void){

    if(SystemInfo.keylocked){
    
        if(Key.Value!=(KEY_HOURS+KEY_MINUTES)&&(Key.Value!=0)){

           Key.Release=0;
           Key.Trg=0;
           Key.Value=0;
           lcd_disp_flash(3); 
           return 1;
        }
    }
       return 0;

}

//****************************************************************//
//函数名称: Key_Process
//函数功能: 按键处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Process(void){

    Key_Trg_Process();
    
    Key_Value_Process();
    
    Key_Release_Process();

}
//****************************************************************//
//函数名称: Key_Timer
//函数功能: 按键定时处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Key_Timer(void){

      if(Key.Delays){
        
      Key.Delays--;
        
      if( Key.Delays==0){
      
          if(Key.HoldFlag==hold_start_100) 
           Key.HoldFlag=hold_already_100;
          else if(Key.HoldFlag==hold_start_300)
            Key.HoldFlag=hold_already_300;
          else if( Key.HoldFlag==hold_already_500)
            Key.HoldFlag=hold_already_500;
          else if(Key.HoldFlag==hold_start_600)
            Key.HoldFlag=hold_already_600;
          else if( Key.HoldFlag==hold_start_1000)
            Key.HoldFlag=hold_already_1000;
          else if( Key.HoldFlag==hold_start_2000)
            Key.HoldFlag=hold_already_2000;
          else if( Key.HoldFlag==hold_start_3000)
            Key.HoldFlag=hold_already_3000;
          else if(Key.HoldFlag==hold_start_9000)
            Key.HoldFlag=hold_already_9000;
          else if(hold_start_other)
            Key.HoldFlag=hold_already_other;
      }
    }

}
//****************************************************************//
//函数名称: void Is_Key_Press(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Is_Key_Press(void){

   std_gpio_init_t Key_Gpio_Init = {0};
   uint8_t cache,is_enable_lptime=0;
   cache=  Key_State_Read();
   if(cache&KEY_MINUTES){

    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLDOWN;
    
    Key_Gpio_Init.pin =  KEY_MINUTE_PIN;
    std_gpio_init(KEY_MINUTE_PORT, &Key_Gpio_Init);
     Key.Key_Config_PuDown=KEY_MINUTES;
    is_enable_lptime++;
   }
   if(cache&KEY_TIMING){
       
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLDOWN;
    
    Key_Gpio_Init.pin =  KEY_TIMING_PIN;
    std_gpio_init(KEY_TIMING_PORT, &Key_Gpio_Init);
     is_enable_lptime++;
    Key.Key_Config_PuDown|=KEY_TIMING;  
   }
   if(cache&KEY_WEEKS) {
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLDOWN;
    
    Key_Gpio_Init.pin =  KEY_WEEKS_PIN;
    std_gpio_init(KEY_WEEKS_PORT, &Key_Gpio_Init);
    is_enable_lptime++;
    Key.Key_Config_PuDown|=KEY_WEEKS;  
   }
   if(cache&KEY_MODE){
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLDOWN;
    
    Key_Gpio_Init.pin =  KEY_MODE_PIN;
    std_gpio_init(KEY_MODE_PORT, &Key_Gpio_Init);
    is_enable_lptime++;
    Key.Key_Config_PuDown|=KEY_MODE;  
   }
   if(cache&KEY_HOURS){
       
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLDOWN;
    
    Key_Gpio_Init.pin =  KEY_HOURS_PIN;
    std_gpio_init(KEY_HOURS_PORT, &Key_Gpio_Init);
    is_enable_lptime++;
    Key.Key_Config_PuDown|=KEY_HOURS; 
   }
   if(is_enable_lptime>0||Display.fast_disp_channel_times)  {
     LpTime1_Enable();
     Bsp_Key_Exit_Enable();
   }else
     LpTime1_Disable();

}
//****************************************************************//
//函数名称: void Key_Out_Sleep_Config(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2025.10.11 Whm创建函数
//***************************************************************//
void Key_Out_Sleep_Config(void){

   std_gpio_init_t Key_Gpio_Init = {0};

   if(Key.Key_Config_PuDown&KEY_MINUTES){

    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLUP;
    
    Key_Gpio_Init.pin =  KEY_MINUTE_PIN;
    std_gpio_init(KEY_MINUTE_PORT, &Key_Gpio_Init);

   }
   if(Key.Key_Config_PuDown&KEY_TIMING){
       
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLUP;
    
    Key_Gpio_Init.pin =  KEY_TIMING_PIN;
    std_gpio_init(KEY_TIMING_PORT, &Key_Gpio_Init); 
   }
   if(Key.Key_Config_PuDown&KEY_WEEKS) {
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLUP;
    
    Key_Gpio_Init.pin =  KEY_WEEKS_PIN;
    std_gpio_init(KEY_WEEKS_PORT, &Key_Gpio_Init);

   }
   if(Key.Key_Config_PuDown&KEY_MODE){
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLUP;
    
    Key_Gpio_Init.pin =  KEY_MODE_PIN;
    std_gpio_init(KEY_MODE_PORT, &Key_Gpio_Init);

   }
   if(Key.Key_Config_PuDown&KEY_HOURS){
       
    Key_Gpio_Init.mode = GPIO_MODE_INPUT;
    Key_Gpio_Init.pull = GPIO_PULLUP;
    
    Key_Gpio_Init.pin =  KEY_HOURS_PIN;
    std_gpio_init(KEY_HOURS_PORT, &Key_Gpio_Init);

   }

}

