#include "system.h"

SEARIL_STRUCT    Searil __attribute__ ((aligned (4u)));


const char manufacturer[]="0 \"xincheng\" ";
#if CHANNEL_NUMBER == 3
const char model[]="0 \"cnph.plug.yd01\" ";
const char serial_number[]="0 \"31968\" ";
#else
const char model[]="0 \"cnph.plug.p30wxm\" ";
const char serial_number[]="0 \"21584\" ";
#endif


const char cmd_model[]="model";
const char cmd_ble_config[]="ble_config";
const char cmd_mcu_version[]="mcu_version";
const char cmd_get_down[]="get_down";
const char cmd_result[]="result ";
const char cmd_error[]="error";
const char cmd_properties_changed[]="properties_changed ";
const char cmd_event_occured[]="event_occured";
const char cmd_set_properties[]="set_properties";
const char cmd_get_properties[]="get_properties";
const char cmd_action[]="action";
const char cmd_miio_net_change[]="MIIO_net_change";
const char cmd_update_fw[]="update_fw";
const char cmd_echo[]="echo";
const char cmd_boot_fail[]="mcu_boot fail";
const char cmd_net[]="net";
const char cmd_time[]="time";
const char cmd_mac[]="mac";
const char cmd_version[]="version";
const char cmd_hellp[]="help";
const char cmd_true[]="true";
const char cmd_flase[]="false";
const char cmd_restore[]="restore";
const char cmd_factory[]="factory";
const char siid_device[1]="1";
const char piid_Manufacturer[1]="1";
const char piid_model[1]="2";
const char piid_Serial_Number[1]="3";   //设备ID
const char piid_FirmwareVersion[1]="4";

//************************************ 
//siid_switch
//switch_status
//piid_mode
//aiid_toggle
const char siid_switch_Arry[5][4]={
    {'2','1','4','1'},
    {'3','1','4','1'},
    {'4','1','4','1'},
    {'5','1','4','1'},
    {'8','1','4','1'},
};
//group
//timer_group
const char pidd_group_Arry[5][3]={
    {'1','2'},
    {'3','4'},
    {'5','6'},
    {'7','8'},
    {'9','1','0'},
};
/*
const char siid_switch[1]="2";
const char piid_switch_status[1]="1";
const char piid_mode[1]="4";
const char aiid_Toggle[1]="1";

const char siid_switch2[1]="3";
const char piid_switch_status2[1]="1";
const char piid_mode2[1]="4";
const char aiid_Toggle2[1]="1";

const char siid_switch3[1]="4";
const char piid_switch_status3[1]="1";
const char piid_mode3[1]="4";
const char aiid_Toggle3[1]="1";

const char siid_switch4[1]="5";
const char piid_switch_status4[1]="1";
const char piid_mode4[1]="4";
const char aiid_Toggle4[1]="1";
const char siid_switch5[1]="6";
const char piid_switch_status5[1]="1";
const char piid_mode5[1]="4";
const char aiid_Toggle5[1]="1";
*/
//************************************ 

const char siid_custom[1]="6";
/*
const char piid_group[1]="1";
const char piid_timer_gropup[1]="2";  
const char piid_group2[1]="3";
const char piid_timer_gropup2[1]="4";  
const char piid_group3[1]="5";
const char piid_timer_gropup3[1]="6";  
const char piid_group4[1]="7";
const char piid_timer_gropup4[1]="8";  
const char piid_group5[1]="9";
const char piid_timer_gropup5[2]="10";  
*/
const char siid_controls_locked[1]="7";
const char piid_lock[1]="1";

//****************************************************************//
//函数名称: void Protocol_SendConfig(uint8_t sendcount,uint8_t sendmax,uint8_t delay,uint8_t tx_state)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Update_SendConfig(uint8_t sendcount,uint8_t sendmax,uint8_t tx_state){

    
    Searil.send_count=sendcount;
    Searil.send_max=sendmax;
    Searil.Tx_State= tx_state;
}

//****************************************************************//
//函数名称: void Protocol_TxBuf_Fill(char*data,uint16_t length,uint8_t send_times,uint8_t type)
//函数功能: 填充
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_TxBuf_Fill(uint16_t length,uint8_t type){

   
    Searil.length=length;
    
    Searil.TxBuf[Searil.length-1]=0x0D;
    
    Searil.send_count=0;
    Searil.send_max=1;
    Searil.wait_feedback_type=type;
    
}
//****************************************************************//
//函数名称: void Protocol_SerialTxCommProcess(void)
//函数功能: 设置模组名称
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_SerialTxCommProcess(void){
    
    if((Searil.Tx_State==Tx_Request)||(Searil.Tx_State==Tx_Repeat)){
     
       Searil.Tx_Delays=100;
       Searil.tx_count=0;
       if(Searil.Tx_State==Tx_Request)
        Searil.send_count=0;
       Searil.Tx_State=Tx_WaitComplete;
      #if defined(USED_USART_1)
       std_usart_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_TXE);
      #else
       std_lpuart_cr1_interrupt_enable(LPUART1, LPUART_CR1_INTERRUPT_TXE);
      #endif
    }
}
//****************************************************************//
//函数名称: uint16_t Protocol_Start_Number(char *data)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint16_t Protocol_Start_Number(char *data){

     uint16_t start_number=strlen(data)*sizeof(char);
    
    return  start_number;
}
//****************************************************************//
//函数名称: void Protocol_Send_GetDown(void)
//函数功能: 发射get_down
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_GetDown(void){

    strcpy(Searil.TxBuf,cmd_get_down);
    
    Protocol_TxBuf_Fill(strlen(cmd_get_down)*sizeof(char)+1,wait_feedback_get_down);
    
    Searil.Tx_State=Tx_Request;



}
//****************************************************************//
//函数名称: void Protocol_get_net_cmd(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_GetNet(void){

    strcpy(Searil.TxBuf,cmd_net);
    
    Protocol_TxBuf_Fill(strlen(cmd_net)*sizeof(char)+1,wait_feeback_check_net);
    
    Searil.Tx_State=Tx_Request;
}
//****************************************************************//
//函数名称: void Protocol_Send_Update_Start(void)
//函数功能: 发射开始升级
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Update_Ready(void){

    char Txdata[]="result \"ready\"";
    strcpy(Searil.TxBuf,Txdata);
    Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_update_start);
    Searil.Tx_State=Tx_Request;

}
//****************************************************************//
//函数名称: void Protocol_Send_GetTime(void)
//函数功能: 获取当前时间
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_GetTime(void){
    //清除获取当前时间标志位
    System.current_time_is_updated=0;
    strcpy(Searil.TxBuf,(char*)cmd_time);
    Protocol_TxBuf_Fill(strlen(cmd_time)+1,wait_feeback_current_time);
    Searil.Tx_State=Tx_Request;
    
}
//****************************************************************//
//函数名称: void Protocol_Send_Boot_Fail(void)
//函数功能: 发射升级失败
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Protocol_Send_Boot_Fail(void){

     strcpy(Searil.TxBuf,(char*)cmd_boot_fail);
    
     Protocol_TxBuf_Fill(strlen(cmd_boot_fail)+1,wait_feedback_boot_fail_ok);
    
     Searil.Tx_State=Tx_Request;
}

