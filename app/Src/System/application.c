#include "system.h"




//****************************************************************//
//函数名称: main
//函数功能: 主函数
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
int main(void){


   Bsp_Init();
   //系統上电
   System_PowerOn_Process();
    
   while(1){
                            
    Bsp_IWDG_ReFresh();

    Lcd_Display();
    
    Protocol_Process();
 
    Time_1ms_poll();
       
    Sleep_Process();
   
   }

}


