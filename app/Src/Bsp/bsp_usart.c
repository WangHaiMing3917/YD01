#include "bsp.h"



//****************************************************************//
//函数名称: Bsp_Uart_Config
//函数功能: 串口初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Usart_Config(void){
 
  #if defined(USED_USART_1)
    /* USART时钟使能 */
    std_rcc_apb2_clk_enable(RCC_PERIPH_CLK_USART1);
    
    std_usart_init_t usart_init_t={0};
       /* LPUART 模块初始化 */
    usart_init_t.baudrate = 115200;
    usart_init_t.wordlength = USART_WORDLENGTH_8BITS;
    usart_init_t.stopbits = USART_STOPBITS_1;
    usart_init_t.parity = USART_PARITY_NONE;
    usart_init_t.hardware_flow = USART_FLOWCONTROL_NONE;
    usart_init_t.direction = USART_DIRECTION_SEND_RECEIVE;
    
    /* USART初始化 */   
    if(STD_OK != std_usart_init(USART1,&usart_init_t))
    {
        /* 波特率配置不正确处理代码 */
        while(1);
    }
    std_usart_enable(USART1);
    
    std_usart_cr1_interrupt_enable(USART1,USART_CR1_INTERRUPT_RXNE);
    /* 配置USART1中断优先级以及使能USART1的NVIC中断 */   
    NVIC_SetPriority(USART1_IRQn,NVIC_PRIO_0);    
    NVIC_EnableIRQ(USART1_IRQn);
    std_usart_clear_flag(USART1,USART_FLAG_RXNE); 
    std_usart_clear_flag(USART1,USART_FLAG_TC); 
    std_usart_clear_flag(USART1,USART_FLAG_TXE); 

  #else
    std_lpuart_init_t lpuart_config = {0};
    
    /* 配置LPUART 时钟源为RCH */
    std_rcc_set_lpuart1clk_source(RCC_CLKSEL_LPUART1_SEL_SYSCLK);
        /* 配置LPUART 外设时钟 */
    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_LPUART1);
    
    /* LPUART 模块初始化 */
    lpuart_config.prescaler = LPUART_PRESCALER_DIV1;
    lpuart_config.baudrate = 115200;
    lpuart_config.parity = LPUART_PARITY_NONE;
    lpuart_config.stopbits = LPUART_STOPBITS_1;
    lpuart_config.wordlength = LPUART_WORDLENGTH_8BITS;
    lpuart_config.direction = LPUART_DIRECTION_SEND_RECEIVE;
    std_lpuart_pin_swap_enable(LPUART1) ;

    /* LPUART 初始化 */
    if (STD_OK != std_lpuart_init(LPUART1,&lpuart_config))
    {
        /* 波特率配置不正确处理代码 */
        while(1);
    } 
  
    std_lpuart_enable(LPUART1);
    
    std_lpuart_cr1_interrupt_enable(LPUART1,LPUART_CR1_INTERRUPT_RXNE);
    /* 配置USART1中断优先级以及使能USART1的NVIC中断 */   
    NVIC_SetPriority(LPUART1_IRQn,NVIC_PRIO_0);    
    NVIC_EnableIRQ(LPUART1_IRQn);
    std_lpuart_clear_flag(LPUART1,LPUART_FLAG_RXNE); 
    std_lpuart_clear_flag(LPUART1,LPUART_FLAG_TC); 
    std_lpuart_clear_flag(LPUART1,LPUART_FLAG_TXE); 
   #endif
}


