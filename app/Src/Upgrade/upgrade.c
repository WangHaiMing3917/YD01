#include "system.h"

#define CRC16_POLY       0x8005

UPDATE_STRUCT Update  __attribute__ ((aligned (4u)));
//****************************************************************//
//函数名称:  void X_Modem_Timer(void)
//函数功能:  
//参    数:
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void X_Modem_Timer(void){

    
  if(SystemInfo.system_state==update_into){ 
      
      if(Update.time_out){
       
      if(--Update.time_out==0){
      
           Update.time_out_error++;
           Update.time_out=1000;
           if(Update.time_out_error>25)
              Update.time_out_error=0; 
           if(Update.time_out_error==25){
              Send_over_Update();
              Update.time_out=0;
           }
           
           else{
              Send_Nak_Xmodem();   
           
           }
           
      }
      
    }
   }
   if(Update.wait_send_can_update_delays){
   
       if(--Update.wait_send_can_update_delays==0)
          Update.wait_send_can_update=1;  
   }

}
//****************************************************************//
//函数名称:  void Send_C_Check_Xmodem_Mode(void)
//函数功能:  
//参    数:
//返 回 值:
//说    明:  data 的第一个数值需要是空格
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Send_C_Check_Xmodem_Mode(void){
    
    Searil.length=1;
    
    Searil.TxBuf[0]='C';
    
    
    //已发次数，最大次数，延时，发射状态
    Protocol_Update_SendConfig(0,1,Tx_Request);   

    Update.time_out=3000;
    Update.pack_number=0;
    Update.packs_count=0;

    //清除所有错误
    Xmodem_error_clear(); 
}



//****************************************************************//
//函数名称:  void Send_Ack_Xmodem(void)
//函数功能:  发送Ack
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Send_Ack_Xmodem(void){

    Searil.length=1;
    
    Searil.TxBuf[0]=ACK;
    
    Protocol_Update_SendConfig(0,1,Tx_Request); 
}
//****************************************************************//
//函数名称:  void Send_over_Update(void){
//函数功能:  连发3次取消
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Send_over_Update(void){
    
    Searil.length=1;
    
    Searil.TxBuf[0]=CAN;
    
    Protocol_Update_SendConfig(0,3,Tx_Request);  
    
   // Update.wait_send_can_update=1;
    Update.wait_send_can_update_delays=800;
    
}
//****************************************************************//
//函数名称:  void Send_Nak_Xmodem(void)
//函数功能:  发送Nak
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Send_Nak_Xmodem(void){

    Searil.length=1;
    
    Searil.TxBuf[0]=NAK;
    
    Protocol_Update_SendConfig(0,1,Tx_Request); 
}
//****************************************************************//
//函数名称: void Xmodem_error_clear(void
//函数功能:  xmodem错误清除
//参    数:
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Xmodem_error_clear(void){
    
    Update.pack_number_error=0;
    Update.time_out_error=0;
    Update.crc_error=0;
}
//****************************************************************//
//函数名称: void Update_PowerDown_error_clear_All(void
//函数功能: 掉电清除所有错误计数状态 
//参    数:
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Update_PowerDown_error_clear_All(void){

    Update.time_out=0;
    Xmodem_error_clear();
}
//****************************************************************//
//函数名称:  void Send_C_Start_Xmodem(void)
//函数功能:  发送字符C开始Xmodem传输
//参    数:
//返 回 值:
//说    明:  data 的第一个数值需要是空格
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Update_Recive(XMODEM_STRUCT *Rtr){

    uint16_t crc16;
    uint8_t  crc_l;
    uint8_t  crc_h;
    uint8_t Xmodem_head=Rtr->head;
    uint8_t Xmodem_serialnumber= Rtr-> serialnumber;
    uint8_t Xmodem_serialnumber_complement= Rtr-> serialnumber_complement;
    uint8_t Xmodem_data[128];
    memcpy(Xmodem_data,(uint8_t*)Rtr->data,128);
    uint8_t Xmodem_crc_h=Rtr->crc_h;
    uint8_t Xmodem_crc_l=Rtr->crc_l;
    //超时
    Update.time_out=1000;
    
    switch(Xmodem_head){
    
        case SOH:
           Update.pack_number++;
           Update.pack_number_complement=~ Update.pack_number;
        
           crc16=Crc16_Xmodem((uint8_t*)&Xmodem_data[0],128u);
           crc_l=crc16;
           crc_h= crc16>>8;
              //数据包序号相同
           if((Update.pack_number==Xmodem_serialnumber)&&(Update.pack_number_complement==Xmodem_serialnumber_complement)){
                          //校验码相同
              if((crc_l==Xmodem_crc_l)&&(crc_h==Xmodem_crc_h)){  
                 //写入数据
                  Bsp_Write_Flash_Word(UPDATE_ADDRESS+(Update.packs_count*128),(uint32_t*)&Xmodem_data[0],32);
                  
                  Update.packs_count++;
                  
                  Send_Ack_Xmodem();
                  
                  Xmodem_error_clear(); 
              }else{
              
                  Send_Nak_Xmodem();   
                  Update.pack_number--;
                  Update.crc_error++;
                  if(Update.crc_error>10)
                    Update.crc_error=10;  
              }
           }else if(Update.pack_number==(Xmodem_serialnumber+1)){
                    Update.pack_number_complement=~ (Update.pack_number-1);
                    if( Update.pack_number_complement==Xmodem_serialnumber_complement){
                        Send_Ack_Xmodem();
                        Xmodem_error_clear(); 
                    }else {
                       Send_Nak_Xmodem();  
                       Update.pack_number_error++;
                     if(Update.pack_number_error>10)
                       Update.pack_number_error=10;  
                    }
                   Update.pack_number--;      
           }else{

              Send_Nak_Xmodem();
              Update.pack_number--;    
              Update.pack_number_error++;
              if(Update.pack_number_error>10)
                 Update.pack_number_error=10; 
             
           }
           if(Update.pack_number_error==10||Update.crc_error==10)
              Send_over_Update();
         
          break;
        case EOT:
               //升级结束
               SystemInfo.system_state=update_wait_check;
               SystemInfo.upgrade_pack_number=Update.packs_count;
               SystemInfo.is_request_save=1;
              // SystemInfo_Save();
               Update.wait_send_eot_end=1;
               Send_Ack_Xmodem(); 
        
          break;
        case CAN:
               Send_Ack_Xmodem(); 
          break;
        
        default:
          break;
    
    }


}