//****************************************************************//
//函数名称: void Protocol_Send_Restor(void)
//函数功能: 发送删除配网
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Protocol_Send_Restor(void){
    
     strcpy(Searil.TxBuf,(char*)cmd_restore);
    
     Protocol_TxBuf_Fill(strlen(cmd_restore)+1,wait_feeback_restor);
    
     Searil.Tx_State=Tx_Request;

    
}
//****************************************************************//
//函数名称: void Protocol_Send_Fac(void)
//函数功能: 发送进入工厂模式
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Protocol_Send_Factory(void){

     strcpy(Searil.TxBuf,(char*)cmd_factory);
    
     Protocol_TxBuf_Fill(strlen(cmd_factory)+1,wait_feeback_factory);
    
     Searil.Tx_State=Tx_Request;

}
//****************************************************************//
//函数名称: void Protocol_Channel_NumberCheck(void)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Channel_NumberCheck(char*cache){

      if(strncmp(cache,siid_switch_Arry[0],1)==0)
          return 0;
      else if(strncmp(cache,siid_switch_Arry[1],1)==0)
          return 1;
      else if(strncmp(cache,siid_switch_Arry[2],1)==0)
          return 2;
      else if(strncmp(cache,siid_switch_Arry[3],1)==0)
          return 3;
      else if(strncmp(cache,siid_switch_Arry[4],1)==0)
          return 4;
      return 0;
}
//****************************************************************//
//函数名称: void Protocol_Group_NumebrCheck(void)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
uint8_t Protocol_Group_NumebrCheck(char*cache){

      if(strncmp(cache,pidd_group_Arry[0],1)==0||strncmp(cache,(pidd_group_Arry[0]+1),1)==0)
          return 0;
      else if(strncmp(cache,pidd_group_Arry[1],1)==0||strncmp(cache,(pidd_group_Arry[1]+1),1)==0)
          return 1;
      else if(strncmp(cache,pidd_group_Arry[2],1)==0||strncmp(cache,(pidd_group_Arry[2]+1),1)==0)
          return 2;
      else if(strncmp(cache,pidd_group_Arry[3],1)==0||strncmp(cache,(pidd_group_Arry[3]+1),1)==0)
          return 3;
      else if(strncmp(cache,pidd_group_Arry[4],1)==0||strncmp(cache,(pidd_group_Arry[4]+1),1)==0)
          return 4;
      return 0;
}
//****************************************************************//
//函数名称: void Protocol_Cal_GroupNumber(void)
//函数功能: 计算数值组数目
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Down_Set_Properties_Process(uint8_t group){
    
      char *temp=NULL;
      char code[6] ="-4003 "; 
      char code2[6]="-4002 "; 
      strcpy(Searil.TxBuf,cmd_result);
      //从第几字节开始
      Searil.length=Protocol_Start_Number((char*)cmd_result);
      //pass down   
      temp=strtok(Searil.RxBuf," ");
      //pass set properties
      temp=strtok(NULL," ");
      
      for(uint8_t i=0;i<group;i++){
         //得到Siid
           temp=strtok(NULL," "); 
          
           if(strncmp(temp,siid_switch_Arry[0],1)==0||strncmp(temp,siid_switch_Arry[1],1)==0||strncmp(temp,siid_switch_Arry[2],1)==0||
              strncmp(temp,siid_switch_Arry[3],1)==0||strncmp(temp,siid_switch_Arry[4],1)==0){
               char cache_siid_switch[1];
               strcpy(cache_siid_switch,temp);
               uint8_t group=Protocol_Channel_NumberCheck(temp);
               temp=strtok(NULL," "); 
               //siid填充
               Searil.TxBuf[Searil.length++]=cache_siid_switch[0];
               //siid后面的空格填充
               Searil.TxBuf[Searil.length++]=' ';
               
               if(strncmp(temp,(siid_switch_Arry[0]+1),1)==0||strncmp(temp,(siid_switch_Arry[1]+1),1)==0||strncmp(temp,(siid_switch_Arry[2]+1),1)==0||
                  strncmp(temp,(siid_switch_Arry[3]+1),1)==0||strncmp(temp,(siid_switch_Arry[4]+1),1)==0 ){
                  strcpy(cache_siid_switch,temp);
                  //填充piid 
                  Searil.TxBuf[Searil.length++]=cache_siid_switch[0]; 
                  //填充空格 
                  Searil.TxBuf[Searil.length++]=' ';
                   
                  temp=strtok(NULL," ");
                  //长关 
                  if(strncmp(temp,"false",4)==0){
                     Protocol_Change_Mode(CLOSE_STATE,group); 
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';  
                     Searil.TxBuf[Searil.length++]=' ';
                  }else if(strncmp(temp,"true",4)==0){
                     Protocol_Change_Mode(OPEN_STATE,group);
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';
                     Searil.TxBuf[Searil.length++]=' ';
                  }else{
                     strcpy((char*)&Searil.TxBuf[Searil.length],code);
                     Searil.length+=6; 
                  }
               }else if(strncmp(temp,(siid_switch_Arry[0]+2),1)==0||strncmp(temp,(siid_switch_Arry[1]+2),1)==0||strncmp(temp,(siid_switch_Arry[2]+2),1)==0||
                        strncmp(temp,(siid_switch_Arry[3]+2),1)==0||strncmp(temp,(siid_switch_Arry[4]+2),1)==0){
                   
                  strcpy(cache_siid_switch,temp);   
                  //填充piid 
                  Searil.TxBuf[Searil.length++]=cache_siid_switch[0]; 
                  //填充空格 
                  Searil.TxBuf[Searil.length++]=' ';
                  temp=strtok(NULL," "); 
                   
                  if(strncmp(temp,"0",1)==0){
                      
                     Protocol_Change_Mode(AUTO_STATE,group);
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';
                     Searil.TxBuf[Searil.length++]=' ';
                  }else if(strncmp(temp,"1",1)==0){
                      
                     Protocol_Change_Mode(OPEN_STATE,group);
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';  
                     Searil.TxBuf[Searil.length++]=' ';
                  }else if(strncmp(temp,"2",1)==0){
                      
                     Protocol_Change_Mode(CLOSE_STATE,group);
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';  
                     Searil.TxBuf[Searil.length++]=' ';
                  }else{
                    strcpy((char*)&Searil.TxBuf[Searil.length],code);
                    Searil.length+=6; 
                  }
               }
             //custom
            }else if(strncmp(temp,siid_custom,1)==0){
               char cache_siid_custom[1]; 
               temp=strtok(NULL," ");
               //siid填充
               Searil.TxBuf[Searil.length++]=siid_custom[0];
               //siid后面的空格填充
               Searil.TxBuf[Searil.length++]=' ';
               uint8_t group=Protocol_Group_NumebrCheck(temp); 
               if(strncmp(temp,pidd_group_Arry[0],1)==0||strncmp(temp,pidd_group_Arry[1],1)==0||strncmp(temp,pidd_group_Arry[2],1)==0
                  ||strncmp(temp,pidd_group_Arry[3],1)==0||strncmp(temp,pidd_group_Arry[4],1)==0){
                   
                  uint8_t number;
                  strcpy(cache_siid_custom,temp);  
                  temp=strtok(NULL," ");  
                  //填充piid 
                  Searil.TxBuf[Searil.length++]=cache_siid_custom[0]; 
                  Searil.TxBuf[Searil.length++]=' ';
                  number =atoi(temp); 
                  //0-28内有效
                  if(number<28){
                     //code
                     Searil.TxBuf[Searil.length++]='0'; 
                     Searil.TxBuf[Searil.length++]=' ';
                  }else{
                     strcpy((char*)&Searil.TxBuf[Searil.length],code);
                     Searil.length+=6;   
                  } 
                   
               }else if(strncmp(temp,(pidd_group_Arry[0]+1),1)==0||strncmp(temp,(pidd_group_Arry[1]+1),1)==0||strncmp(temp,(pidd_group_Arry[2]+1),1)==0
                       ||strncmp(temp,(pidd_group_Arry[3]+1),1)==0||strncmp(temp,(pidd_group_Arry[4]+1),1)==0){
                   
                  strcpy(cache_siid_custom,temp);  
                  //将定时数据发送到数组
                  temp=strtok(NULL," ");
                  //填充piid 
                  Searil.TxBuf[Searil.length++]=cache_siid_custom[0];
                  Searil.TxBuf[Searil.length++]=' ';
                  //是字符串
                  if(strncmp(temp,"\"",1)==0){
                     //code
                     Searil.TxBuf[Searil.length++]='0'; 
                     Searil.TxBuf[Searil.length++]=' ';   
                     Protocol_TimingGroup_Set(temp,group); 
                  
                  }else{
                     strcpy((char*)&Searil.TxBuf[Searil.length],code);
                     Searil.length+=6;  
                  }
               }
             //设备信息,因为是写入，所以反馈-4002
            }else if(strncmp(temp,siid_device,1)==0){
                //填充siid
                temp=strtok(NULL," ");
                
                Searil.TxBuf[Searil.length++]=siid_device[0];
                Searil.TxBuf[Searil.length++] =' ';
               //企业标志 
               if(strncmp(temp,piid_Manufacturer,1)==0){
                   
                 Searil.TxBuf[Searil.length++]=piid_Manufacturer[0];
                 Searil.TxBuf[Searil.length++] =' ';
                 //code
                 strcpy((char*)&Searil.TxBuf[Searil.length],code2);
                 Searil.length+=6;   
                   
               //产品模型    
               }else if(strncmp(temp,piid_model,1)==0){
                   
                 Searil.TxBuf[Searil.length++]=piid_model[0];
                 Searil.TxBuf[Searil.length++] =' ';
                 //code
                 strcpy((char*)&Searil.TxBuf[Searil.length],code2);
                 Searil.length+=6; 
               //设备ID    
               }else if(strncmp(temp,piid_Serial_Number,1)==0){
                   
                 Searil.TxBuf[Searil.length++]=piid_Serial_Number[0];
                 Searil.TxBuf[Searil.length++] =' ';
                 //code
                 strcpy((char*)&Searil.TxBuf[Searil.length],code2);
                 Searil.length+=6;     
                //固件版本号
               }else if(strncmp(temp,piid_FirmwareVersion,1)==0){
                   
                 Searil.TxBuf[Searil.length++]=piid_FirmwareVersion[0];
                 Searil.TxBuf[Searil.length++] =' ';
                 //code
                 strcpy((char*)&Searil.TxBuf[Searil.length],code2);
                 Searil.length+=6;  
                   
               }
               
            }else if(strncmp(temp,siid_controls_locked,1)==0){
             
               temp=strtok(NULL," "); 
               //siid填充
               Searil.TxBuf[Searil.length++]=siid_controls_locked[0];
               //siid后面的空格填充
               Searil.TxBuf[Searil.length++]=' ';
               
               if(strncmp(temp,piid_lock,1)==0){
                  //填充piid 
                  Searil.TxBuf[Searil.length++]=piid_lock[0]; 
                  //填充空格 
                  Searil.TxBuf[Searil.length++]=' ';
                  temp=strtok(NULL," ");
                  //长关 
                  if(strncmp(temp,"false",4)==0){

                     System_Properties_Change_Cal(0,Lock_Change);
                     SystemInfo.keylocked=0;
                     Display.update_lcd=1;  
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';  
                     Searil.TxBuf[Searil.length++]=' ';
                  }else if(strncmp(temp,"true",4)==0){
              
                     System_Properties_Change_Cal(0,Lock_Change);
                     SystemInfo.keylocked=1;
                     //填充code，修改成功 
                     Searil.TxBuf[Searil.length++]='0';
                     Searil.TxBuf[Searil.length++]=' ';
                  }else{
                     strcpy((char*)&Searil.TxBuf[Searil.length],code);
                     Searil.length+=6; 
                  }
               }
            }
      }
     Protocol_TxBuf_Fill(Searil.length,wait_feedback_result);
      
     Searil.Tx_State=Tx_Request; 
}

