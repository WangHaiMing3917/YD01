#include "system.h"


//****************************************************************//
//函数名称: USART1_IRQHandler
//函数功能: 串口中断处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
#if !defined(USED_USART_1)
void LPUART1_IRQHandler(void)
{
    if(std_lpuart_get_flag(LPUART1,LPUART_FLAG_ORE)){
        
        
           std_lpuart_clear_flag(LPUART1,LPUART_FLAG_ORE);
       
    }
    /* 检查到接收寄存器非空标志后， 读取接收数据 */    
    if(((std_lpuart_cr1_get_interrupt_enable(LPUART1,LPUART_CR1_INTERRUPT_RXNE))
         &&(std_lpuart_get_flag(LPUART1,LPUART_FLAG_RXNE))) != 0)
    {   
     
        Searil.Rx_Delays=5; 
        if(!Searil.Rx_Start){
           Searil.rx_count=0u; 
           Searil.RxBuf[Searil.rx_count]=(char)std_lpuart_rx_data_read(LPUART1);
           if(Searil.Tx_State==Tx_WaitAck)
            Searil.Tx_State=Tx_Idle;
           Searil.Rx_Start=1u;
          
          
        }else{
           if(Searil.rx_count>518)
             Searil.rx_count=518u;  
           Searil.RxBuf[++Searil.rx_count]= (char)std_lpuart_rx_data_read(LPUART1);
           if(Searil.rx_count>=519){
              Searil.Rx_Delays=0;
              Searil.Rx_Start=0; 
              Searil.Rx_Complete=1; 
           }               
        }
                 
    }
    /* 检查发送寄存器为空标志置1时，写入发送数据 */    
    if(((std_lpuart_cr1_get_interrupt_enable(LPUART1,LPUART_CR1_INTERRUPT_TXE))
         &&(std_lpuart_get_flag(LPUART1,LPUART_FLAG_TXE))) != 0)
    {

        std_lpuart_tx_data_write(LPUART1, (uint32_t)Searil.TxBuf[Searil.tx_count]);
        Searil.tx_count++;
        if (Searil.length== Searil.tx_count)
        {
            /* 完成发送后，关闭TXE中断，开启发送完成中断 */    
            std_lpuart_cr1_interrupt_disable(LPUART1,LPUART_CR1_INTERRUPT_TXE);
            std_lpuart_cr1_interrupt_enable(LPUART1,LPUART_CR1_INTERRUPT_TC);
     
        }
    }
    /* 检测到发送完成标志置1，将全局标志置1 */    
    if(((std_lpuart_cr1_get_interrupt_enable(LPUART1,LPUART_CR1_INTERRUPT_TC))
        &&(std_lpuart_get_flag(LPUART1,LPUART_FLAG_TC))) != 0)
    {
        std_lpuart_clear_flag(LPUART1,LPUART_FLAG_TC);
        std_lpuart_cr1_interrupt_disable(LPUART1,LPUART_CR1_INTERRUPT_TC);
 
        /* 将发送完成全局标志置1 */
        if(Searil.Tx_State==Tx_WaitComplete){
           Searil.Tx_State=Tx_WaitAck;
           Searil.send_count++; 
        }

    }

}
#else
//****************************************************************//
//函数名称: USART1_IRQHandler
//函数功能: 串口中断处理
//参    数:
//返 回 值:
//说    明: 
//修改记录: 
//***************************************************************//
void USART1_IRQHandler(void){

    
    if(std_usart_get_flag(USART1,USART_FLAG_ORE)){
        
        
           std_usart_clear_flag(USART1,USART_FLAG_ORE);
       
    }
    /* 检查到接收寄存器非空标志后， 读取接收数据 */    
    if(((std_usart_get_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_RXNE))
         &&(std_usart_get_flag(USART1,USART_FLAG_RXNE))) != 0)
    {   
     
        Searil.Rx_Delays=5; 
        if(!Searil.Rx_Start){
           Searil.rx_count=0u; 
           Searil.RxBuf[Searil.rx_count]=(char)std_usart_rx_read_data(USART1);
           if(Searil.Tx_State==Tx_WaitAck)
            Searil.Tx_State=Tx_Idle;
           Searil.Rx_Start=1u;
          
          
        }else{
           if(Searil.rx_count>518)
             Searil.rx_count=518u;  
           Searil.RxBuf[++Searil.rx_count]= (char)std_usart_rx_read_data(USART1);
           if(Searil.rx_count>=519){
              Searil.Rx_Delays=0;
              Searil.Rx_Start=0; 
              Searil.Rx_Complete=1; 
           }               
        }
                 
    }
    /* 检查发送寄存器为空标志置1时，写入发送数据 */    
    if(((std_usart_get_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_TXE))
         &&(std_usart_get_flag(USART1,USART_FLAG_TXE))) != 0)
    {

        std_usart_tx_write_data(USART1, (uint32_t)Searil.TxBuf[Searil.tx_count]);
        Searil.tx_count++;
        if (Searil.length== Searil.tx_count)
        {
            /* 完成发送后，关闭TXE中断，开启发送完成中断 */    
            std_usart_cr1_interrupt_disable(USART1,USART_CR1_INTERRUPT_TXE);
            std_usart_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_TC);
     
        }
    }
    /* 检测到发送完成标志置1，将全局标志置1 */    
    if(((std_usart_get_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_TC))
        &&(std_usart_get_flag(USART1,USART_FLAG_TC))) != 0)
    {
        std_usart_clear_flag(USART1,USART_FLAG_TC);
        std_usart_cr1_interrupt_disable(USART1,USART_CR1_INTERRUPT_TC);
 
        /* 将发送完成全局标志置1 */
        if(Searil.Tx_State==Tx_WaitComplete){
           Searil.Tx_State=Tx_WaitAck;
           Searil.send_count++; 
        }

    }


}
#endif
//****************************************************************//
//函数名称: Usart_Init
//函数功能: 串口初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Usart_Init(void){

    
    if(!System.uart_is_init){
    
       System.uart_is_init=1;
    
       Bsp_Usart_Init();
    
    }
    
    
    
}
//****************************************************************//
//函数名称: Usart_DeInit
//函数功能: 串口去初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Usart_DeInit(void){


   if(System.uart_is_init){
      
      System.uart_is_init=0;
       
      Bsp_Usart_DeInit();
       
   }

}





