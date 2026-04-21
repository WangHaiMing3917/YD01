#include "system.h"

LCD_STRUCT Display;


//****************************************************************//
//函数名称: Lcd_Number_Disp(uint8_t Number,uint8_t pos)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Number_Disp(uint8_t Number,uint8_t pos){

  switch(Number){
  
      case 0:
         Bsp_Disp_A(pos);
         Bsp_Disp_B(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_E(pos);
         Bsp_Disp_F(pos);
       break;
      case 1:
         Bsp_Disp_B(pos);
         Bsp_Disp_C(pos);       
       break;
      case 2:
         Bsp_Disp_A(pos);
         Bsp_Disp_B(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_E(pos);
         Bsp_Disp_G(pos);
       break;
      case 3:
         Bsp_Disp_A(pos);
         Bsp_Disp_B(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_G(pos);   
       break;
      case 4:
         Bsp_Disp_F(pos);
         Bsp_Disp_B(pos);
         Bsp_Disp_G(pos);
         Bsp_Disp_C(pos);   
       break;
      case 5:
         Bsp_Disp_A(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_F(pos);
         Bsp_Disp_G(pos);      
       break;  
      case 6:
         Bsp_Disp_A(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_E(pos);
         Bsp_Disp_F(pos);
         Bsp_Disp_G(pos);       
       break;
      case 7:
         Bsp_Disp_A(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_B(pos);    
       break;
      case 8:
         Bsp_Disp_A(pos);
         Bsp_Disp_B(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_E(pos);
         Bsp_Disp_F(pos); 
         Bsp_Disp_G(pos);        
       break;
      case 9:
         Bsp_Disp_A(pos);
         Bsp_Disp_B(pos);
         Bsp_Disp_C(pos);
         Bsp_Disp_D(pos);
         Bsp_Disp_F(pos); 
         Bsp_Disp_G(pos);      
       break;
      case 255: 
         Bsp_Disp_G(pos);      
         break;
      default:
       break;
  
  }
}
//****************************************************************//
//函数名称: void Lcd_ASCII_Disp(uint8_t ASCII,uint8_t Pos)
//函数功能:   显示ASCII
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_ASCII_Disp(uint8_t ASCII,uint8_t Pos){


    switch(ASCII){
        
        case  ASCII_0:
           Lcd_Number_Disp(0,Pos);
          break;
        case  ASCII_1:
           Lcd_Number_Disp(1,Pos);
          break;
        case  ASCII_2:
           Lcd_Number_Disp(2,Pos);
          break;
        case  ASCII_3:
           Lcd_Number_Disp(3,Pos); 
          break;
        case  ASCII_4:
           Lcd_Number_Disp(4,Pos);
          break;
        case  ASCII_5:
           Lcd_Number_Disp(5,Pos);
          break;
        case  ASCII_6:
           Lcd_Number_Disp(6,Pos);
          break;
        case  ASCII_7:
           Lcd_Number_Disp(7,Pos);
          break;
        case  ASCII_8:
           Lcd_Number_Disp(8,Pos);
          break;
        case  ASCII_9:
           Lcd_Number_Disp(9,Pos);
          break;
        case  ASCII_A:
            Bsp_Disp_ASCII_A(Pos);
          break;
        case  ASCII_B:
            Bsp_Disp_ASCII_B(Pos);  
          break;   
        case  ASCII_C:
            Bsp_Disp_ASCII_C(Pos);    
          break;  
        case  ASCII_D:
            Bsp_Disp_ASCII_D(Pos);   
          break;  
        case  ASCII_E:
            Bsp_Disp_ASCII_E(Pos);     
          break;     
        case  ASCII_F:
            Bsp_Disp_ASCII_F(Pos);     
          break; 
        case  ASCII_G:
            Bsp_Disp_ASCII_G(Pos);    
          break; 
        case  ASCII_H:
            Bsp_Disp_ASCII_H(Pos);  
          break; 
        case  ASCII_I:
            Bsp_Disp_ASCII_I(Pos);  
          break;  
        case  ASCII_J:
            Bsp_Disp_ASCII_J(Pos);   
          break;   
        case  ASCII_K:
            Bsp_Disp_ASCII_K(Pos);    
          break;
        case  ASCII_L:
            Bsp_Disp_ASCII_L(Pos);   
          break;   
        case  ASCII_M:
            Bsp_Disp_ASCII_M(Pos);   
          break;   
        case  ASCII_N:
            Bsp_Disp_ASCII_N(Pos);    
          break;   
        case  ASCII_O:
            Bsp_Disp_ASCII_O(Pos);   
          break;
        case  ASCII_P:
            Bsp_Disp_ASCII_P(Pos);   
          break;   
        case  ASCII_Q:
            Bsp_Disp_ASCII_Q(Pos);   
          break;   
        case  ASCII_R:
            Bsp_Disp_ASCII_R(Pos);    
          break;
        case  ASCII_S:
            Bsp_Disp_ASCII_S(Pos);  
          break;
        case  ASCII_T:
            Bsp_Disp_ASCII_T(Pos);  
          break;   
        case  ASCII_U:
            Bsp_Disp_ASCII_U(Pos);   
          break;   
        case  ASCII_V:
            Bsp_Disp_ASCII_V(Pos);  
          break;
        case  ASCII_W:
            Bsp_Disp_ASCII_W(Pos);   
          break;   
        case  ASCII_X:
            Bsp_Disp_ASCII_X(Pos);   
          break;   
        case  ASCII_Y:
            Bsp_Disp_ASCII_Y(Pos);   
          break;
        case  ASCII_Z:
            Bsp_Disp_ASCII_Z(Pos);   
          break;
        default:
         break;

    }

}
//****************************************************************//
//函数名称: void Lcd_Disp_All(void)
//函数功能: 全显
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_All(void){

  Bsp_Disp_All();

}
//****************************************************************//
//函数名称: void Lcd_Disp_Week(uint8_t weeks)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Week(uint8_t weeks){


      if((weeks&MonDay)==MonDay)
         Bsp_Disp_Monday();
      if((weeks&Tuesday)==Tuesday)
         Bsp_Disp_Tuesday(); 
      if((weeks&Wednesday)==Wednesday)
         Bsp_Disp_Wednesday();  
      if((weeks&Thursday)==Thursday)
         Bsp_Disp_Thursday();  
      if((weeks&Friday)==Friday)
         Bsp_Disp_Friday(); 
      if((weeks&Saturday)==Saturday)
         Bsp_Disp_Saturday(); 
      if((weeks&Sunday)==Sunday)
         Bsp_Disp_Sunday(); 
}
//****************************************************************//
//函数名称: void Lcd_Disp_Mode(uint8_t mode)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Mode(uint8_t mode){

  if( Display.relay_state_flash_flag){
      
      if( !SystemInfo.time_channel[Current.channel-1].Relays_States)
         Bsp_Disp_TimingClose();
      else
         Bsp_Disp_TimingOpen();  
  
  }
  if(!Display.not_disp_mode){

    if((mode&AUTO_STATE)==AUTO_STATE)   
       Bsp_Disp_TimingAuto();  
    if(!Display.relay_state_flash_flag){
        
     if((mode&OPEN_STATE)==OPEN_STATE)
       Bsp_Disp_TimingOpen();
     if((mode&CLOSE_STATE)==CLOSE_STATE)
       Bsp_Disp_TimingClose();
    }

  }

}
//****************************************************************//
//函数名称: void Lcd_Channel_Fast_Flash_Timer(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Channel_Fast_Flash_Timer(void){

   if(Display.fast_disp_channel_times){
   
      if(Display.Fast_disp_channel_Delays){
          
         Display.Fast_disp_channel_Delays--;
         if(Display.Fast_disp_channel_Delays==0u){
             
             Display.channel_fast_flash_flag=~Display.channel_fast_flash_flag;
             Lcd_Fast_Disp_Channel_Delays_Set(2);
             Display.fast_disp_channel_times--;
             if(Display.fast_disp_channel_times==0u){
                Display.channel_fast_flash_enable=0;
             }
            Display.update_lcd=1;
         }
      }
   }
}

//****************************************************************//
//函数名称: void Lcd_Disp_Lock(uint8_t is_lock)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Lock(uint8_t is_lock){

    if(is_lock) {
        
        if(!Display.lock_flash_flag)
          Bsp_Disp_Lock();
    }
}
//****************************************************************//
//函数名称: void Lcd_Disp_Wifi_state(uint8_t state)
//函数功能: 添加wifi连接状态
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Wifi_state(uint8_t state){

   if(!System.is_power_down){
       
      if(!state){
      
         if(Display.lcd_flash_flag)
             Bsp_Disp_Bluetooth();
      }else
         Bsp_Disp_Bluetooth();
   
   }

}
//****************************************************************//
//函数名称: void lcd_disp_flash(uint8_t times ,uint8_t delays)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void lcd_disp_flash(uint8_t times){
    
     if(!Display.lock_flash_enable){
       Display.lock_flash_enable=1;
       Display.locked_flash_times=times;
     }else
       Display.locked_flash_times=times;
     Display.update_lcd=1;
}
//****************************************************************//
//函数名称: void Lcd_disp_lock_flash_timer(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_disp_lock_flash_timer(void){

    if(Display.locked_flash_times&&Display.lock_flash_enable==1){
    
       Display.locked_flash_times--;
 
       Display.lock_flash_flag=~Display.lock_flash_flag;
       if(Display.locked_flash_times==0){
         Display.lock_flash_flag=0;  
         Display.lock_flash_enable=0;
       }           
       Display.update_lcd=1;
    }else{
       Display.lock_flash_enable=0;
    }
}
//****************************************************************//
//函数名称: void Lcd_BackLight_Open(void)
//函数功能: 背光灯控制
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_BackLight_Open(void){
    
   System_Back_Led_Open();
   System.back_led_delays=60;

}
//****************************************************************//
//函数名称: Lcd_PowerOn_Display
//函数功能: 上电显示
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_PowerOn_Display(void){
   
   uint16_t Factory_Check_Cnt =1050u;
   uint16_t Power_On_Delays   =1000u;
    
   System.wait_into_factory=0;
    
   Bsp_IWDG_ReFresh(); 
    
   if(!Bsp_Hour_Key_Read()) 
     System.wait_into_factory=1;
   
   Lcd_Disp_All();
   //背光计时开始
   Lcd_BackLight_Open();
   
   if(!Bsp_Hour_Key_Read() && System.wait_into_factory)
      Factory_Check_Cnt=1000u; 
   
   while(Power_On_Delays--){
   
     std_delayms(1u);
       
     if(!Bsp_Hour_Key_Read() && System.wait_into_factory){
         
       Factory_Check_Cnt--;
         
       if(Factory_Check_Cnt>1000)
         Factory_Check_Cnt=0;  
     }
   }
   //0.5S-1S内允许进入工厂模式
   if(Factory_Check_Cnt<950u&&Factory_Check_Cnt>450u){
       
      System_Mode_Set(Factory_Mode);
       
      factory.item = factory_disp_current_channel; 
       
      factory.delays=1000u;
       
   }else
      System_Mode_Set(Normal_Mode);
   
   Display.update_lcd=1;
   


}
//****************************************************************//
//函数名称: void Lcd_Disp_Version_And_Name(void)
//函数功能: 显示版本和名称
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Factory_Disp_Version_And_Name(void){

    uint8_t Version_H=0;
    uint8_t Version_L=0;
    Version_H= VERSION_H;
    Version_L= VERSION_L*10;
    //显示版本
    Lcd_Number_Disp(Version_H,Timing_Decade);
    Lcd_Number_Disp(Version_L,Timing_Unit);
    
     char *file_name =NULL;
    if(SystemInfo.ChannelCount ==3)
     strcpy(file_name,ThreeChannelInfo[INFO_modle]);
    else
     strcpy(file_name,FiveChannelInfo[INFO_modle]);   
    //显示名称
    Lcd_ASCII_Disp(file_name[0],Hours_Decade);
    Lcd_ASCII_Disp(file_name[1],Hours_Unit);
    Lcd_ASCII_Disp(file_name[2],Minute_Decade);
    Lcd_ASCII_Disp(file_name[3],Minute_Unit);
    Lcd_ASCII_Disp(file_name[4],Sec_Decade);
    Lcd_ASCII_Disp(file_name[5],Sec_Unit);
}
//****************************************************************//
//函数名称: void Lcd_Disp_Factory_Auto(void)
//函数功能: 自动显示
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Factory_Auto(void){
   
   uint8_t data=0;
   switch(factory.disp_item){

       case Factory_Auto_disp_Step_1:
           data=1;
         break;
       case Factory_Auto_disp_Step_2:
           data=2; 
         break;
       case Factory_Auto_disp_Step_3:
           data=3;   
         break;
       case Factory_Auto_disp_Step_4:
           data=4;  
         break;
       case Factory_Auto_disp_Step_5:
           data=5;   
         break;
       case Factory_Auto_disp_Step_6:
           data=6;  
         break;
       case Factory_Auto_disp_Step_7:
           data=7; 
         break;
       case Factory_Auto_disp_Step_8:
           data=8;   
         break;
       case Factory_Auto_disp_Step_All:
          LCD_ARRAY.RAM0=0xffffffff;
          LCD_ARRAY.RAM1=0xffffffff;
          LCD_ARRAY.RAM2=0xffffffff;
          LCD_ARRAY.RAM3=0xffffffff;
         break;
       default:
         break;
   }
   if(factory.disp_item<Factory_Auto_disp_Step_All){
     //显示版本
     Lcd_Number_Disp(data,Timing_Decade);
     Lcd_Number_Disp(data,Timing_Unit);
     //显示名称
     Lcd_Number_Disp(data,Hours_Decade);
     Lcd_Number_Disp(data,Hours_Unit);
     Lcd_Number_Disp(data,Minute_Decade);
     Lcd_Number_Disp(data,Minute_Unit);
     Lcd_Number_Disp(data,Sec_Decade);
     Lcd_Number_Disp(data,Sec_Unit);
   }
}
//****************************************************************//
//函数名称: void Lcd_Disp_Factory_Channel(void)
//函数功能: 显示通道总数
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Factory_Channel(void){

    Lcd_ASCII_Disp(ASCII_C,Hours_Decade);
    Lcd_ASCII_Disp(ASCII_H,Hours_Unit);
    Lcd_ASCII_Disp(SystemInfo.ChannelCount,Minute_Unit);
}