//****************************************************************//
//函数名称: void Protocol_Get_Properties_Process(uint8_t group)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Get_Properties_Process(uint8_t group){
    
      char *temp=NULL;

      strcpy(Searil.TxBuf,cmd_result);
      //从第几字节开始
      Searil.length=Protocol_Start_Number((char*)cmd_result);
      //pass down   
      temp=strtok(Searil.RxBuf," ");
      //pass get_properties
      temp=strtok(NULL," ");

      for(uint8_t i=0;i<group;i++){
        //得到Siid
        temp=strtok(NULL," "); 
        //填充siid
        strncpy((char*)&Searil.TxBuf[Searil.length++],temp,1); 
        Searil.TxBuf[Searil.length++]=' ';
        //siid 
        if(strncmp(temp,siid_device,1)==0){
           //得到piid
           temp=strtok(NULL," "); 
           //填充piid
           strncpy((char*)&Searil.TxBuf[Searil.length++],temp,1);
           Searil.TxBuf[Searil.length++]=' ';
           if(strncmp(temp,piid_Manufacturer,1)==0) {
             //填充code，填充数值
             strcpy(&Searil.TxBuf[Searil.length],manufacturer);
             Searil.length+=strlen(manufacturer);
           }else if(strncmp(temp,piid_model,1)==0){
               
             strcpy(&Searil.TxBuf[Searil.length],model);
             Searil.length+=strlen(model);  
           }else if(strncmp(temp,piid_Serial_Number,1)==0){
             strcpy(&Searil.TxBuf[Searil.length],serial_number);
             Searil.length+=strlen(serial_number);  
           }else if(strncmp(temp,piid_FirmwareVersion,1)==0){
             char number[4]={0};
             number[0]=VERSION/1000+'0';
             number[1]=VERSION%1000/100+'0';
             number[2]=VERSION%1000%100/10+'0';
             number[3]=VERSION%1000%100%10+'0';   
             //填充code，填充数值
             Searil.TxBuf[Searil.length++]='0';
             Searil.TxBuf[Searil.length++]=' ';
             Searil.TxBuf[Searil.length++]='\"';
             strcat( Searil.TxBuf,number);
             Searil.TxBuf[Searil.length++]='\"';
             Searil.TxBuf[Searil.length++]=' ';
           }else{
            
           }
        }else if(strncmp(temp,siid_switch_Arry[0],1)==0||strncmp(temp,siid_switch_Arry[1],1)==0||strncmp(temp,siid_switch_Arry[2],1)==0||
                 strncmp(temp,siid_switch_Arry[3],1)==0||strncmp(temp,siid_switch_Arry[4],1)==0){
           uint8_t ch= Protocol_Channel_NumberCheck(temp); 
           temp=strtok(NULL," "); 
           //填充piid
           strncpy((char*)&Searil.TxBuf[Searil.length++],temp,1);
           Searil.TxBuf[Searil.length++]=' ';
           if(strncmp(temp,(siid_switch_Arry[0]+1),1)==0||strncmp(temp,(siid_switch_Arry[1]+1),1)==0||strncmp(temp,(siid_switch_Arry[2]+1),1)==0||
              strncmp(temp,(siid_switch_Arry[3]+1),1)==0||strncmp(temp,(siid_switch_Arry[4]+1),1)==0) {
              //填充code，填充数值
              Searil.TxBuf[Searil.length++]='0';
              Searil.TxBuf[Searil.length++]=' ';
              if(SystemInfo.time_channel[ch].Relays_States){ 
                  
                 strcpy(&Searil.TxBuf[Searil.length],cmd_true);
                 Searil.length+=strlen(cmd_true);
              }else{
                 strcpy(&Searil.TxBuf[Searil.length],cmd_flase);
                 Searil.length+=strlen(cmd_flase);
              }
              Searil.TxBuf[Searil.length++]=' ';
           }else if(strncmp(temp,(siid_switch_Arry[0]+2),1)==0||strncmp(temp,(siid_switch_Arry[1]+2),1)==0||strncmp(temp,(siid_switch_Arry[2]+2),1)==0
              ||strncmp(temp,(siid_switch_Arry[3]+2),1)==0||strncmp(temp,(siid_switch_Arry[4]+2),1)==0)  {
              //填充code，填充数值                        
              Searil.TxBuf[Searil.length++]='0';
              Searil.TxBuf[Searil.length++]=' ';
              if( SystemInfo.time_channel[ch].Mode==CLOSE_STATE)
                Searil.TxBuf[Searil.length++]='2';
              else if(SystemInfo.time_channel[ch].Mode==OPEN_STATE)
                Searil.TxBuf[Searil.length++]='1';
              else if(SystemInfo.time_channel[ch].Mode==AUTO_STATE)
                Searil.TxBuf[Searil.length++]='0';
              Searil.TxBuf[Searil.length++]=' ';
           }else{
              Searil.length-=8;
           }
        }else if(strncmp(temp,siid_controls_locked,1)==0){
            
           temp=strtok(NULL," "); 
           //填充piid
           strncpy((char*)&Searil.TxBuf[Searil.length++],temp,1);
           Searil.TxBuf[Searil.length++]=' ';
           if(strncmp(temp,piid_lock,1)==0) {
              //填充code，填充数值
              Searil.TxBuf[Searil.length++]='0';
              Searil.TxBuf[Searil.length++]=' ';
              if(SystemInfo.keylocked){
                 strcpy(&Searil.TxBuf[Searil.length],cmd_true);
                 Searil.length+=strlen(cmd_true);
              }else{
                 strcpy(&Searil.TxBuf[Searil.length],cmd_flase);
                 Searil.length+=strlen(cmd_flase);
              }
              Searil.TxBuf[Searil.length++]=' ';
           }
        } else if(strncmp(temp,siid_custom,1)==0){
            
           temp=strtok(NULL," "); 
           //填充piid
           strncpy((char*)&Searil.TxBuf[Searil.length++],temp,1);
           Searil.TxBuf[Searil.length++]=' ';
           uint8_t group= Protocol_Group_NumebrCheck(temp);
           if(strncmp(temp,pidd_group_Arry[0],1)==0||strncmp(temp,pidd_group_Arry[1],1)==0||strncmp(temp,pidd_group_Arry[2],1)==0||
              strncmp(temp,pidd_group_Arry[3],1)==0||strncmp(temp,pidd_group_Arry[4],1)==0) {
               
               //填充code，填充数值
              Searil.TxBuf[Searil.length++]='0';
              Searil.TxBuf[Searil.length++]=' ';
            //Value
            if(System.timer_Enable_Count[group]>=10){
             
              Searil.TxBuf[Searil.length++]=  System.timer_Enable_Count[group]/10+0x30;
              Searil.TxBuf[Searil.length++]=  System.timer_Enable_Count[group]%10+0x30;
         
            }else
              Searil.TxBuf[Searil.length++]=System.timer_Enable_Count[group]+0x30;
            Searil.TxBuf[Searil.length++]=' ';
           }else if(strncmp(temp,(pidd_group_Arry[0]+1),1)==0||strncmp(temp,(pidd_group_Arry[1]+1),1)==0||strncmp(temp,(pidd_group_Arry[2]+1),1)==0||
                    strncmp(temp,(pidd_group_Arry[3]+1),1)==0||strncmp(temp,(pidd_group_Arry[4]+1),2)==0){
               //填充code，填充数值
              Searil.TxBuf[Searil.length++]='0';
              Searil.TxBuf[Searil.length++]=' ';
              Searil.TxBuf[Searil.length++]='\"'; 
           for(uint8_t i=0;i<28;i++){
               
             uint8_t disp_none1=SystemInfo.time_channel[group].timing[2*i].disp_none;
             uint8_t disp_none2=SystemInfo.time_channel[group].timing[2*i+1].disp_none; 
            //第1个字节,右移4位                                                            
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC(((( SystemInfo.time_channel[group].timing[2*i].enable<<7u)|(disp_none1<<6u)|SystemInfo.time_channel[group].timing[2*i].hour)>>4u));
           //第2个字符
            Searil.TxBuf[Searil.length++]= System_Number_To_ASSIIC(((SystemInfo.time_channel[group].timing[2*i].enable<<7u)|SystemInfo.time_channel[group].timing[2*i].hour)&0x0F);
            //第3个字节,右移4位
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC((SystemInfo.time_channel[group].timing[2*i].minutes)>>4);
            //第4个字符
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC((SystemInfo.time_channel[group].timing[2*i].minutes)&0x0F); 
            if((SystemInfo.time_channel[group].timing[2*i].enable==0&&SystemInfo.time_channel[group].timing[2*i].hour==0&&SystemInfo.time_channel[group].timing[2*i].minutes==0)&&
                SystemInfo.time_channel[group].timing[2*i+1].enable==0&&SystemInfo.time_channel[group].timing[2*i+1].hour==0&&SystemInfo.time_channel[group].timing[2*i+1].minutes==0&&
               (SystemInfo.time_channel[group].timing[2*i+1].close)&& (SystemInfo.time_channel[group].timing[2*i].close)) {
               //第5个字符                                                                    
               Searil.TxBuf[Searil.length++]='f';
               Searil.TxBuf[Searil.length++]='f';
            }else{
               //第5个字符   
               Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC( SystemInfo.time_channel[group].timing[2*i].week);
               Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC( SystemInfo.time_channel[group].timing[2*i+1].week);
            }
            //第7个字符
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC(((SystemInfo.time_channel[group].timing[i*2+1].enable<<7u)|(disp_none2<<6u)|SystemInfo.time_channel[group].timing[i*2+1].hour)>>4u);
            //第8个字符 
            Searil.TxBuf[Searil.length++]= System_Number_To_ASSIIC(((SystemInfo.time_channel[group].timing[i*2+1].enable<<7u)|SystemInfo.time_channel[group].timing[i*2+1].hour)&0x0F);
            //第9个字节
            Searil.TxBuf[Searil.length++]= System_Number_To_ASSIIC((SystemInfo.time_channel[group].timing[i*2+1].minutes)>>4);
            Searil.TxBuf[Searil.length++]=System_Number_To_ASSIIC((SystemInfo.time_channel[group].timing[i*2+1].minutes)&0x0F);
           }
              Searil.TxBuf[Searil.length++]='\"'; 
           }else
             Searil.length-=8;
        }
        
      }
     Protocol_TxBuf_Fill(Searil.length+1,wait_feedback_result);
      
     Searil.Tx_State=Tx_Request; 
}
//****************************************************************//
//函数名称: void Protocol_Send_MCU_Version(void)
//函数功能: 发送版本
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_MCU_Version(void){
    
    
      char number[5]={0};
      char send_mcu_version[(strlen(cmd_mcu_version)+strlen(number))*sizeof(char)];
      number[0]=' ';
      number[1]=VERSION/1000+'0';
      number[2]=VERSION%1000/100+'0';
      number[3]=VERSION%1000%100/10+'0';
      number[4]=VERSION%1000%100%10+'0';
      strcpy(send_mcu_version,cmd_mcu_version);
      strcat(send_mcu_version,number);
      strcpy(Searil.TxBuf,(char*)send_mcu_version);
    
      Protocol_TxBuf_Fill(strlen(send_mcu_version)+1,wait_feeback_only_mcu_vesrion);
    
     Searil.Tx_State=Tx_Request;   
      
    
}

