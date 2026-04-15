#include "system.h"

SYSTEM_STRUCT System __attribute__ ((aligned (4u)));

SYSTEM_INFO_STRUCT SystemInfo __attribute__ ((aligned (4u)));

//const BIN_FILE_NAME(file_name[16u]);
//设备model
//const MODEL_NAME(model_name[50]);

const uint16_t VERSION __attribute__ ((at(0x08003000))) =MCU_VERSION;

typedef  void (*pFunction)(void);

 /* 跳转函数 */

pFunction Jump_To_BootLoader;

/* 跳转地址,中间变量作用 */

uint32_t JumpAddress; 

//****************************************************************//
//函数名称: System_PowerOn_Process(void)
//函数功能: 系统上电
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerOn_Process(void){

   memset(&System, 0, sizeof(System));
   //系統数据读取
   SystemInfo_Memory_Init() ;
   //液晶上电显示 
   Lcd_PowerOn_Display(); 
   //初始当前时间 
   Current_Clock_Init();  
   //使能低功耗时钟 
   LpTime1_Enable();     
   //上电低压检测处理
   System_PowerOn_Voltage_Detect();
}
//****************************************************************//
//函数名称: System_ChannelNumber_Check(void)
//函数功能: 系统通道数量确认
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_ChannelNumber_Check(void){

  uint8_t data = SystemInfo.ChannelCount;
    
  if(Bsp_ChannelMode_Detect())
    SystemInfo.ChannelCount = 3; 
  else
    SystemInfo.ChannelCount = 5;
  
  if(data != SystemInfo.ChannelCount){
      
     SystemInfo.is_request_save = 1u;
     //将数据写入Flash的第一行
//     SystemInfo_Save();
  }

}
//****************************************************************//
//函数名称: System_Mode_Set(uint8_t mode)
//函数功能: 系统模式设置
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Mode_Set(uint8_t mode){

   System.mode = mode;
    
}
//****************************************************************//
//函数名称: uint8_t System_Mode_Read(void)
//函数功能: 系统模式设置
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t System_Mode_Read(void){

  return System.mode;
}