//****************************************************************//
//函数名称: void Lcd_Disp_Factory_Key_Press(void)
//函数功能: 工厂按键测试
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Factory_Key_Press(void){

     
   switch(factory.key_item){
       case Factory_Key_Step_None:
          LCD_ARRAY.RAM0=0x00;
          LCD_ARRAY.RAM1=0x00;
          LCD_ARRAY.RAM2=0x00;
          LCD_ARRAY.RAM3=0x00;   
          break;
       case Factory_Key_Step_1:

          Lcd_Number_Disp(1,Hours_Unit);
          break;
       case Factory_Key_Step_2:
          Lcd_Number_Disp(2,Hours_Unit);
          break;   
       case Factory_Key_Step_3:
          Lcd_Number_Disp(3,Hours_Unit);
          break;
       case Factory_Key_Step_4:
          Lcd_Number_Disp(4,Hours_Unit);
          break;   
       case Factory_Key_Step_5:
          Lcd_Number_Disp(5,Hours_Unit);
          break;
       default:
          break;
   }
    Lcd_Disp_Wifi_state(Display.disp_wifi); 
}
//****************************************************************//
//函数名称: void Lcd_Disp_Factory_Key_Press(void)
//函数功能: 工厂按键测试
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Factory_Relay_Count(uint16_t value,uint8_t index){

    Lcd_Number_Disp(index,Timing_Decade);
    
    Lcd_Number_Disp(value/100000,Hours_Decade);
    Lcd_Number_Disp(value%100000/10000,Hours_Unit);
    
    Lcd_Number_Disp(value%100000%10000/1000,Minute_Decade);
    Lcd_Number_Disp(value%100000%10000%1000/100,Minute_Unit);
    
    Lcd_Number_Disp(value%100000%10000%1000%100/10,Sec_Decade);
    Lcd_Number_Disp(value%100000%10000%1000%100%10,Sec_Unit);

}
//****************************************************************//
//函数名称: void Lcd_Disp_Channel(uint8_t channel)
//函数功能: 显示通道号
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Channel(uint8_t channel){
   
    if(Display.channel_fast_flash_enable){
        
        if(!Display.channel_fast_flash_flag)
             Lcd_Number_Disp(channel,Timing_Decade);

    }else{
    
        Lcd_Number_Disp(channel,Timing_Decade);
    }

}
//****************************************************************//
//函数名称: void Lcd_Disp_Current_Clock(void)
//函数功能: 显示当前时间
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Current_Clock(void){
    

    Lcd_Number_Disp(Current.Hours/10,Hours_Decade);
    Lcd_Number_Disp(Current.Hours%10,Hours_Unit);
    
    Lcd_Number_Disp(Current.Minute/10,Minute_Decade);
    Lcd_Number_Disp(Current.Minute%10,Minute_Unit);

    Lcd_Number_Disp(Current.Sec/10,Sec_Decade);
    Lcd_Number_Disp(Current.Sec%10,Sec_Unit);

    Lcd_Disp_Week(Current.Week);
   
    Lcd_Disp_Channel(Current.channel);

    Lcd_Disp_Mode(Current.Mode);
}