//****************************************************************//
//函数名称: void Protocol_Send_Cmd_Too_Long(void)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Cmd_Too_Long(void){


  char Txdata[]="error \"Cmd Too Long\" -5002";

   strcpy(Searil.TxBuf,(char*)Txdata);
    
   Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_error_code);
    
   Searil.Tx_State=Tx_Request;   
    
}
//****************************************************************//
//函数名称: void Protocol_Send_Cmd_MemoryError(void)
//函数功能: 发射内存错误
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Cmd_MemoryError(void){

  char Txdata[]="error \"memory error\" -5001";

   strcpy(Searil.TxBuf,(char*)Txdata);
    
   Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_error_code);
    
   Searil.Tx_State=Tx_Request;
}


void Protocol_Send_Debug_0(void){


  char Txdata[]="set_log_level 0";
  strcpy(Searil.TxBuf,(char*)Txdata);
  Protocol_TxBuf_Fill(strlen(Txdata)*sizeof(char)+1,wait_feedback_error_code);
    
   Searil.Tx_State=Tx_Request;

} 
//****************************************************************//
//函数名称: void Protocol_Get_Current_Time(uint8_t *temp)
//函数功能: 获取数据
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Get_Current_Time(char *temp){

  uint8_t number=0;
  number++;
    if(*(temp+number)==':'){
      Current.Hours= System_Char_To_Number(*(temp));
      number++;	   //是数值
    } else{
      Current.Hours= System_Char_To_Number(*temp)*10;
      Current.Hours+=System_Char_To_Number(*(temp+number));
      number+=2; //数值 
    }

    if(*(temp+number+1)==':'){

      Current.Minute=System_Char_To_Number(*(temp+number));
      number+=2;
    }else{
      Current.Minute=System_Char_To_Number(*(temp+number))*10;
      number++;
      Current.Minute+=System_Char_To_Number(*(temp+number));
      number+=2;
    }
    if(*(temp+number+1)==':'){
      Current.Sec=System_Char_To_Number(*(temp+number));
      number+=2;
    }else{
      Current.Sec=System_Char_To_Number(*(temp+number))*10;
      number++;
      Current.Sec+=System_Char_To_Number(*(temp+number));
      number+=2;
    }

}
//****************************************************************//
//函数名称: void Protocol_Get_Current_Time(uint8_t *temp)
//函数功能: 获取数据
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Action_Send(uint8_t ch){

      strcpy(Searil.TxBuf,cmd_result);
      Searil.length=Protocol_Start_Number((char*)cmd_result);
    
      Searil.TxBuf[Searil.length++]=siid_switch_Arry[ch][0];  

      Searil.TxBuf[Searil.length++]=' ';

      Searil.TxBuf[Searil.length++]=siid_switch_Arry[ch][3];  

      Searil.TxBuf[Searil.length++]=' '; 
      //code
      Searil.TxBuf[Searil.length++]='0'; 
      if(!SystemInfo.time_channel[ch].Relays_States)
        Protocol_Switch_Status(1,ch);
      else
        Protocol_Switch_Status(0,ch); 

     Protocol_TxBuf_Fill(Searil.length+1,wait_feedback_result);
    
     Searil.Tx_State=Tx_Request;
     System_Properties_Change_Cal(ch,Mode_Change);
}
//****************************************************************//
//函数名称: void Protocol_Receive_Process(void)
//函数功能: 协议接收处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Receive_Process(char *data,uint16_t Length){
    
        uint8_t count=0;
        char Rx_cache[Length];
        strncpy(Rx_cache,data,Length);
        char *temp=NULL;
        if(Length>=512){

          Protocol_Cmd_Cache(CMD_TOO_LONG);
          return ;
        }
        //得到内容
        temp=strtok(Rx_cache," ");
        
        if(NULL != temp){  
            
          if(strncmp(temp,"down",4)==0){
              
           temp= strtok(NULL," ");    
           
           if(strncmp(temp,"set_properties",14)==0){
               
              count=0;
              Searil.DataGoroupsNumber=0;
              while(1){
                temp= strtok(NULL," ");
                if (NULL != temp){
                  count++;
                  if(count%3==0)
                   Searil.DataGoroupsNumber++;
                }else
                  break; 
              }    
               Protocol_Cmd_Cache(CMD_SET_PROPERTIES_RPS);
            }else if(strncmp(temp,"none",4)==0){
               //do not
                __NOP();
 
            }else if(strncmp(temp,"get_properties",14)==0)  {
                
               count=0;
                
               Searil.DataGoroupsNumber=0;
                
               while(1){
               
                  temp= strtok(NULL," ");
                   
                  if (NULL != temp){
                    count++;
                    if(count%2==0)
                      Searil.DataGoroupsNumber++;
                  }else
                    break; 
               }
    
              Protocol_Cmd_Cache(CMD_GET_PROPERTIES);

            }else if(strncmp(temp,"action",6)==0) 
              Protocol_Cmd_Cache(CMD_ACTION);
            else if(strncmp(temp,"update_fw",9)==0){
              //取消发射get_down
              System_Disable_Send_Get_Down();
              //不在发射升级失败
              System.send_update_fail_enable=0;
              Protocol_Cmd_Clear();
              System.wait_to_update_delays=2000;  
       

            } else if(strncmp(temp,"MIIO_net_change",15)==0) {
                //通过此收到数据改变wifi灯的效果
                temp= strtok(NULL," ");
                if(strncmp(temp,"offline",7)==0||strncmp(temp,"unprov",3)==0||strncmp(temp,"uap",3)==0
                 ||strncmp(temp,"updating",8)==0){
                    if(strncmp(temp,"updating",8)!=0&&strncmp(temp,"local",5)!=0)
                      Display.disp_wifi=0; 

                }else if(strncmp(temp,"cloud",5)==0){
                    
                    Display.disp_wifi=1;
                    ///
                    //先停止get_down,上传属性
                    System_Disable_Send_Get_Down();
                    
                    System.is_power_on_send_changed = 1;
                     
                    System.Properties_Change = ALL_Change;
                 
                    //System.power_on_send_properties_delays = 10;
                   //// 
                   // Protocol_Cmd_Cache(CMD_TIME);
                    
                }
            } 
            else if(strncmp(temp,"MIIO_mcu_version_req",15)==0)
               Protocol_Cmd_Cache(CMD_MCU_VER); 
            else
               Protocol_Cmd_Cache(CMD_MEMORY_ERROR);
          }else{
            if(strncmp(temp,"ok",2)==0){
                
              if(System.is_not_allow_send_changed)
                 System.is_not_allow_send_changed=0; 
               
              if(Searil.wait_feedback_type==wait_feedback_set_model){
                  
                 //发射设置BLE
                 System.Model_Interactive_Step=Send_Ble_config; 
                 //允许交互
                 System.will_interactive_model=1;
                 
                  
              }else if(Searil.wait_feedback_type==wait_feedback_ble_config){

                 //发送mcu版本
                 System.Model_Interactive_Step=Send_Mcu_Version; 
                 //允许交互
                 System.will_interactive_model=1;
                 
                  
              }else if(Searil.wait_feedback_type==wait_feeback_send_mcu_vesrion){

                 //发送mcu版本
                 System.Model_Interactive_Step=Complete;
                 //清除连接延时
                 Searil.connect_wifi_time_out=0;
                 //结束交互
                 System.will_interactive_model=0;
                  
                 if(SystemInfo.system_state == update_fail){
                    
                    System.send_update_fail_enable=1;
           
                    System.update_fail_send_times=0;
           
                    System.update_fail_send_delays=100;
                 }else{
                   System_Enable_Send_Get_Down();
                 }
//                  Protocol_Send_Debug_0(); 
              }else if(Searil.wait_feedback_type==wait_feedback_update_start){
                  
                 Protocol_Cmd_Clear();
                 Protocol_Cmd_Cache(CMD_INTO_UPDATE);
        
                 //发送c等待运输传输完成
              }else if(Searil.wait_feedback_type==wait_feedback_error_code||Searil.wait_feedback_type==wait_feeback_restor ){
                  
                 if(Searil.wait_feedback_type==wait_feeback_restor ){
                     
                     Display.disp_wifi=0;
                     if(SystemInfo.wifi_in_factory){
                       SystemInfo.wifi_in_factory=0;
                       SystemInfo.is_request_save=1;
                       SystemInfo_Save();    
                     }                         
                     System.Model_Interactive_Step=Send_Model;
                 }

              }else if(Searil.wait_feedback_type==wait_feedback_boot_fail_ok){
                 //模组成功收到 mcu升级失败，进行重新升级

                 System.send_update_fail_enable=0; 
                 SystemInfo.system_state=normal;
                 SystemInfo.is_request_save=1;
                 SystemInfo_Save();
                 //使能发射get_down
                 System_Enable_Send_Get_Down();
                  
              }else  if(Searil.wait_feedback_type==wait_feeback_factory){

                 Factory_Cyc_Check_Net();

                  
              }else{
              }
            //连接中
           }else if(strncmp(temp,"local",5)==0){
            //可以正常通讯
                 if(System_Mode_Read()==Factory_Mode){
                           
                   Display.disp_wifi=1;
                   Display.update_lcd=1;
                 }
           }
           else if(strncmp(temp,"error",5)==0){
               
              if(Searil.wait_feedback_type==wait_feedback_set_model||Searil.wait_feedback_type== wait_feedback_ble_config||Searil.wait_feedback_type==wait_feeback_send_mcu_vesrion)
                 System.will_interactive_model=1;
           }else {
             if(Searil.wait_feedback_type==wait_feeback_current_time||Searil.wait_feedback_type==wait_feeback_cal_time){
                 
                 uint16_t year;uint8_t month, day;
                 year=((*temp)-0x30)*1000+(*(temp+1)-0x30)*100+(*(temp+2)-0x30)*10+(*(temp+3)-0x30) ;
                 if((*(temp+5)-0x30)>0){
                   month=(*(temp+5)-0x30)*10+(*(temp+6)-0x30);
                 }else
                   month=(*(temp+6)-0x30);
                 if((*(temp+8)-0x30)>0)
                 
                   day=(*(temp+8)-0x30)*10+ (*(temp+9)-0x30);
                 else
                   day=(*(temp+9)-0x30);
                 //当前时间折算年月日
                 Current.Week= Zeller(year,month,day);
                 
                 temp= strtok(NULL," ");
                 
                 Protocol_Get_Current_Time(temp);
                 
                 Display.update_lcd=1;
                 
                 System.current_time_is_updated=1;
                 
                 System_Enable_Send_Get_Down();
                 /*
                 System.Properties_Change=ALL_Change;
                 
                 System.power_on_send_properties_delays=3000;
                 */
                 
              }
     
           }
          }
        }
}
//****************************************************************//
//函数名称: void Protocol_SerialRxCommProcess(void)
//函数功能: 接收完成
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_SerialRxCommProcess(void){

    if(Searil.Rx_Complete){
    
       Searil.Rx_Complete=0;

       if(SystemInfo.system_state==update_into)
         Update_Recive((XMODEM_STRUCT *)Searil.RxBuf);
       else
         Protocol_Receive_Process((char*)Searil.RxBuf,Searil.rx_count);

       
    }
}
//****************************************************************//
//函数名称: void Protocol_1ms_Timer(void)
//函数功能: 1ms处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_1ms_Timer(void){

    //等待应答，如果有应答了允许进入发送空闲状态
    if( Searil.Tx_State==Tx_WaitAck){
        
         Searil.Tx_Delays--;
         
         if( Searil.Tx_Delays==0){
             
             if(Searil.send_count<Searil.send_max){
                 
                 Searil.Tx_State=Tx_Repeat;
                 
             }else
               Searil.Tx_State=Tx_Idle;
         }             
    }
    if(Searil.Rx_Start){
  
       if(--Searil.Rx_Delays==0){
       
           Searil.Rx_Start=0u;
           Searil.Rx_Complete=1;
       }
    }
    if(System.wait_to_update_delays){
        
      if(--System.wait_to_update_delays==0)
        Protocol_Cmd_Cache(CMD_UPDATE_READY);  

    
    }

    

}
 //****************************************************************//
