#include "bsp.h"


//****************************************************************//
//函数名称: void Bsp_IWDG_Init(void)
//函数功能: 初始化看门狗
//参    数: 
//返 回 值:
//说    明:2S 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_IWDG_Init(void){

    
  #ifndef _DUBUG__   
    /* 使能RCL时钟 */
    std_rcc_rcl_enable();
    
    while(std_rcc_get_rcl_ready() != 1)
    {
    };

    /* 使能IWDG的写权限 */
    std_iwdg_write_access_enable();

    /* 配置IWDG参数 */
    std_iwdg_set_overflow_period(IWDG_OVERFLOW_PERIOD_4096);

    /* IWDG使能 */
    std_iwdg_start();
  #endif
}
//****************************************************************//
//函数名称: void Bsp_IWDG_ReFresh(void)
//函数功能: IWDG喂狗
//参    数: 
//返 回 值:
//说    明:2S 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_IWDG_ReFresh(void){

    #ifndef _DUBUG__   
     std_iwdg_refresh();

    #endif
}

