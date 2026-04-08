#include "system.h"



#define POLY 0xEDB88320UL

typedef  void (*pFunction)(void);

/* app起始执行地址 */

#define APPLICATION_ADDRESS   0x08001800

 /* 跳转函数 */

pFunction Jump_To_Application;

/* 跳转地址,中间变量作用 */

uint32_t JumpAddress;

 extern uint32_t CRC_TEST;

//****************************************************************//
//函数名称: void Jump_Process(void)
//函数功能: 跳转函数
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Jump_Process(void){

    if (((*(__IO uint32_t*)APPLICATION_ADDRESS) & 0x2FFE0000 ) == 0x20000000){

     /* 跳转到程序运行地址 */

      JumpAddress = *(__IO uint32_t*) (APPLICATION_ADDRESS + 4);

     /* 转换为函数类型 */

      Jump_To_Application = (pFunction) JumpAddress;

      /* 关闭中断 这个非常重要,如果没有关闭boot下的中断,很容易跳到app后被卡死*/

      __disable_irq();

     /* 初始化app栈指针 */

      __set_MSP(*(__IO uint32_t*) APPLICATION_ADDRESS);
    
      Jump_To_Application();
    }

}

//****************************************************************//
//函数名称: int main(void)
//函数功能: 主函数
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
int main(void){

     Bsp_Init();
     std_delayms(100);
     System_Memory_Init();

     while(1){
         
       Bsp_IWDG_ReFresh();
         
       System_Process(); 
         
         
         
         
     }

    
    
    
}