//****************************************************************//
//函数名称: void System_Config_Load(void)
//函数功能: 系统数据载入
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Config_Load(void){
    
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
//函数名称: void System_TimeOut_Set(uint16_t times)
//函数功能: 设置退出返回
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_TimeOut_Set(uint16_t times){

     System.TimeOut=times;

}
//****************************************************************//
//函数名称: void System_TimeOut_Clear(void)
//函数功能: 清除时候
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_TimeOut_Clear(void){

    System.TimeOut=0;

}
//****************************************************************//
//函数名称: void System_Factory_Disp_Timer(void)
//函数功能: 工厂模式显示定时
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Factory_Disp_Timer(void){
    
    if(factory.delays){
       
      factory.delays--;
       
      if(factory.delays==0){
          
         if(factory.item<factory_test_key){
         
            if(factory.item!=2){
                
              factory.item++;
                
              if(factory.item==factory_disp_number)
                  factory.delays=300u;
              else
                  factory.delays=1000u;
              if(factory.item==factory_test_key){
                  Channel_ALL_OFF();
              } 
            }else{
                
              if(factory.disp_item<Factory_Auto_disp_Step_All){
                 
                  factory.disp_item++;
                  
                  if(factory.disp_item<Factory_Auto_disp_Step_All)
                     factory.delays=300u;
                  else
                     factory.delays=1000u;//全显1S
              }else{
                  
                  factory.item++;
                  
                  factory.disp_item=0;
                  
                  factory.delays=1000u;//全显1S
              }
            }
            Display.update_lcd=1;
         }
      }
   }
}
//****************************************************************//
//函数名称: System_Out_Current_TimeSet
//函数功能: 系统退出当前时间设置
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Out_Current_TimeSet(void){

     Display.col_not_flash=0u;
     Display.not_disp_mode=0u;
   
}
//****************************************************************//
//函数名称: void System_1ms_Timer(void)
//函数功能: 系统1ms定时
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_1ms_Timer(void){

    if(System.wait_connect_wifi_delays){

       if(--System.wait_connect_wifi_delays==0){
          //模块交互步骤
          System.Model_Interactive_Step=Send_Model;
          //准备交互模块
          System.will_interactive_model=1;
       }
    }
    //get_down延时
    if(System.send_get_down_enable){

      if( System.get_down_delays){

        if(--System.get_down_delays==0){
            
           Protocol_Cmd_Cache(CMD_GET_DOWN);
                //100ms 
           System.get_down_delays=150;
        }
      }
   }  
       Factory_Check_Net_Timer(); 
}
//****************************************************************//
//函数名称: void System_Wifi_Connect_Init(void)
//函数功能: wifi连接初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Wifi_Connect_Init(void){

     Usart_Init();
         
     Bsp_Time8_Init();

}
//****************************************************************//
//函数名称: void System_Wifi_Connect_DeInit(void)
//函数功能: wifi连接去初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Wifi_Connect_DeInit(void){

     Usart_DeInit();
          
     Bsp_Time8_Deinit();

}
//****************************************************************//
//函数名称: void System_PowerDown_UpdateStateProcess(void)
//函数功能: 系统掉电后更新状态处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerDown_UpdateStateProcess(void){
    
    //如果在升级过程中掉电
    if(SystemInfo.system_state!=normal){
       
       SystemInfo.system_state=update_power_down;
        
       SystemInfo.is_request_save=1;
           
//       SystemInfo_Save();
        
       Update_PowerDown_error_clear_All();    
       //取消发射
       Searil.Tx_State=Tx_Idle;  
    }
}
//****************************************************************//
//函数名称: void System_Connect_Wifi_Process(void)
//函数功能: 系统上电
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Connect_Wifi_Process(void){
    
      //配置wifi需要用的硬件  
      System_Wifi_Connect_Init();

       //等待2秒配置无线 
      if(SystemInfo.system_state==normal){
         //1秒后开始连接wifi
         System.wait_connect_wifi_delays=200;
         
         if(SystemInfo.wifi_in_factory)
           Protocol_Send_Restor();
       
      }else if(SystemInfo.system_state==update_fail) {
       
         System.send_update_fail_enable=1;
          
         System.update_fail_send_times=0;
           
         System.update_fail_send_delays=200;
         
      }
}

