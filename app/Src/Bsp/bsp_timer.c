#include "bsp.h"

#define TIM_ARR_VALUE   9
#define TIM3_ARR_VALUE  49

//****************************************************************//
//函数名称: Bsp_Time8_Init
//函数功能: 定时器8初始化
//参    数:
//返 回 值:
//说    明: 定时1ms
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Time8_Init(void){

    std_tim_basic_init_t basic_init_struct = {0};
     
    uint32_t tmp_psc_value;
    
    /* TIM8时钟使能 */
    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_TIM8);
    
    tmp_psc_value = (uint32_t)(((SystemCoreClock) / 10000) - 1);
        
    /* 配置TIM8计数器参数 */
    basic_init_struct.prescaler = tmp_psc_value;
    basic_init_struct.counter_mode = TIM_COUNTER_MODE_UP;
    basic_init_struct.period = TIM_ARR_VALUE;
    basic_init_struct.clock_div = TIM_CLOCK_DTS_DIV1;
    basic_init_struct.auto_reload_preload = TIM_AUTORELOAD_PRE_ENABLE;
    std_tim_init(TIM8, &basic_init_struct);    
    NVIC_SetPriority(TIM8_IRQn, NVIC_PRIO_1);
    NVIC_EnableIRQ(TIM8_IRQn);  
       /* 使能更新中断 */
    std_tim_interrupt_enable(TIM8, TIM_INTERRUPT_UPDATE);
    
    /* 开启定时器计数 */
    std_tim_enable(TIM8);  

}
//****************************************************************//
//函数名称: Bsp_Time8_Deinit
//函数功能: 定时器8初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Time8_Deinit(void){

    std_tim_deinit(TIM8);    

    NVIC_DisableIRQ(TIM8_IRQn);  
       /* 使能更新中断 */
    std_tim_interrupt_disable(TIM8, TIM_INTERRUPT_UPDATE);
    
    std_tim_disable(TIM8) ;
}