//****************************************************************//
//函数名称: void Lcd_Disp_Hide_Time(void)
//函数功能: 显示横杠
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Hide_Time(void){

     Lcd_Number_Disp(255,Hours_Decade) ;
     Lcd_Number_Disp(255,Hours_Unit) ;
     Lcd_Number_Disp(255,Minute_Decade) ;
     Lcd_Number_Disp(255,Minute_Unit) ; 
    
}

//****************************************************************//
//函数名称: void Lcd_Disp_Set_Timing(uint8_t Channel_Num,uint8_t TimingIndex)
//函数功能: 定时时间
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Set_Timing(uint8_t Channel_Num,uint8_t TimingIndex){


       if(!SystemInfo.time_channel[Channel_Num-1].timing[TimingIndex].enable){
            
            Lcd_Disp_Hide_Time();
            Lcd_Disp_Week(WeekModeTable[0]);  
       }else {
            Lcd_Number_Disp(SystemInfo.time_channel[Channel_Num-1].timing[TimingIndex].hour/10,Hours_Decade) ;
            Lcd_Number_Disp(SystemInfo.time_channel[Channel_Num-1].timing[TimingIndex].hour%10,Hours_Unit) ;
            Lcd_Number_Disp(SystemInfo.time_channel[Channel_Num-1].timing[TimingIndex].minutes/10,Minute_Decade) ;
            Lcd_Number_Disp(SystemInfo.time_channel[Channel_Num-1].timing[TimingIndex].minutes%10,Minute_Unit) ; 
            Lcd_Disp_Week(WeekModeTable[SystemInfo.time_channel[Channel_Num-1].timing[TimingIndex].week]);
       }
       
       Lcd_Number_Disp(Channel_Num,Sec_Unit); 

       if(!Display.lcd_flash_flag){
         if(((TimingIndex+2)%2)==0)
           Lcd_Disp_Mode(OPEN_STATE);
         else
           Lcd_Disp_Mode(CLOSE_STATE);
         TimingIndex= TimingIndex+1;
 
         Lcd_Number_Disp((TimingIndex+1)/2/10,Timing_Decade);
         Lcd_Number_Disp((TimingIndex+1)/2%10,Timing_Unit);
       }
}
//****************************************************************//
//函数名称: void Lcd_Disp_Set_CurrentTime(uint8_t Flash_Pos)
//函数功能: 定时时间
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Set_CurrentTime(uint8_t Flash_Pos){

    switch(Flash_Pos){
        case Hours_Flash:
             if(!Display.lcd_flash_flag){
                Lcd_Number_Disp(Current.Hours/10,Hours_Decade) ;
                Lcd_Number_Disp(Current.Hours%10,Hours_Unit) ;
             }
            Lcd_Number_Disp(Current.Minute/10,Minute_Decade) ;
            Lcd_Number_Disp(Current.Minute%10,Minute_Unit) ;
             
            Lcd_Disp_Week(Current.Week);
            Lcd_Disp_Mode(Current.Mode);
             
            Lcd_Number_Disp(Current.Sec/10,Sec_Decade) ;
            Lcd_Number_Disp(Current.Sec%10,Sec_Unit);  
             
          break;
        case Minute_Flash:
      
            Lcd_Number_Disp(Current.Hours/10,Hours_Decade) ;
            Lcd_Number_Disp(Current.Hours%10,Hours_Unit) ;
            if(!Display.lcd_flash_flag){              
                Lcd_Number_Disp(Current.Minute/10,Minute_Decade) ;
                Lcd_Number_Disp(Current.Minute%10,Minute_Unit) ;
            }
            Lcd_Disp_Week(Current.Week);
            Lcd_Disp_Mode(Current.Mode);  
            Lcd_Number_Disp(Current.Sec/10,Sec_Decade) ;
            Lcd_Number_Disp(Current.Sec%10,Sec_Unit);  
             
          break;
        case Week_Flash:
            Lcd_Number_Disp(Current.Hours/10,Hours_Decade) ;
            Lcd_Number_Disp(Current.Hours%10,Hours_Unit) ;
              
            Lcd_Number_Disp(Current.Minute/10,Minute_Decade) ;
            Lcd_Number_Disp(Current.Minute%10,Minute_Unit) ;
        
            Lcd_Disp_Mode(Current.Mode); 
            if(!Display.lcd_flash_flag)
              Lcd_Disp_Week(Current.Week);
            Lcd_Number_Disp(Current.Sec/10,Sec_Decade) ;
            Lcd_Number_Disp(Current.Sec%10,Sec_Unit);  
            
            
          break;
        default:
          break;
    }

}
//****************************************************************//
//函数名称: Lcd_Display
//函数功能: 液晶显示处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Disp_Col(void){

   if(Display.col_not_flash)
     Bsp_Disp_Col();
   else{
     if(!Display.lcd_flash_flag)
      Bsp_Disp_Col();
   }
}
//****************************************************************//
//函数名称: Lcd_Display
//函数功能: 液晶显示处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Display(void){


   if(Display.update_lcd){
    
      Display.update_lcd=0;
      Bsp_Clear_Lcd_Ram_Arrary(); 
       
      switch(System_Mode_Read()){
          case Normal_Mode:

             Lcd_Disp_Current_Clock();
             Lcd_Disp_Lock(SystemInfo.keylocked);
          
             Lcd_Disp_Wifi_state(Display.disp_wifi);
          
             Lcd_Disp_Col();

            break;
          case Select_Channel_Mode:
              
             Lcd_ASCII_Disp(ASCII_C,Hours_Decade);
             Lcd_ASCII_Disp(ASCII_H,Hours_Unit);
             //当前通道
             if(!Display.lcd_flash_flag)
             Lcd_ASCII_Disp(System.timing_channel_number,Minute_Unit);
          
            break;
          case Set_Current_Hours_Mode:
            Lcd_Disp_Col();
            Lcd_Disp_Set_CurrentTime(Hours_Flash);
            break;
          case Set_Current_Minutes_Mode:
            Lcd_Disp_Col();
            Lcd_Disp_Set_CurrentTime(Minute_Flash);   
          
            break;
          case Set_Current_Week_Mode:
            Lcd_Disp_Col();
            Lcd_Disp_Set_CurrentTime(Week_Flash); 
            break;
          case Set_Timing_Mode:
              Lcd_Disp_Col();
              Lcd_Disp_Set_Timing(System.timing_channel_number,System.timing_index);
              
            break;

          case Factory_Mode:
              switch(factory.item){
                   //显示版本和型号
                  /*
                  case factory_disp_ver_name:
                      Lcd_Factory_Disp_Version_And_Name();
                    break;
                  */
                  //显示当前是几路
                  case factory_disp_current_channel:
                      Lcd_Disp_Factory_Channel();
                    break;
                  
                  //循环显示1-8，全显后关闭
                  case factory_disp_number:
                      Lcd_Disp_Factory_Auto();
                    break;
                  //继电器打开，并且提示也打开
                  case factory_control_relays:
                      Factory_Relay_Test();
                    break;
                  //按键显示1-5
                  case factory_test_key:
                      Lcd_Disp_Factory_Key_Press();
                    break;
                  case factory_disp_relay_count:
                     Lcd_Disp_Factory_Relay_Count(factory.relays_count,factory.channel);
                    break;
                  default:
                    break;
              }
            break;
          default:
            break;
      }
      Bsp_Write_To_LCD_RAM((uint32_t*)&LCD_ARRAY.RAM0);
   
   }
}