//****************************************************************//
//函数名称: System_PowerState_Change_HardwareProcess
//函数功能: 系统电压改变硬件处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerState_Change_HardwareProcess(void){

   if(!System.is_power_down){
     //未掉电判断Wifi有无初始化，关闭所有外部中断，打开掉电中断
     if(!System.wifi_hardware_is_init){
         
       System.wifi_hardware_is_init=1;  
       //关闭按键中断    
       Bsp_Key_Exit_Disable();
       //配置掉电中断  
       System_PowerDown_Exit_Config();
         
       System_Connect_Wifi_Process();
     }
     
   }else{
        
      if(System.wifi_hardware_is_init){
          
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
          
         Into_Sleep_Mode(); 
      }
    }

}
//****************************************************************//
//函数名称: System_Power_Down_Detect
//函数功能: 低压监测
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerOn_Voltage_Detect(void){
    
    uint8_t state = Bsp_Power_Down_Scan();
    
    if(!state)
       //掉电关继电器，关背光灯，设置低压标志位
       Power_Down_Process();
    else
       //删除低压标志位
       Power_Down_Restore();
    
    //根据电压状态配置电源
    System_PowerState_Change_HardwareProcess();
      //系统已初始化完毕
    System.power_on_init=1; 
}
//****************************************************************//
//函数名称: uint8_t Number_Of_Pid(uint16_t number)
//函数功能: Pid数值位数
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Number_Of_Pid(uint16_t number){

     uint8_t pos=1;
     if((number/10000)>0)
         pos=5;
     else if((number/1000)>0)
         pos=4;
     else if((number/100)>0) 
         pos=3;
     else if((number/10)>0)
         pos=2;
     return pos;
}
//****************************************************************//
//函数名称: void Searil_Timer(void)
//函数功能: 串口定时
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Searil_Timer(void){

   //wifi连接超时
   if(Searil.connect_wifi_time_out){
   
     if(--Searil.connect_wifi_time_out==0){
        
       if((System.Model_Interactive_Step==Send_Model)||(System.Model_Interactive_Step==Send_Mcu_Version)||
         (System.Model_Interactive_Step==Send_Ble_config)){
          //重新发射连接指令
          System.will_interactive_model=1;
         
       }
     }
   }

}
//****************************************************************//
//函数名称: void System_PowerOn_ConfigModel(void)
//函数功能: 系统还未完全上电处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerOn_ConfigModel(void){

  
  if(!System.will_interactive_model|| System_Mode_Read()==Factory_Mode||SystemInfo.system_state)
      return;
  
   System.will_interactive_model=0;
   //配置阶段停止发射get_down
   System_Disable_Send_Get_Down();
   //上电发射设置model
   if( System.Model_Interactive_Step==Send_Model){
     uint8_t len=0; 
     //定义一个特点长度的数组 
     if(SystemInfo.ChannelCount==3)
       len=   (strlen(ThreeChannelInfo[INFO_modle])+strlen(Cmd_Table[INDEX_CMD_MODEL]))*sizeof(char);
     else
       len=   (strlen(FiveChannelInfo[INFO_modle])+strlen(Cmd_Table[INDEX_CMD_MODEL]))*sizeof(char);
     
      char send_model_name[len];
     //填充model到数组
     strcpy(send_model_name,Cmd_Table[INDEX_CMD_MODEL]);
       
     //将字符串连接起来
     if(SystemInfo.ChannelCount==3)
       strcat(send_model_name,ThreeChannelInfo[INFO_modle]);
     else
       strcat(send_model_name,FiveChannelInfo[INFO_modle]);
       
     strcpy(Searil.TxBuf,(char*)send_model_name); 
       
     Protocol_TxBuf_Fill(strlen(send_model_name)*sizeof(char)+1,wait_feedback_set_model);
     //连接wifi超时计数
     Searil.connect_wifi_time_out=200u;
       
     Searil.Tx_State=Tx_Request;  
     
   }else if(System.Model_Interactive_Step==Send_Ble_config){
     
       
     uint8_t arrary_number;
     char cmd_set[5]=" set ";

     //计算数组总长度，不算截止符
     if(SystemInfo.ChannelCount==3)
      arrary_number= (strlen(ThreeChannelInfo[INFO_SerialNum])+strlen(Cmd_Table[INDEX_CMD_BLE_CONFIG])+strlen(cmd_set))*sizeof(char)+5;
     else
      arrary_number= (strlen(FiveChannelInfo[INFO_SerialNum])+strlen(Cmd_Table[INDEX_CMD_BLE_CONFIG])+strlen(cmd_set))*sizeof(char)+5;
     
    // char device_pid[Number_Of_Pid(DEVICE_PID)];
       
     char send_ble_config[arrary_number];
       
     char version[5];
     version[0]=' ';     
     version[1]=DEVICE_VERSION/1000+'0';
     version[2]=DEVICE_VERSION%1000/100+'0';
     version[3]=DEVICE_VERSION%1000%100/10+'0';
     version[4]=DEVICE_VERSION%1000%100%10+'0';
     strcpy(send_ble_config,Cmd_Table[INDEX_CMD_BLE_CONFIG]);
     strcat(send_ble_config,cmd_set);
       
   //  sprintf(device_pid,"%d",DEVICE_PID);
     if(SystemInfo.ChannelCount==3)
       strcat(send_ble_config,ThreeChannelInfo[INFO_SerialNum]);
     else
       strcat(send_ble_config,FiveChannelInfo[INFO_SerialNum]);
     
     strcat(send_ble_config,version);
     
     strcpy(Searil.TxBuf,(char*)send_ble_config); 
       
     Protocol_TxBuf_Fill(arrary_number+1,wait_feedback_ble_config); 
     
     Searil.Tx_State=Tx_Request;
     
     Searil.connect_wifi_time_out=200;
     
   } else if(System.Model_Interactive_Step==Send_Mcu_Version ){
    
      char number[5]={0};
      char send_mcu_version[(strlen(Cmd_Table[INDEX_CMD_MCU_VERSION])+strlen(number))*sizeof(char)];
      number[0]=' ';
      number[1]=VERSION/1000+'0';
      number[2]=VERSION%1000/100+'0';
      number[3]=VERSION%1000%100/10+'0';
      number[4]=VERSION%1000%100%10+'0';
      strcpy(send_mcu_version,Cmd_Table[INDEX_CMD_MCU_VERSION]);
      strcat(send_mcu_version,number);
      
      strcpy(Searil.TxBuf,(char*)send_mcu_version); 
       
      Protocol_TxBuf_Fill(strlen(send_mcu_version)+1,wait_feeback_send_mcu_vesrion); 
      
      Searil.connect_wifi_time_out=200;
      
      Searil.Tx_State=Tx_Request;
      
   }
}

