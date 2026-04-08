#include "bsp.h"


//****************************************************************//
//函数名称: void Bsp_Read_Flash_Bytes(uint32_t Address,uint16_t Length,uint8_t *Buff)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Flash_Read_Bytes(uint32_t Address,uint16_t Length,uint8_t *Buff){

   for(uint8_t i=0;i<Length;i++)
    Buff[i]=*(uint8_t *)(Address+i);

}

uint32_t count=0;

//****************************************************************//
//函数名称: void Bsp_Write_Flash_Word(uint32_t Address,uint32_t *Buff,uint16_t length)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Write_Flash_Word(uint32_t Address,uint32_t *Buff,uint16_t length){

    std_status_t  status;
    /* 清除错误标志 */
    std_flash_clear_flag(FLASH_FLAG_ALL_ERR);

     __disable_irq();
    
    /* Flash控制寄存器解锁 */
    std_flash_unlock();
    
     if (std_flash_get_lock_status() == false)
    {
        /* Flash编程 */
        for (uint32_t word_count = 0; word_count < length; word_count++) 
        {
            Bsp_IWDG_ReFresh();
            
            status = std_flash_word_program(Address + (word_count << 2), Buff[word_count]);
            
            /* 编程异常，加入自定义处理代码 */
            while(status != STD_OK)
            {
            }
            
            /* 校验编程数据 */
            if (*(uint32_t *)(Address + (word_count << 2)) != Buff[word_count])
            {
                /* 校验异常，加入自定义处理代码 */
                while(1)
                {
                  count=word_count;
                }
            }
        }
  
       __enable_irq();  
        /* Flash控制寄存器加锁 */
        std_flash_lock();
    }

}
//****************************************************************//
//函数名称: void Bsp_Erase_Page(uint16_t PageNumber,uint8_t length)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Erase_Page(uint16_t PageNumber,uint8_t length){

    std_status_t  status;
    
    std_flash_clear_flag(FLASH_FLAG_ALL_ERR);
    
    __disable_irq();
    
    /* Flash控制寄存器解锁 */
    std_flash_unlock();
    
    if (std_flash_get_lock_status() == false){
        
       while(length--){
           
         Bsp_IWDG_ReFresh();
           
         status = std_flash_page_erase(PageNumber++);
         /* 擦除异常，加入自定义处理代码 */
         while(status != STD_OK)
         {
            
         }
       }
        /* Flash控制寄存器加锁 */
        std_flash_lock();
    }
      __enable_irq();      
}