//****************************************************************//
//函数名称:void  Lcd_Fast_Disp_Channel_Delays_Set(uint16_t delays)
//函数功能: 设置延时时间
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void  Lcd_Fast_Disp_Channel_Delays_Set(uint16_t delays){
    
        Display.Fast_disp_channel_Delays=delays;
}
    
//****************************************************************//
//函数名称: void Lcd_Fast_Disp_Channel_Into(uint8_t times,uint16_t delays)
//函数功能: 快速显示通道
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Fast_Disp_Channel_Into(uint8_t times,uint16_t delays){
    
      Display.channel_fast_flash_enable=1;
      Display.fast_disp_channel_times=times;
      Lcd_Fast_Disp_Channel_Delays_Set(delays);

}

//****************************************************************//
//函数名称: void Lcd_Fast_Disp_Channel_Out(void)
//函数功能: 推出通道快闪
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Fast_Disp_Channel_Out(void){
    
      Display.channel_fast_flash_enable=0;
      Display.fast_disp_channel_times=0;
      Display.Fast_disp_channel_Delays=0;

}


//****************************************************************//
//函数名称: void Lcd_Channel_State_Change_Fast_Flash(uint8_t times )
//函数功能: 继电器状态改变快闪
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Channel_State_Change_Fast_Flash(uint8_t times ){
    
   Display.relay_state_flash_enable =1;
   Display.relay_state_flash_flag=0;
   Display.releay_state_change_times    =   times;

}
//****************************************************************//
//函数名称: void Lcd_Channel_StateFlash_Timer(void)
//函数功能: 状态闪烁
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Channel_StateFlash_Timer(void){

     if(Display.relay_state_flash_enable&& System_Mode_Read()==Normal_Mode){
         
         Display.releay_state_change_times--;
         Display.relay_state_flash_flag=~ Display.relay_state_flash_flag;
         if(!Display.releay_state_change_times){
           Display.relay_state_flash_enable=0;
           Display.relay_state_flash_flag=0;
         }
        Display.update_lcd=1;

     }else{
        Display.relay_state_flash_enable=0;
        Display.relay_state_flash_flag=0;
        Display.releay_state_change_times=0; 
     }
     

}


//****************************************************************//
//函数名称: void Lcd_Wifi_disp_set(uint8_t on_off)
//函数功能: wifi显示设置
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Lcd_Wifi_disp_set(uint8_t on_off) {

     Display.disp_wifi=on_off;
     Display.update_lcd=1;
}

