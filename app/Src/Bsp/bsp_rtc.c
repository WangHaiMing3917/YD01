#include "bsp.h"





//****************************************************************//
//函数名称: Bsp_RTC_Init
//函数功能: RTC初始化
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_RTC_Init(void){
    
     /* 关闭RTC寄存器写保护 */
    std_rtc_write_protection_disable();
    
    /* 使能秒周期、2Hz周期定时中断 */
    std_rtc_wut_interrupt_enable( RTC_WUT_INTERRUPT_2HZ);
        
    /* 使能RTC寄存器写保护 */
    std_rtc_write_protection_enable();
    
    /* 配置中断优先级 */
    NVIC_SetPriority(RTC_TAMP_IRQn, NVIC_PRIO_1); 
    /* 使能中断 */
    NVIC_EnableIRQ(RTC_TAMP_IRQn);       


}

