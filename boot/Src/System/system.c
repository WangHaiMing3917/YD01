#include "system.h"


SYSTEM_INFO_STRUCT SystemInfo __attribute__ ((aligned (4u)));

uint32_t CRC_TEST;
 
//****************************************************************//
//函数名称: void System_Process(void)
//函数功能: 系统处理
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Process(void){


         //备份区接收完毕，进入CRC校验，如果是掉电了也去查一下，是否已经成功接收到数据了
         if(SystemInfo.system_state==update_wait_check||SystemInfo.system_state==update_power_down){
             
            //最后一组数据是CRC，最后一个数据包之前是完全的数据，
            uint32_t Address= (SystemInfo.upgrade_pack_number-1)*128+UPDATE_ADDRESS;
            //下一个
            uint16_t Length=   *(uint32_t*)Address;
            if(Length>=0x7400){
               SystemInfo.system_state=update_fail;
               SystemInfo.is_request_save=1;
               SystemInfo_Save();
               Jump_Process();
               return;                
            }
            uint32_t UpdateCrc=*(uint32_t*)(Address+4);
            //start address
            uint16_t start_address=(APP_START_ADDRESS-0x8000000)/512u;
             
            CRC_TEST= Crc32_Cal((uint8_t*)UPDATE_ADDRESS,Length) ;
             
            //CRC相同，赋值备份区到APP区，并且删除备份区
            if(UpdateCrc==Crc32_Cal((uint8_t*)UPDATE_ADDRESS,Length)){
               //擦除所有页
               Bsp_Erase_Page(start_address,(APP_LENGHTH/512u));
               //将备份区写入app区
               Bsp_Write_Flash_Word(APP_START_ADDRESS,(uint32_t*)UPDATE_ADDRESS,Length/4u);
               SystemInfo.system_state=normal;
                
            }else
               SystemInfo.system_state=update_fail;
            SystemInfo.is_request_save=1;
            SystemInfo_Save();
         }else if(SystemInfo.system_state==update_into){//说明数据还没传输完
            //数据还没有传输完，断电则判断为升级失败
               SystemInfo.system_state=update_fail;
               SystemInfo.is_request_save=1;
               SystemInfo_Save();            
         }
         
         
         //跳转进入主程序
         Jump_Process();
     
}

