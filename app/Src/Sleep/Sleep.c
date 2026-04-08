#include "system.h"

SLEEP_STRUCT Sleep;





//****************************************************************//
//函数名称: void Sleep_Process(void)
//函数功能: 睡眠处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Into_Sleep_Mode(void){

    /* 使能超低功耗配置 */
    std_pmu_ultra_lowpower_enable();

    std_pmu_enter_stop(PMU_ENTRY_LOWPOWER_MODE_WFI);
}

//****************************************************************//
//函数名称: void Sleep_Process(void)
//函数功能: 睡眠处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Sleep_Process(void){

   if(System.is_power_down){
       
      Is_Key_Press();
      //进入睡眠
      Into_Sleep_Mode();
      //退出睡眠IO配置为上拉
      Key_Out_Sleep_Config();
      //如果是定时唤醒,则按键检测
      if(Sleep.wakeup_type!=wake_up_by_rtc&&Sleep.wakeup_type!=0){
          
         Sleep.wakeup_type=0;
          
         LpTime1_Disable();
       
         Key_Scan();
       
         Key_Process();
         
      }
   }
   else{

        LpTime1_Enable();

   }
}

