#include "system.h"



//****************************************************************//
//函数名称: LpTime1_Porcess
//函数功能: 30ms中断处理
//参    数:
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void LpTime1_Porcess(void){

  Key_Timer();

  Lcd_Channel_Fast_Flash_Timer();

  Sleep.wakeup_type=wake_up_by_lptime ;
}
//****************************************************************//
//函数名称: LPTIM1_IRQHandler
//函数功能: 低功耗中断
//参    数:
//返 回 值:
//说    明:    0.5S
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void LPTIM1_IRQHandler(void){


    if ((std_lptim_get_interrupt_status(LPTIM1, LPTIM_INTERRUPT_ARRM)) && (std_lptim_get_flag(LPTIM1, LPTIM_FLAG_ARRM)) )
    {
        /* 清除ARRM状态标志 */
        std_lptim_clear_flag(LPTIM1, LPTIM_CLEAR_ARRM);
        
        Bsp_IWDG_ReFresh();
        
        LpTime1_Porcess();

       if(!System.is_power_down){ 
           
          Key_Scan();
   
          Key_Process(); 
       }
    }

}

//****************************************************************//
//函数名称: LpTime1_Enable
//函数功能: 低功耗使能
//参    数:
//返 回 值:
//说    明:    
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void LpTime1_Enable(void){

   if(!System.lptime_is_enable) {
       
      Bsp_Lptime1_Enable();
       
      System.lptime_is_enable=1;
   }
}

//****************************************************************//
//函数名称: LpTime1_Disable
//函数功能: 低功耗时钟，CNT清0
//参    数:
//返 回 值:
//说    明:   
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void LpTime1_Disable(void){

    if(System.lptime_is_enable) {
       
      Bsp_Lptime1_Disable();
       
      System.lptime_is_enable=0;
   }


}





