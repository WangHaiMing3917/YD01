#include "system.h"

FACTORY_STRUCT factory;




//****************************************************************//
//函数名称: void Factory_Send_Connect_Wifi(void)
//函数功能: 配置进入工厂模式
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Factory_Send_Connect_Wifi(void){

  if(System_Mode_Read()==Factory_Mode){

    if(factory.item==factory_test_key){   
        
        if(!factory.will_connect_wifi){
            
           factory.will_connect_wifi=1;
            
           Protocol_Send_Factory();
            
        }
    }

  }
}
//****************************************************************//
//函数名称: void Factory_Cyc_Check_Net(void)
//函数功能: 工厂模式循环确认是否已经成功连接Wifi
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Factory_Cyc_Check_Net(void){

   SystemInfo.wifi_in_factory=1;
//   SystemInfo_Save(); 
   factory.factory_check_net_delays=500;
}
//****************************************************************//
//函数名称: void Factory_Check_Net_Timer(void)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Factory_Check_Net_Timer(void){

    if(!Display.disp_wifi&&SystemInfo.wifi_in_factory){
    
        if(factory.factory_check_net_delays){
        
            if(--factory.factory_check_net_delays==0){
                
               Protocol_Cmd_Cache(CMD_GET_NET);
                
               factory.factory_check_net_delays=500; 
            }
        }
    
    }
    
}
//****************************************************************//
//函数名称: Factory_Relay_Test(void)
//函数功能: 继电器测试
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Factory_Relay_Test(void){

   Bsp_Clear_Lcd_Ram_Arrary();
   Channel_ALL_ON();
}
//****************************************************************//
//函数名称: Factory_Key_Release_ConnectWifi(void)
//函数功能: 按键松开后连接wifi
//参    数:
//返 回 值:
//说    明:
//修改记录: 2025.10.11 Whm创建函数
//***************************************************************//
void Factory_Key_Release_ConnectWifi(void){

   //工厂模式下按键松开后连接wifi
   if(factory.item==factory_test_key){
       
       factory.key_item=Factory_Key_Step_None;
       
       Factory_Send_Connect_Wifi();
       
       Display.update_lcd=1;
   }
}





