//****************************************************************//
//函数名称: Bsp_Uart_Gpio_Init
//函数功能: 低功耗串口初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Usart_Gpio_Init(void)
{
  #if defined(USED_USART_1)
    std_gpio_init_t tmp_gpio_cfg = {0};
    
    /* UAsRT1 GPIO引脚配置    
       PA2    ------> USART1发送引脚
       PA1    ------> USART1接收引脚 
    */    
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOA);
    tmp_gpio_cfg.pin = USART_TX_PIN | USART_RX_PIN;
    tmp_gpio_cfg.mode = GPIO_MODE_ALTERNATE;
    tmp_gpio_cfg.output_type = GPIO_OUTPUT_PUSHPULL;
    tmp_gpio_cfg.pull = GPIO_PULLUP;
    tmp_gpio_cfg.alternate = GPIO_AF1_USART1;
    std_gpio_init(GPIOA, &tmp_gpio_cfg);  
  #else  
    std_gpio_init_t tmp_gpio_cfg = {0};
    
    /* UAsRT1 GPIO引脚配置    
       PA2    ------> USART1发送引脚
       PA3    ------> USART1接收引脚 
    */    
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOA);
    tmp_gpio_cfg.pin = USART_TX_PIN | USART_RX_PIN;
    tmp_gpio_cfg.mode = GPIO_MODE_ALTERNATE;
    tmp_gpio_cfg.output_type = GPIO_OUTPUT_PUSHPULL;
    tmp_gpio_cfg.pull = GPIO_PULLUP;
    tmp_gpio_cfg.alternate = GPIO_AF6_LPUART1;
    std_gpio_init(GPIOA, &tmp_gpio_cfg);
  #endif
}
//****************************************************************//
//函数名称: Bsp_Uart_Gpio_Init
//函数功能: 低功耗串口初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Usart_Gpio_Deint(void)
{
    #if defined(USED_USART_1)
    std_gpio_init_t tmp_gpio_cfg = {0};
    
    /* UAsRT1 GPIO引脚配置    
       PA2    ------> USART1发送引脚
       PA1    ------> USART1接收引脚 
    */    
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOA);
    tmp_gpio_cfg.pin = USART_TX_PIN | USART_RX_PIN;
    tmp_gpio_cfg.mode = GPIO_MODE_INPUT;
    tmp_gpio_cfg.pull = GPIO_PULLDOWN;
    std_gpio_init(GPIOA, &tmp_gpio_cfg);
    #else     
    std_gpio_init_t tmp_gpio_cfg = {0};
    
    /* UAsRT1 GPIO引脚配置    
       PA2    ------> USART1发送引脚
       PA3    ------> USART1接收引脚 
    */    
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOA);
    tmp_gpio_cfg.pin = USART_TX_PIN | USART_RX_PIN;
    tmp_gpio_cfg.mode = GPIO_MODE_INPUT;
    tmp_gpio_cfg.pull = GPIO_PULLDOWN;
    std_gpio_init(GPIOA, &tmp_gpio_cfg);
    #endif
}
//****************************************************************//
//函数名称: void Bsp_Uart_Init(void)
//函数功能: 串口初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Usart_Init(void){

    Bsp_Usart_Gpio_Init();
    
    Bsp_Usart_Config();


}
//****************************************************************//
//函数名称: void Bsp_Uart_DeInit(void)
//函数功能: 串口去初始化
//参    数:
//返 回 值:
//说    明: 关闭所有中断
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Usart_DeInit(void){

  #if defined(USED_USART_1)
    std_usart_deinit(USART1);
    std_usart_cr1_interrupt_disable(USART1,USART_CR1_INTERRUPT_RXNE);
    std_usart_cr1_interrupt_disable(USART1,USART_CR1_INTERRUPT_TC);
    std_usart_cr1_interrupt_disable(USART1,USART_CR1_INTERRUPT_TXE);
    NVIC_DisableIRQ(USART1_IRQn);  
  #else
    std_lpuart_deinit(LPUART1);
    std_lpuart_cr1_interrupt_disable(LPUART1,LPUART_CR1_INTERRUPT_RXNE);
    std_lpuart_cr1_interrupt_disable(LPUART1,LPUART_CR1_INTERRUPT_TC);
    std_lpuart_cr1_interrupt_disable(LPUART1,LPUART_CR1_INTERRUPT_TXE);
    NVIC_DisableIRQ(LPUART1_IRQn);
  #endif
    
}