//函数名称: void Protocol_Cmd_Cache(uint8_t CmdCache)
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Cmd_Cache(uint8_t CmdCache){
    
    if((CmdCache==System.Cmd)||(CmdCache==System.Cmd_Cache2)||(CmdCache==System.Cmd_Cache3)||(CmdCache==System.Cmd_Cache))
        return;
    //当前命令存在
    if(System.Cmd){
        //第二个缓存命令是否存在
        if(System.Cmd_Cache){
           //第三个缓存命令是否存在
           if(System.Cmd_Cache2){
              //第四个缓冲命令
              if(System.Cmd_Cache3)
                 System.Cmd_Cache3=CmdCache;
              else
                System.Cmd_Cache3=CmdCache;
           }else
             System.Cmd_Cache2=CmdCache;
        }else
          System.Cmd_Cache=CmdCache;
    }else
      System.Cmd=CmdCache;
}

//****************************************************************//
//函数名称: void Protocol_Process(void)
//函数功能: 协议处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Cmd_Refresh(void){

    if((System.Cmd_Cache||System.Cmd_Cache2||System.Cmd_Cache3)){
        
      System.Cmd=System.Cmd_Cache;
        
      System.Cmd_Cache=System.Cmd_Cache2;
        
      System.Cmd_Cache2=System.Cmd_Cache3;
      System.Cmd_Cache3=0;
    }

}
//****************************************************************//
//函数名称: void Protocol_Cmd_Clear(void)
//函数功能: 清除所有命令
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Cmd_Clear(void){
    
   System.Cmd_Cache2=0;
    System.Cmd_Cache3=0;
    System.Cmd_Cache=0;
    System.Cmd=0;
}
//****************************************************************//
//函数名称: void Protocol_Msg_Send(void)
//函数功能: 定时发射net
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Msg_Send(void){

    //优先级最高，属性改变
     Update_CAN_Process();
     if(Searil.Tx_State==Tx_Idle&&!Searil.Rx_Start){
        if(System.Cmd){ 
            
         switch(System.Cmd){
      
             case CMD_GET_DOWN:
               if(System.send_get_down_enable)
                Protocol_Send_GetDown();
               break;
             case CMD_MCU_VER:
                 Protocol_Send_MCU_Version();
               break;
             case CMD_TIME:
                 Protocol_Send_GetTime();
               break;
             case CMD_PROPERTIES_CHANGED:
                 Protocol_Send_Properties_Changed();
               break;
             case CMD_UPDATE_FAIL:
               if(System.send_update_fail_enable)
                 Protocol_Send_Boot_Fail(); 
               break;
             case CMD_GET_NET:
               Protocol_Send_GetNet();
               break;
             case CMD_RESTORE:
               Protocol_Send_Restor();
               break;
             case CMD_SET_PROPERTIES_RPS:
               Protocol_Down_Set_Properties_Process(Searil.DataGoroupsNumber);  
               break;
             case CMD_GET_PROPERTIES:
               Protocol_Get_Properties_Process(Searil.DataGoroupsNumber);
               break;
             case CMD_ACTION:
               Protocol_Action_Send(System.receive_channel);   
               break;
             case CMD_TOO_LONG:
               Protocol_Send_Cmd_Too_Long();  
               break;
             case CMD_UPDATE_READY:
               Protocol_Send_Update_Ready();
               break;
             case CMD_MEMORY_ERROR:
               Protocol_Send_Cmd_MemoryError();  
               break;
             case CMD_INTO_UPDATE:
                 SystemInfo.system_state=update_into;
  
                 Bsp_Erase_Page((UPDATE_ADDRESS-0x08000000)/512u,(0x08010000-UPDATE_ADDRESS)/512);
                 SystemInfo.is_request_save=1;
                 SystemInfo_Save();
                 SystemInfo.update_count++;  
                 Protocol_Cmd_Clear();
                 Send_C_Check_Xmodem_Mode();
               break;
             default:
               break;
       
        }
        System.Cmd=0;
        Protocol_Cmd_Refresh();
      }
    }
 
}