//****************************************************************//
//函数名称: void System_Number_To_ASSIIC(uint8_t number)
//函数功能: 数值转换成ASSIIC
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
char System_Number_To_ASSIIC(uint8_t number){

    char value=0;
    if(number==0)
      value=number+0x30;   
    else if(number>0&&number<=9)
      value=number+0x30;
    else if(number>=10&&number<=15)
      value=number+0x57;  
    
    return   value;

}
//****************************************************************//
//函数名称: uint8_t System_Char_To_Number(char data)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t System_Char_To_Number(char data){
    
    uint8_t number=0;
    if(data<=0x39&&data>=0x30){
    
      number=data-0x30;

    }else if(data<=0x66&&data>=0x61)
      number=data-0x57;
    
   return  number;
}
//****************************************************************//
//函数名称: void System_JumpBoot_DeintProcess(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_JumpBoot_DeintProcess(void){

     NVIC_DisableIRQ(LPUART1_IRQn);
     NVIC_DisableIRQ(TIM8_IRQn);  
     NVIC_DisableIRQ(RTC_TAMP_IRQn);
     NVIC_DisableIRQ(LPTIM1_IRQn);
     NVIC_DisableIRQ(EXTI4_15_IRQn);
     NVIC_DisableIRQ(EXTI0_1_IRQn);
     NVIC_DisableIRQ(EXTI2_3_IRQn);
     //去初始化液晶显示
     std_lcd_deinit();
     //RTC去初始化
     std_rtc_deinit();
     //串口去初始化
     Usart_DeInit();
     //定时器8初始化     
     Bsp_Time8_Deinit();
     //去低功耗初始化
     std_lptim_deinit(LPTIM1);
     SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
     SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
     SysTick->LOAD = 0 ; 
}
//****************************************************************//
//函数名称:void Jump_Process(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Jump_Process(void){

    if (((*(__IO uint32_t*)0x08000000) & 0x2FFE0000 ) == 0x20000000){

     /* 跳转到程序运行地址 */

      JumpAddress = *(__IO uint32_t*) (0x08000000 + 4);

     /* 转换为函数类型 */
      __disable_irq();
        
      Jump_To_BootLoader = (pFunction) JumpAddress;
      //关闭所有中断,去初始化外设
      System_JumpBoot_DeintProcess();
      /* 关闭中断 这个非常重要,如果没有关闭boot下的中断,很容易跳到app后被卡死*/

     /* 初始化app栈指针 */

      __set_MSP(*(__IO uint32_t*) 0x08000000);
    
      Jump_To_BootLoader();
    }

}
//****************************************************************//
//函数名称:void System_Enable_Send_Get_Down(void)
//函数功能: 使能打开发射get_Down
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Enable_Send_Get_Down(void){

     System.send_get_down_enable=1;
    
     System.get_down_delays=10;

}
//****************************************************************//
//函数名称:void System_Disable_Send_Get_Down(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Disable_Send_Get_Down(void){

    System.get_down_delays=0;
    System.send_get_down_enable=0;

}
//****************************************************************//
//函数名称:void System_PowerDown_Exit_Config(void)
//函数功能: 配置掉电IO口中断
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerDown_Exit_Config(void){

   if(!System.power_down_exit_is_config){
      //配置掉电中断  
      Bsp_Power_Down_Exit_Init();
      System.power_down_exit_is_config=1; 
   }
}
//****************************************************************//
//函数名称: void System_PowerDown_Exit_Deint(void)
//函数功能: 关闭掉电中断
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_PowerDown_Exit_Deint(void){
    
   if(System.power_down_exit_is_config){
       
      Bsp_Power_Down_Exit_Deint();
      System.power_down_exit_is_config=0; 
   }

}
//****************************************************************//
//函数名称:void Power_Down_Process(void)
//函数功能: 掉电处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Power_Down_Process(void){
    
   //掉电情况下,继电器是打开的,则关闭，但是不改变标志位
   for(uint8_t i=0;i<SystemInfo.ChannelCount;i++){
  
      if(SystemInfo.time_channel[i].Relays_States)
         Channel_Control(i,RELAY_OFF,without_change_flag);
      
   }
   
   System.is_power_down=1;
   
   System_Back_Led_Close();

}
//****************************************************************//
//函数名称:void Power_Down_Restore(void)
//函数功能: 掉电恢复
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Power_Down_Restore(void){

   //掉电情况下,继电器是打开的,则关闭，但是不改变标志位
  for(uint8_t i=0;i<SystemInfo.ChannelCount;i++){
  
      if(SystemInfo.time_channel[i].Relays_States)
        Channel_Control(i,RELAY_ON,without_change_flag);

  }
   System.is_power_down=0;

}
//****************************************************************//
//函数名称:void System_Back_Led_Open(void)
//函数功能:背光灯打开
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Back_Led_Open(void){

    if(!System.back_led_state && !System.is_power_down){
   
       Bsp_Back_Light_Open(); 
       System.back_led_state=1;
    }

}
//****************************************************************//
//函数名称:void System_Back_Led_Close(void)
//函数功能: 背光灯关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Back_Led_Close(void){

    if(System.back_led_state){
   
       Bsp_Back_Light_Close(); 
       System.back_led_state=0;
        
    }
}
//****************************************************************//
//函数名称:void PowerDown_FroceSaveInfo(void)
//函数功能: 低压强制存储数据
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void PowerDown_FroceSaveInfo(void){

   if(System.is_power_down){
        
       uint16_t crc16= Crc16_Cal((uint8_t *)&SystemInfo.time_channel,845u);
       if( SystemInfo.crc16!=crc16) {
         SystemInfo.is_request_save=1u;
         //将数据写入Flash的第一行
//         SystemInfo_Save(); 
       }
    }

}
//****************************************************************//
//函数名称:void PowerDown_FroceSaveInfo(void)
//函数功能: 低压强制存储数据
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Zeller(int years,int month,int day){

     int y, c, m, d, w;
     y = years % 100;//年　如2015 即年是15年
     c = years / 100;// 年份前两位　如2015即20
     m = month; d = day;
     if (m == 1 || m == 2) { //判断月份是否为1或2
         y--;
         m += 12;//某年的1、2月要看作上一年的13、14月来计算
     }
     w = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1;//蔡勒公式的公式
     while (w < 0) w += 7;//确保余数为正
     w %= 7;
     if(w==0)  //星期日
       w=0x40;
     else if(w==1)
       w=1;   
     else if(w==2)
       w=2;
     else if(w==3)
       w=4;
     else if(w==4)
       w=8;  
     else if(w==5)
       w=0x10;    
     else if(w==6)
       w=0x20;       
     return w;
}
//****************************************************************//
//函数名称:void System_Properties_Change_Cal(uint8_t Index,uint8_t state)
//函数功能: 属性更改未赋值
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Properties_Change_Cal(uint8_t Index,uint8_t state){
      
      uint32_t cache;
      cache=  (uint32_t)state;
      cache <<= (Index*5);
      System.Properties_Change|=cache;

}



