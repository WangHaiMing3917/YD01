#include "bsp.h"





//****************************************************************//
//函数名称: Bsp_SystemClock_Config
//函数功能: 系统时钟配置
//参    数:
//返 回 值:
//说    明: 16MHZ 内部RCH 滴答时钟位2MHZ-0.5ms
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_SystemClock_Config(void){
    
   //设置Flash读访问等待时间
   std_flash_set_latency(FLASH_LATENCY_0CLK);
   //使能RCH
   std_rcc_rch_enable();
   //等待RCH稳定
   while(!std_rcc_get_rch_ready()); 
   //设置系统时钟源为RCH
   std_rcc_set_sysclk_source(RCC_SYSCLK_SRC_RCHSYS);  
   //等待配置完成 
   while(std_rcc_get_sysclk_source() != RCC_SYSCLK_SRC_STATUS_RCHSYS);
   //配置AHB分频
   std_rcc_set_ahbdiv(RCC_HCLK_DIV1);
   //设置APB1、APB2分频因子
   std_rcc_set_apb1div(RCC_PCLK1_DIV1);
   std_rcc_set_apb2div(RCC_PCLK2_DIV1);
    
   SystemCoreClockUpdate(); 
    
   std_delay_init(); 
}
//****************************************************************//
//函数名称: Bsp_LxTal_Config(uint32_t Lxtal_drv_mode,uint32_t Lxtal_drv_level)
//函数功能: 外部32k始终配置
//参    数: Lxtal_drv_mode,Lxtal_drv_level
//返 回 值:
//说    明: 外部低速时钟，配置驱动模式，以及等级
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_LxTal_Config(uint32_t Lxtal_drv_mode,uint32_t Lxtal_drv_level){

    /* RTC APB时钟使能 */
    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_RTC);
    
    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_PMU);
    
    //要更新LXTAL配置，必须解除备份域的写保护
    std_pmu_vaon_write_enable();
    
    //配置LXTAL驱动模式参数
    std_rcc_lxtal_drive_mode_config(Lxtal_drv_mode);
    
    //配置LXTAL驱动能力
    std_rcc_lxtal_drive_config(Lxtal_drv_level);
    
    //使能LXTAL 
    std_rcc_lxtal_enable(RCC_LXTAL_ON);
    
    //等待LXTAL时钟稳定
    while(!std_rcc_get_lxtal_ready());
    /* 配置LCD/RTC 时钟源为LXTAL */
    std_rcc_set_rtcclk_source(RCC_RTC_ASYNC_CLK_SRC_LXTAL); 
     
    Bsp_LpTimer_Init();
    //RTC使能
    std_rcc_rtc_enable();
    /* 恢复备份域的写保护 */
    std_pmu_vaon_write_disable();   
}
//****************************************************************//
//函数名称: Bsp_Init
//函数功能: 底层初始化
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Init(void){


    __disable_irq();
    
    Bsp_SystemClock_Config();
    
    Bsp_LxTal_Config(RCC_LXTAL_DRIVE_MODE_NORMAL,RCC_LXTAL_DRIVE_LEVEL3);
    
    Bsp_IWDG_Init();
    
    Bsp_Lcd_Init();
    
    Bsp_Gpio_Init();
    
    Bsp_RTC_Init();
    
    __enable_irq();

}
//****************************************************************//
//函数名称: Bsp_LowPower_Config
//函数功能: 低功耗配置
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_LowPower_Config(void){

   std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_PMU);
     /* 使能超低功耗配置 */
   std_pmu_ultra_lowpower_enable();
    
   std_pmu_enter_stop(PMU_ENTRY_LOWPOWER_MODE_WFI);
}

