//****************************************************************//
//函数名称: void Protocol_Process(void)
//函数功能: 协议处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Process(void){
   
    //低电压返回    
   if(System.is_power_down)
      return ;

    Protocol_SerialRxCommProcess();
   
    System_PowerOn_ConfigModel();
   
    Protocol_Msg_Send();
   
    Protocol_SerialTxCommProcess();
}
//****************************************************************//
//函数名称: void Protocol_Switch_Status(uint8_t On_Off)
//函数功能: 打开关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Switch_Status(uint8_t On_Off,uint8_t channel){

   if(On_Off) {
       
     if(SystemInfo.time_channel[channel].Mode!=OPEN_STATE)
       SystemInfo.time_channel[channel].Mode=OPEN_STATE;
     
   }else{
       
     if(SystemInfo.time_channel[channel].Mode!=CLOSE_STATE)
      SystemInfo.time_channel[channel].Mode=CLOSE_STATE;

   }   
   if((channel+1)==Current.channel)
    Current.Mode= SystemInfo.time_channel[channel].Mode;
   if( SystemInfo.time_channel[channel].Mode==CLOSE_STATE)
      Channel_Control(channel,RELAY_OFF,change_flag);
   else  if( SystemInfo.time_channel[channel].Mode==OPEN_STATE)
      Channel_Control(channel,RELAY_ON,change_flag);

   Display.not_disp_mode=0;     //显示模式
   Display.update_lcd=1;

}

