#include "bsp.h"


#define RELOAD_VALUE          (uint32_t) (1639u)

//****************************************************************//
//函数名称: Bsp_LpTimer_Init
//函数功能: 低功耗定时器初始化
//参    数:
//返 回 值:
//说    明: LpTimer1    32k 30ms
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_LpTimer_Init(void){

    std_lptim_deinit(LPTIM1);
     /* 选择LPTIM1的时钟源为LXTAL */
    std_rcc_set_lptim1clk_source(RCC_LPTIM1_ASYNC_CLK_SRC_LXTAL);
    
    /* LPTIM1外设时钟使能 */
    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_LPTIM1);

    /* 使能LPTIM1时钟 */
    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_LPTIM1);
    
    /* 设置LPTIM1预分频器 */
    std_lptim_set_prescaler(LPTIM1, LPTIM_PRESCALER_DIV1);
    
    /* 使能软件触发计数 */
    std_lptim_set_software_trig(LPTIM1);

    NVIC_SetPriority(LPTIM1_IRQn, NVIC_PRIO_1);
    
    NVIC_EnableIRQ(LPTIM1_IRQn);

}

//****************************************************************//
//函数名称: Bsp_Lptime1_Enable
//函数功能: 定时器1使能
//参    数:
//返 回 值:
//说    明: LpTimer1    32k 30ms
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Lptime1_Enable(void){

     /* 使能自动重载匹配中断 */
    std_lptim_interrupt_enable(LPTIM1, LPTIM_INTERRUPT_ARRM);
    
    /* 使能LPTIM */
    std_lptim_enable(LPTIM1);
    
    
    /* 设置自动重载值 */
    std_lptim_set_auto_reload(LPTIM1, RELOAD_VALUE);
   
    
    /* 启动LPTIM计数 */
    std_lptim_start_counter(LPTIM1, LPTIM_COUNT_CONTINUOUS);

}
//****************************************************************//
//函数名称: Bsp_Lptime1_Disable
//函数功能: 定时器1失能
//参    数:
//返 回 值:
//说    明: LpTimer1    32k 30ms
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Lptime1_Disable(void){


     /* 使能自动重载匹配中断 */
    std_lptim_interrupt_disable(LPTIM1, LPTIM_INTERRUPT_ARRM);
    
    /* 使能LPTIM */
    std_lptim_disable(LPTIM1);


}



