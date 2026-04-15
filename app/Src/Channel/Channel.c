#include "system.h"


RELAY_STRUCT RELAYS_INDEX[5]={

  {(GPIO_t*)RELAYS_CHANNEL_1_PORT,RELAYS_CHANNEL_1_PIN},
  {(GPIO_t*)RELAYS_CHANNEL_2_PORT,RELAYS_CHANNEL_2_PIN},
  {(GPIO_t*)RELAYS_CHANNEL_3_PORT,RELAYS_CHANNEL_3_PIN},
  {(GPIO_t*)RELAYS_CHANNEL_4_PORT,RELAYS_CHANNEL_4_PIN},
  {(GPIO_t*)RELAYS_CHANNEL_5_PORT,RELAYS_CHANNEL_5_PIN},
};





//****************************************************************//
//函数名称: void Channel_Control(uint8_t index,uint8_t state,uint8_t flag)
//函数功能: 继电器近控制不更改状态
//参    数: index 0-5 state 状态 flag 是否上报状态
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Channel_Control(uint8_t index,uint8_t state,uint8_t flag){

    if(state){

        Bsp_Relays_Open(RELAYS_INDEX[index].port_t,RELAYS_INDEX[index].pin);
        
        SystemInfo_Relay_Count_Increase(index);
        
       if(flag)
         SystemInfo.time_channel[index].Relays_States=1u;
    }else{
      Bsp_Relays_Close(RELAYS_INDEX[index].port_t,RELAYS_INDEX[index].pin);
      if(flag)
        SystemInfo.time_channel[index].Relays_States=0u;
    }
    System_Properties_Change_Cal(index,Switch_Change); 
}

//****************************************************************//
//函数名称: void Channel_ALL_OFF(void)
//函数功能: 通道全关
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Channel_ALL_OFF(void){

     for(uint8_t i=0;i<SystemInfo.ChannelCount;i++)
       Channel_Control(i,RELAY_OFF,change_flag);
}

//****************************************************************//
//函数名称: void Channel_ALL_ON(void)
//函数功能: 通道全开
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Channel_ALL_ON(void){

     for(uint8_t i=0;i<SystemInfo.ChannelCount;i++)
       Channel_Control(i,RELAY_ON,change_flag);
}
//****************************************************************//
//函数名称: void Channel_Mode_Changed(void)
//函数功能: 通道模式切换
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Channel_Mode_Changed(void){


                   
      if(SystemInfo.time_channel[Current.channel-1].Timing_is_Valid){
         
         if(SystemInfo.time_channel[Current.channel-1].Mode==CLOSE_STATE)
            SystemInfo.time_channel[Current.channel-1].Mode=AUTO_STATE;
         else
            SystemInfo.time_channel[Current.channel-1].Mode>>=1;
      }else{
       
         if(SystemInfo.time_channel[Current.channel-1].Mode==OPEN_STATE)
            SystemInfo.time_channel[Current.channel-1].Mode=CLOSE_STATE;
         else
            SystemInfo.time_channel[Current.channel-1].Mode=OPEN_STATE;  
      }
      Current.Mode= SystemInfo.time_channel[Current.channel-1].Mode;
      //当前定时组数据比对
      if(SystemInfo.time_channel[Current.channel-1].Mode==AUTO_STATE)
         Check_Near_CurrentTime_Arrary((TIMING_INFO*)&(SystemInfo.time_channel[Current.channel-1]));  
      else{
         Display.relay_state_flash_flag=0;
         Display.relay_state_flash_enable=0;
      }
      if( Current.Mode==CLOSE_STATE)
         Channel_Control(Current.channel-1,RELAY_OFF,change_flag);
      else  if( Current.Mode==OPEN_STATE)
         Channel_Control(Current.channel-1,RELAY_ON,change_flag);

      Display.not_disp_mode=0;     //显示模式
      Display.update_lcd=1;
             
      System_Properties_Change_Cal(Current.channel-1,Mode_Change); 

}