//****************************************************************//
//函数名称:  uint16_t Crc16_Xmodem(uint8_t *data,uint16_t length)
//函数功能:  CRC16
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint16_t Crc16_Xmodem(uint8_t *data,uint16_t length){

   uint8_t i;
   uint16_t crc=0;
    
   while(length--){
        
      crc^=((uint16_t)(*data++))<<8;
      for(i=0;i<8;i++){
      
         if(crc&0x8000)
           crc=(crc<<1)^0x1021;
         else
           crc<<=1;
      }
   }
   return crc;
   
}
//****************************************************************//
//函数名称: uint16_t Crc16_Cal(uint8_t *data, uint16_t length)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：Crc校验计算
//修改记录: 2023.6.13 
//***************************************************************//
uint16_t Crc16_Cal(uint8_t *data, uint16_t length){

     uint8_t i,crc_in;

     uint16_t crc_sum = 0xFFFF;

     while (length --) {

        crc_in = * (data ++);

        for (i=0u;i<8u;i++) {

           if (((crc_sum & 0x8000) >> 8) ^ (crc_in & 0x80))
              crc_sum = (crc_sum << 1) ^ CRC16_POLY;
           else
              crc_sum = (crc_sum << 1);
           
           crc_in <<= 1;
        }
     }
     return crc_sum;

}
//****************************************************************//
//函数名称: void Update_Fail_Process(void)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2023.6.13 
//***************************************************************//
void Update_CAN_Process(void){

    //取消数据的状态已经发完
    if(Update.wait_send_can_update==1&& Searil.Tx_State==Tx_Idle){
        
        //升级结束
        SystemInfo.system_state=normal;
        SystemInfo.is_request_save=1;
//        SystemInfo_Save();
        Update.wait_send_can_update=0;
        System.update_fail_send_times=0;
        System.send_update_fail_enable=1;
        System.update_fail_send_delays=100;
    }


}

