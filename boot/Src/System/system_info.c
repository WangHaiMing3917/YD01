#include "system.h"
#include <string.h>
typedef struct{

   uint8_t  flag[16];
   uint32_t relays_count[5];

} NotClearCount_t;

 NotClearCount_t NotClearCount __attribute__((at(0x02001F00)));

//****************************************************************//
//函数名称: SystemInfo_IsInitialized
//函数功能: 系统 信息 是否已初始化
//参    数:
//返 回 值: true or false
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t SystemInfo_IsInitialized(void) {

     SystemInfo.Msp =    *(volatile uint8_t *)((uint32_t)SYSTEM_INFO_ADDRESS + 4u);
     SystemInfo.endMsp = *(volatile uint8_t *)((uint32_t)SYSTEM_INFO_ADDRESS + (sizeof(SYSTEM_INFO_STRUCT) - 1u));

     if (SystemInfo.Msp == 0xAA&& SystemInfo.endMsp == 0x55)
        return 1u;

     return 0u;

}
//****************************************************************//
//函数名称: SystemInfo_Load
//函数功能: 系统信息载入
//参    数:
//返 回 值: 
//说    明: flash 2k
//修改记录: 2023.7.27 创建函数whm
//***************************************************************//
void SystemInfo_Load(void){

     uint32_t addr;
     uint8_t  index;
     uint16_t  length=sizeof(SYSTEM_INFO_STRUCT)/4;
     uint32_t *data = (uint32_t *)&SystemInfo;
     uint8_t loop=SYSTEM_INFO_LENGTH/sizeof(SYSTEM_INFO_STRUCT);
   
     for (index=0u;index<loop;index++) {
        
        addr = SYSTEM_INFO_ADDRESS + (index * sizeof(SYSTEM_INFO_STRUCT)); 
        SystemInfo.Msp = *(volatile uint8_t *)(addr + 4u); //指针指向msp_h
        SystemInfo.endMsp = *(volatile uint8_t *)(addr + (sizeof(SYSTEM_INFO_STRUCT) - 1u));
        if (SystemInfo.Msp != 0xAA || SystemInfo.endMsp != 0x55)
           break;
     }
     if(index)
      index-=1u;
     addr = SYSTEM_INFO_ADDRESS + (index * sizeof(SYSTEM_INFO_STRUCT));
     while(length--){
     
         *data = *(volatile uint32_t *)addr;
         addr += 4u;
         data ++;
     }
       if(index >= (loop - 1u)) {
     
        SystemInfo.index = 0u;
         
        System_Save_WriteToFlash(SYSTEM_INFO_ADDRESS,(uint32_t *)&SystemInfo,sizeof(SYSTEM_INFO_STRUCT),ERASE_SYSTEM_INFO); 
         
     }

}

//****************************************************************//
//函数名称: void System_Save_WriteToFlash(uint32_t addr,uint32_t *pdata,uint16_t length,erase_type_t erase_type)
//函数功能: 系统信息读取
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void System_Save_WriteToFlash(uint32_t addr,uint32_t *pdata,uint16_t length,erase_type_t erase_type){


    if (erase_type) 
      //擦除数据页，
      Bsp_Erase_Page((SYSTEM_INFO_ADDRESS-0x8000000)/512u,(SYSTEM_INFO_LENGTH/512));


     Bsp_Write_Flash_Word(addr,(uint32_t*)pdata,length/4u);


}
//****************************************************************//
//函数名称: SystemInfo_Save(void)
//函数功能: 系统信息存储
//参    数:
//返 回 值: 
//说    明: 
//修改记录: 2023.7.27 创建函数whm
//***************************************************************//
void SystemInfo_Save(void){

     if (SystemInfo.is_request_save) {

        uint8_t loop = SYSTEM_INFO_LENGTH/sizeof(SYSTEM_INFO_STRUCT);

        SystemInfo.is_request_save = 0u;

        uint16_t crc_value = Crc16_Cal((uint8_t *)&SystemInfo.Msp,(sizeof(SYSTEM_INFO_STRUCT) - 4u));

        if (SystemInfo.save_crc != crc_value) {

           erase_type_t erase_type = ERASE_NONE;

           Bsp_IWDG_ReFresh();

           SystemInfo.index ++;

           SystemInfo.save_crc = crc_value;

           if (SystemInfo.index >= loop) {

              SystemInfo.index = 0u;

              erase_type = ERASE_SYSTEM_INFO;
           }

           System_Save_WriteToFlash((SYSTEM_INFO_ADDRESS + (SystemInfo.index * sizeof(SYSTEM_INFO_STRUCT))),
                                   (uint32_t *)&SystemInfo,sizeof(SYSTEM_INFO_STRUCT),erase_type);
        }
     }
}


//****************************************************************//
//函数名称: void System_Memory_Init(void)
//函数功能: 内存数据初始化
//参    数:
//返 回 值: 
//说    明: 
//修改记录: 2023.7.27 创建函数whm
//***************************************************************//
void System_Memory_Init(void){

    memset(&SystemInfo, 0, sizeof(SystemInfo));

    std_delayms(100);
    
    if (SystemInfo_IsInitialized()) {            //判断是否初始化
   
        SystemInfo_Load();                        //载入配置信息

    }


}