//****************************************************************//
//函数名称: void Protocol_Change_Mode(uint8_t mode,uint8_t channel)
//函数功能: 打开关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Change_Mode(uint8_t mode,uint8_t channel){
    
    switch(mode){
        //auto
        case AUTO_STATE:
          if(System_Mode_Read()!=Normal_Mode)
            System_Mode_Set(Normal_Mode);  
          if(SystemInfo.time_channel[channel].Mode!=AUTO_STATE){
            SystemInfo.time_channel[channel].Mode=AUTO_STATE;
            if((channel+1)== Current.channel)
              Current.Mode= SystemInfo.time_channel[channel].Mode; 
          }
          if(SystemInfo.time_channel[channel].Mode==AUTO_STATE){
            Check_Near_CurrentTime_Arrary((TIMING_INFO*)&(SystemInfo.time_channel[channel]));  
          }else{
            Display.relay_state_flash_flag=0;
            Display.relay_state_flash_enable=0;
          } 
          
          Display.not_disp_mode=0;     //显示模式
          Display.update_lcd=1;  
          break;
          //开
        case OPEN_STATE:
           Protocol_Switch_Status(1,channel);
          break;
        //关
        case CLOSE_STATE:
           Protocol_Switch_Status(0,channel);   
          break;
        default:
          break;
    
    }
    System.Properties_Change|=(Mode_Change<<channel*5); 
}
//****************************************************************//
//函数名称: void Protocol_TimingGroup_Set(char *temp)
//函数功能: 打开关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_TimingGroup_Set(char *temp,uint8_t ch){

   uint8_t cache[140]={0};
    temp++;  
   for(uint8_t j=0;j<140;j++)
     cache[j]=System_Char_To_Number(*(temp+j*2))*16+System_Char_To_Number(*(temp+j*2+1));
   
   for(uint8_t i=0;i<28;i++){
      //使能都为0，且小时和分钟都为0
      if(((cache[5*i]&0xFF)==0x00)&&((cache[5*i+1]&0xFF)==0x00)&&((cache[5*i+3]&0xFF)==0x00)&&((cache[5*i+4]&0xFF)==0x00)
         &&((cache[5*i+2]&0x88)==0x88)){
          
       SystemInfo.time_channel[ch].timing[2*i].enable      =0;
       SystemInfo.time_channel[ch].timing[2*i].hour        =0;
       SystemInfo.time_channel[ch].timing[2*i].minutes     =0; 
       SystemInfo.time_channel[ch].timing[2*i].disp_none   =0;
       SystemInfo.time_channel[ch].timing[2*i].close       =1;
             
       SystemInfo.time_channel[ch].timing[2*i+1].enable    =0;
       SystemInfo.time_channel[ch].timing[2*i+1].hour      =0; 
       SystemInfo.time_channel[ch].timing[2*i+1].minutes   =0; 
       SystemInfo.time_channel[ch].timing[2*i+1].disp_none =0;
       SystemInfo.time_channel[ch].timing[2*i+1].close     =1;
      }else{
          
       SystemInfo.time_channel[ch].timing[2*i].enable    =(cache[5*i]&0x80)>>7u;
       SystemInfo.time_channel[ch].timing[2*i].disp_none    =(cache[5*i]&0x40)>>6u;   
       SystemInfo.time_channel[ch].timing[2*i].hour      =cache[5*i]&0x3F;
       SystemInfo.time_channel[ch].timing[2*i].minutes   =cache[5*i+1]; 
       SystemInfo.time_channel[ch].timing[2*i].week      =(cache[5*i+2]&0xF0)>>4u;
       SystemInfo.time_channel[ch].timing[2*i].close     =(cache[5*i+2]&0x80)>>7u;
          
       SystemInfo.time_channel[ch].timing[2*i+1].week    =cache[5*i+2]&0x0F;
       SystemInfo.time_channel[ch].timing[2*i+1].enable  =(cache[5*i+3]&0x80)>>7u;
       SystemInfo.time_channel[ch].timing[2*i+1].disp_none=(cache[5*i+3]&0x40)>>6u;   
       SystemInfo.time_channel[ch].timing[2*i+1].hour    =cache[5*i+3]&0x3F; 
       SystemInfo.time_channel[ch].timing[2*i+1].minutes =cache[5*i+4]; 
       SystemInfo.time_channel[ch].timing[2*i+1].close   =(cache[5*i+2]&0x08)>>4u;
      }
   }
   if(System_Mode_Read()!=Normal_Mode)
     System_Mode_Set(Normal_Mode);
   Display.col_not_flash=0u;
   Display.not_disp_mode=0;     //显示模式
   Display.update_lcd=1;  
   //通道定时更改扫描，
   Check_Near_CurrentTime_Arrary((TIMING_INFO*)&SystemInfo.time_channel[ch]);

}
//****************************************************************//
//函数名称: void Protocol_Send_Properties_Changed(void)
//函数功能: 发射属性更改
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Protcol_Properties_Changed_Check(uint32_t properties ){

    uint8_t SendProperties=0;

       //右移5位看下一组
       if(properties&ALL_Change){

           if(properties&0x1F){
             System.Properties_Change= properties&0xFFFFFFE0;
             System.receive_channel=0;
           }else if(properties&(0x1F<<5)){
          
            System.Properties_Change= properties&0xFFFFFC00;
             System.receive_channel=1;  
          } else if(properties&(0x1F<<10)){
             System.Properties_Change= properties&0xFFFF8000;
             System.receive_channel=2;  
          }
          SendProperties= (properties>>( System.receive_channel*5))&0x1F;
       }
 
    return SendProperties;

}
//****************************************************************//
//函数名称: void Protocol_Send_Properties_Changed(void)
//函数功能: 发射属性更改
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Send_Properties_Changed(void){
    
      Searil.length=strlen(cmd_properties_changed)*sizeof(char);
      strcpy(Searil.TxBuf,cmd_properties_changed);
    
      uint8_t Need_Report_Pro=Protcol_Properties_Changed_Check(System.Properties_Change);
       //模式改变了
      if(Switch_Change&Need_Report_Pro){
         //siid
         Searil.TxBuf[Searil.length++]=siid_switch_Arry[System.receive_channel][0];
         Searil.TxBuf[Searil.length++]=' ';
         //piid
         Searil.TxBuf[Searil.length++]=siid_switch_Arry[System.receive_channel][1]; 
         Searil.TxBuf[Searil.length++]=' ';
         //Value
         if(SystemInfo.time_channel[System.receive_channel].Relays_States) {
             
           strcpy(&Searil.TxBuf[Searil.length],cmd_true);
           Searil.length+=strlen(cmd_true);  
         }else{
           strcpy(&Searil.TxBuf[Searil.length],cmd_flase);
           Searil.length+=strlen(cmd_flase);  
         }
         Searil.TxBuf[Searil.length++]=' ';
      }
      if(Lock_Change&Need_Report_Pro){
          //siid
         Searil.TxBuf[Searil.length++]=siid_controls_locked[0];
         Searil.TxBuf[Searil.length++]=' ';
         //piid
         Searil.TxBuf[Searil.length++]=piid_lock[0]; 
         Searil.TxBuf[Searil.length++]=' ';
         //Value
         if(SystemInfo.keylocked) {

           strcpy(&Searil.TxBuf[Searil.length],cmd_true);
           Searil.length+=strlen(cmd_true);   
         }else{
           strcpy(&Searil.TxBuf[Searil.length],cmd_flase);
           Searil.length+=strlen(cmd_flase);   
         }
         Searil.TxBuf[Searil.length++]=' ';
      }
       
      if(Mode_Change&Need_Report_Pro){
         //siid
         Searil.TxBuf[Searil.length++]=siid_switch_Arry[System.receive_channel][0];
         Searil.TxBuf[Searil.length++]=' ';
         //piid
         Searil.TxBuf[Searil.length++]=siid_switch_Arry[System.receive_channel][2]; 
         Searil.TxBuf[Searil.length++]=' ';
         //Value
         if(SystemInfo.time_channel[System.receive_channel].Mode==AUTO_STATE) //auto
          Searil.TxBuf[Searil.length++]='0';
         else if(SystemInfo.time_channel[System.receive_channel].Mode==OPEN_STATE) //open
          Searil.TxBuf[Searil.length++]='1';
         else if(SystemInfo.time_channel[System.receive_channel].Mode==CLOSE_STATE) //close
          Searil.TxBuf[Searil.length++]='2';
          Searil.TxBuf[Searil.length++]=' ';

      }
      if(Group_Change&Need_Report_Pro){
        //siid
         Searil.TxBuf[Searil.length++]=siid_custom[0];
         Searil.TxBuf[Searil.length++]=' ';
         //piid
         Searil.TxBuf[Searil.length++]=pidd_group_Arry[System.receive_channel][0]; 
         Searil.TxBuf[Searil.length++]=' ';
         //Value
         if(System.timer_Enable_Count[System.receive_channel]>=10){
             
           Searil.TxBuf[Searil.length++]=  System.timer_Enable_Count[System.receive_channel]/10+0x30;
           Searil.TxBuf[Searil.length++]=  System.timer_Enable_Count[System.receive_channel]%10+0x30;
         }else
           Searil.TxBuf[Searil.length++]=System.timer_Enable_Count[System.receive_channel]+0x30;
          Searil.TxBuf[Searil.length++]=' '; 
      }
      if(Group_Time_Change&Need_Report_Pro){
          
         //siid
         Searil.TxBuf[Searil.length++]=siid_custom[0];
         Searil.TxBuf[Searil.length++]=' ';
         //piid
         Searil.TxBuf[Searil.length++]=pidd_group_Arry[System.receive_channel][1]; 
         Searil.TxBuf[Searil.length++]=' ';
         //value
         Searil.TxBuf[Searil.length++]='\"'; 
         for(uint8_t i=0;i<28;i++){
             uint8_t disp_none1=SystemInfo.time_channel[System.receive_channel].timing[2*i].disp_none;
             uint8_t disp_none2=SystemInfo.time_channel[System.receive_channel].timing[2*i+1].disp_none; 
                     //第1个字节,右移4位
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC((((SystemInfo.time_channel[System.receive_channel].timing[2*i].enable<<7u)|(disp_none1<<6u)|SystemInfo.time_channel[System.receive_channel].timing[2*i].hour)>>4u));
           //第2个字符
            Searil.TxBuf[Searil.length++]= System_Number_To_ASSIIC(((SystemInfo.time_channel[System.receive_channel].timing[2*i].enable<<7u)|SystemInfo.time_channel[System.receive_channel].timing[2*i].hour)&0x0F);
            //第3个字节,右移4位
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC((SystemInfo.time_channel[System.receive_channel].timing[2*i].minutes)>>4);
            //第4个字符
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC((SystemInfo.time_channel[System.receive_channel].timing[2*i].minutes)&0x0F);
            if((SystemInfo.time_channel[System.receive_channel].timing[2*i].enable==0&&SystemInfo.time_channel[System.receive_channel].timing[2*i].hour==0)&&(SystemInfo.time_channel[System.receive_channel].timing[2*i].minutes==0)&&SystemInfo.time_channel[System.receive_channel].timing[2*i].close&&
                SystemInfo.time_channel[System.receive_channel].timing[2*i+1].enable==0&&SystemInfo.time_channel[System.receive_channel].timing[2*i+1].hour==0&&SystemInfo.time_channel[System.receive_channel].timing[2*i+1].minutes==0&&SystemInfo.time_channel[System.receive_channel].timing[2*i+1].close){
               //第5个字符                                                                    
              Searil.TxBuf[Searil.length++]='f';
              Searil.TxBuf[Searil.length++]='f';
            }else{
            
              //第5个字符 
              Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC( SystemInfo.time_channel[System.receive_channel].timing[2*i].week); 
              Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC( SystemInfo.time_channel[System.receive_channel].timing[2*i+1].week);
      
            }
            //第7个字符
            Searil.TxBuf[Searil.length++]=  System_Number_To_ASSIIC(((SystemInfo.time_channel[System.receive_channel].timing[2*i+1].enable<<7u)|(disp_none2<<6u)|SystemInfo.time_channel[System.receive_channel].timing[2*i+1].hour)>>4u);
            //第8个字符 
            Searil.TxBuf[Searil.length++]= System_Number_To_ASSIIC(((SystemInfo.time_channel[System.receive_channel].timing[2*i+1].enable<<7u)|SystemInfo.time_channel[System.receive_channel].timing[2*i+1].hour)&0x0F);
            //第9个字节
            Searil.TxBuf[Searil.length++]= System_Number_To_ASSIIC((SystemInfo.time_channel[System.receive_channel].timing[2*i+1].minutes)>>4);
            //第10个字符
            Searil.TxBuf[Searil.length++]=System_Number_To_ASSIIC((SystemInfo.time_channel[System.receive_channel].timing[2*i+1].minutes)&0x0F);
           }
           Searil.TxBuf[Searil.length++]='\"'; 
           Searil.TxBuf[Searil.length]=' '; 
      }else
          Searil.length--;

      Protocol_TxBuf_Fill(Searil.length+1,wait_feedback_properties_changed);
      
      Searil.Tx_State=Tx_Request;
     // System.Properties_Change=0;
     if(System.is_power_on_send_changed&&!System.Properties_Change){
         
         System.is_power_on_send_changed=0;
         Protocol_Cmd_Cache(CMD_TIME);
         
     }
}
//****************************************************************//
//函数名称: void Protocol_Properties_Changed_Fill(void)
//函数功能: 属性更改上报
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Properties_Changed_Scan(void){

      if(!Display.disp_wifi){
          
        System.Properties_Change=0;
        return;
      }
      if(!System.Properties_Change)
        return;
      if(System.is_not_allow_send_changed)
        return;
      System.Properties_Change_Scan_Delays++;
      
      if(System.Properties_Change_Scan_Delays>=5){
         System.Properties_Change_Scan_Delays=0;
         Protocol_Cmd_Cache(CMD_PROPERTIES_CHANGED);
         System.is_not_allow_send_changed=1; 

      }

}

//****************************************************************//
//函数名称: void Protocol_Repet_Get_CurrentTime(void)
//函数功能: 重复获取当前时间
//参    数:
//返 回 值:
//说    明: 0.5S处理
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Protocol_Repet_Get_CurrentTime(void){
      //当前时间未更新
      if(!System.current_time_is_updated&& Display.disp_wifi==1)
          Protocol_Cmd_Cache(CMD_TIME);

}

