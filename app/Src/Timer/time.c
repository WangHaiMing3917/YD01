#include "system.h"

CURRENT_TIME_STRUCT Current __attribute__ ((aligned (4u)));;
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

     uint8_t enable_count=0;
     uint8_t save_count[56];
     uint8_t save_number=0;
     memset(save_count,0,56);
     //将56组数据有效的定时，且小于当前时间的
     for(uint8_t i=0;i<56;i++){
       //是否使能
       if(Ch->timing[i].enable){
         //有定时使能
         enable_count++;
         //星期有效   
         if((Timing_Week_Mode_Selcet(Ch->timing[i].week)&Current.Week)>0){
            //定时时间小于当前时间   或 定时小时相同，分钟小于或者等于
            if(Ch->timing[i].hour<Current.Hours||((Ch->timing[i].hour==Current.Hours)&&(Ch->timing[i].minutes<=Current.Minute))){
                //存储当前的定时序号
                save_count[save_number]=i+1;
                save_number++; 
            }
         }
       }
     }
     //小于当前时间的定时数组大于0
     if(save_number>0||enable_count){
        uint8_t cache=0;
        for(uint8_t j=save_number;j>0;j--){
        
            for(uint8_t p=1;p<j;p++){
                
              //因为初始的数值+1，所以要-1  将时间数据从小到大排列
              if((Ch->timing[save_count[p-1]-1].hour> Ch->timing[save_count[p]-1].hour)
                ||((Ch->timing[save_count[p-1]-1].hour==Ch->timing[save_count[p]-1].hour)&&(Ch->timing[save_count[p-1]-1].minutes>Ch->timing[save_count[p]-1].minutes))){
                    
                     cache= save_count[p];
                     save_count[p]= save_count[p-1];
                     save_count[p-1]=cache;
              }
            }
        }
        uint8_t error=0;
        
        if(save_number==1){
        //只有一个有效是定时数组  
           __nop();
            
        }else{

          while(save_number){
             error=0; 
             for(uint8_t i=0;i<save_number;i++){
        
               if(Ch->timing[save_count[save_number-1]-1].hour== Ch->timing[save_count[i]-1].hour&&Ch->timing[save_count[save_number-1]-1].minutes== Ch->timing[save_count[i]-1].minutes){
                 //判断是否模式不同
                 if((save_count[save_number-1]%2)!=(save_count[i]%2)){
                  save_count[i]=0;  
                  save_count[save_number-1]=0;
                  error=1;
                 }
               }
             }
             if(save_number==2)
                 break;
             if(error){
               uint8_t cache[56];
               uint8_t cnt=0;
               memset(cache,0,56);               
               for(uint8_t i=0;i<save_number-1;i++){
                   
                 if(save_count[i]>0){
                     cache[cnt]=save_count[i];
                     cnt++;
                 }
               }
               for(uint8_t j=0;j<cnt;j++)
                 save_count[j]=cache[j];
               save_number=cnt;
               if(save_number==1){
                error=0;
                break;
               }
             }
    
             if(error==0)
               break;
          }
        }
        if(save_number||enable_count){
           //定时组不为空 
           if (Ch->Mode!=AUTO_STATE){
               System_Properties_Change_Cal(Ch->Index,Mode_Change);
               Ch->Mode=AUTO_STATE;
           }
           //当前显示通道和下发的通道一致
           if((Ch->Index+1)==Current.channel) {
             Current.Mode=Ch->Mode;
             Lcd_Channel_State_Change_Fast_Flash(6);    
           }
           Ch->Timing_is_Valid=1u;

        } else{
            
           Ch->Timing_is_Valid=0u;
           if(Current.Mode==AUTO_STATE){
             Channel_Control(Ch->Index,RELAY_OFF,change_flag); 
             Ch->Mode=CLOSE_STATE;
             if((Ch->Index+1)==Current.channel)   
               Current.Mode=Ch->Mode;
             System_Properties_Change_Cal(Ch->Index,Mode_Change);
           }
        } 
         //定时值有效    
        if(!error&&save_number){
          
           if(save_count[ save_number-1]%2==0)
            Channel_Control(Ch->Index,RELAY_OFF,change_flag);
           else
            Channel_Control(Ch->Index,RELAY_ON,change_flag);
        }else if(!error&&enable_count)
          Channel_Control(Ch->Index,RELAY_OFF,change_flag);
     }
   //   Lcd_Channel_State_Change_Fast_Flash(6);   
       uint8_t Group_Enable_Cache=0;
      
        for(uint8_t c=0;c<28;c++){
      
         if( Ch->timing[2*c].enable==1|| Ch->timing[2*c+1].enable==1)
           Group_Enable_Cache++; 
         if((Ch->timing[2*c].enable==1)&&(Ch->timing[2*c+1].enable==0)){
           Ch->timing[2*c].disp_none=0;
           Ch->timing[2*c+1].disp_none=1;  
         }else if((Ch->timing[2*c].enable==0)&&(Ch->timing[2*c+1].enable==1)){
           Ch->timing[2*c].disp_none=1;
           Ch->timing[2*c+1].disp_none=0;  
         }
        }
        if(SystemInfo.time_enable_count[Ch->Index]!=Group_Enable_Cache){
           SystemInfo.time_enable_count[Ch->Index]=Group_Enable_Cache;
           System.timer_Enable_Count[Ch->Index]= SystemInfo.time_enable_count[Ch->Index];
           System_Properties_Change_Cal(Ch->Index,Group_Change);    
        }
        if(SystemInfo.crc16!=Crc16_Cal((uint8_t *)&SystemInfo.time_channel,845u))
           System_Properties_Change_Cal(Ch->Index,Group_Time_Change);    
        
        Display.update_lcd=1;
     if(Group_Enable_Cache==0){
     
        if(Current.Mode==AUTO_STATE){
            
           if(SystemInfo.time_channel[Ch->Index].Relays_States)  {
 
              Channel_Control(Ch->Index,RELAY_OFF,change_flag);
           }
           Ch->Mode=CLOSE_STATE;
           Ch->Timing_is_Valid=0;
           System_Properties_Change_Cal(Ch->Index,Mode_Change);
           if((Ch->Index+1)==Current.channel)              
           Current.Mode=Ch->Mode;
        } 
     }
     
     
}
//****************************************************************//
//函数名称: void Timing_Week_Mode_Selcet(void)
//函数功能: 定时星期模式
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Timing_Week_Mode_Selcet(uint8_t Num){

    uint8_t mode=0;
    switch(Num){

       case 0:
           mode=MonDay|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday;
        break;
       case 1:
           mode=MonDay;
        break;
       case 2:
           mode=Tuesday;
        break;
       case 3:
           mode=Wednesday;
        break;
       case 4:
           mode=Thursday;
        break;
       case 5:
           mode=Friday;
        break;   
       case 6:
           mode=Saturday;
        break;
       case 7:
           mode=Sunday;
        break;
       case 8:
           mode=MonDay|Tuesday|Wednesday|Thursday|Friday;
        break;
       case 9:
           mode=Sunday|Saturday;
        break; 
       case 10:
           mode=MonDay|Tuesday|Wednesday|Thursday|Friday|Saturday;
        break; 
       case 11:
           mode=MonDay|Wednesday|Friday;
        break;
       case 12:
           mode=Tuesday|Thursday|Saturday;
        break; 
       case 13:
           mode=MonDay|Tuesday|Wednesday;
        break; 
       case 14:
           mode=Thursday|Friday|Saturday;
        break;
       default:

        break;

    }
  return mode;
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

    uint8_t Number=0;
    switch(Mode){
    
       case (MonDay|Tuesday|Wednesday|Thursday|Friday|Saturday|Sunday):
          Number=0u; 
        break;
       case  MonDay:
          Number=1u;   
        break;
       case  Tuesday:
          Number=2u;    
        break;    
       case  Wednesday:
          Number=3u;   
        break;   
       case  Thursday:
          Number=4u;   
        break;
       case  Friday:
          Number=5u;    
        break;
       case  Saturday:
          Number=6u;    
        break;
       case  Sunday:
          Number=7u;  
        break;
       case (MonDay|Tuesday|Wednesday|Thursday|Friday):
          Number=8u;   
        break;
       case (Sunday|Saturday):
          Number=9u;  
        break;
       case (MonDay|Tuesday|Wednesday|Thursday|Friday|Saturday):
          Number=10u;
        break;
       case (MonDay|Wednesday|Friday):
          Number=11u;
         break;
       case (Tuesday|Thursday|Saturday):
          Number=12u;
         break;
       case  (MonDay|Tuesday|Wednesday):
          Number=13u;
         break;
       case  (Thursday|Friday|Saturday):
          Number=14u; 
         break;
       default: 
        break;
    
    }
   return   Number; 

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
                   //定時的星期包含当前
                  if(Timing_Week_Mode_Selcet(SystemInfo.time_channel[i].timing[j].week)&Current.Week){
                  
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
                  if(SystemInfo.Current_Channel==i)
                    Lcd_Channel_State_Change_Fast_Flash(6);   
                }else  if(Open_Count==0&&Close_Count>0){
                  Channel_Control(SystemInfo.time_channel[i].Index,RELAY_OFF,change_flag);
                  if(SystemInfo.Current_Channel==i)  
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
                   SystemInfo_Save();
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


