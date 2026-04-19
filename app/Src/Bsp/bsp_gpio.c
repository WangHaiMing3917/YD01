#include "bsp.h"
#include "system_info.h"


//****************************************************************//
//函数名称: void Bsp_Wifi_Io_Init(void)
//函数功能: wifi Io 初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Wifi_Io_Init(void){
    
    std_gpio_init_t Gpio_Init = {0};
   
    /*wifi模块使能*/
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_NOPULL; 
    Gpio_Init.pin =  BLUETOOTH_DETECTION_PIN;
    std_gpio_init(BLUETOOTH_DETECTION_PORT, &Gpio_Init);

}
//****************************************************************//
//函数名称: uint8_t Bsp_Mode_Key_Read(void)
//函数功能: 返回模式按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_ChannelMode_Init(void){

    
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB|RCC_PERIPH_CLK_GPIOA|
                            RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD|RCC_PERIPH_CLK_GPIOF);
    
    std_gpio_init_t Gpio_Init = {0};
   
    /*wifi模块使能*/
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_PULLUP; 
    Gpio_Init.pin =  MODE_PIN;
    std_gpio_init(MODE_PORT, &Gpio_Init);

}
//****************************************************************//
//函数名称: uint8_t Bsp_Mode_Key_Read(void)
//函数功能: 返回模式按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_ChannelMode_DeInit(void){

    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB|RCC_PERIPH_CLK_GPIOA|
                            RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD|RCC_PERIPH_CLK_GPIOF);
    
    std_gpio_init_t Gpio_Init = {0};
   
    /*wifi模块使能*/
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_PULLDOWN; 
    Gpio_Init.pin =  MODE_PIN;
    std_gpio_init(MODE_PORT, &Gpio_Init);

}
//****************************************************************//
//函数名称: Bsp_ChannelMode_Detect
//函数功能: 通道模式监测
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_ChannelMode_Detect(void){

    return std_gpio_get_input_pin(MODE_PORT,MODE_PIN);
}

//****************************************************************//
//函数名称: void Bsp_Gpio_Init(void)
//函数功能: io初始化
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Gpio_Init(void){

     std_gpio_init_t Gpio_Init = {0};
    /* 使能IO時鐘*/
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB|RCC_PERIPH_CLK_GPIOA|
                            RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD|RCC_PERIPH_CLK_GPIOF);

    //掉电监测IO初始化 
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_NOPULL; 
    Gpio_Init.pin =  POWER_DOWN_PIN;
    std_gpio_init(POWER_DOWN_PORT, &Gpio_Init);
     
    Gpio_Init.pull = GPIO_PULLUP;
    Gpio_Init.pin =  KEY_MINUTE_PIN;
    std_gpio_init(KEY_MINUTE_PORT, &Gpio_Init);
    
    Gpio_Init.pin =  KEY_TIMING_PIN;
    std_gpio_init(KEY_TIMING_PORT, &Gpio_Init);
    
    Gpio_Init.pin =  KEY_WEEKS_PIN;
    std_gpio_init(KEY_WEEKS_PORT, &Gpio_Init);
    
    Gpio_Init.pin =  KEY_MODE_PIN;
    std_gpio_init(KEY_MODE_PORT, &Gpio_Init);
    
    Gpio_Init.pin =  KEY_HOURS_PIN;
    std_gpio_init(KEY_HOURS_PORT, &Gpio_Init); 
     
    //蓝牙使能初始化 
    Bsp_Wifi_Io_Init();
    //背光灯初始化 
    Bsp_Back_Light_Close();
    //继电器初始化
    Bsp_Relays_Channel_Init(SystemInfo.ChannelCount);
     
}

//****************************************************************//
//函数名称: void Bsp_Back_Light_Open(void)
//函数功能:  背光打开
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Back_Light_Open(void){
    
    #ifndef  _NOT_CONFIG_SWD
    std_gpio_init_t Gpio_Init_STRUCT = {0};
   
   //配置开漏输出
    Gpio_Init_STRUCT.mode = GPIO_MODE_INPUT;
    Gpio_Init_STRUCT.pull = GPIO_NOPULL;
    //背光
    Gpio_Init_STRUCT.pin =  BACK_LIGHT_PIN;
    std_gpio_init(BACK_LIGHT_PORT, &Gpio_Init_STRUCT); 
   #endif
}

//****************************************************************//
//函数名称: void Bsp_Back_Light_Close(void)
//函数功能:  背光打关闭
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Back_Light_Close(void){
    
   #ifndef  _NOT_CONFIG_SWD
    std_gpio_init_t Gpio_Init_STRUCT = {0};
   
   //配置开漏输出
    Gpio_Init_STRUCT.mode = GPIO_MODE_OUTPUT;
    Gpio_Init_STRUCT.pull = GPIO_PULLDOWN;
    //背光
    Gpio_Init_STRUCT.pin =  BACK_LIGHT_PIN;
    std_gpio_init(BACK_LIGHT_PORT, &Gpio_Init_STRUCT);  

    std_gpio_reset_pin(BACK_LIGHT_PORT,BACK_LIGHT_PIN);
   #endif 
}

//****************************************************************//
//函数名称: void Bsp_Relays_Channel_Init(uint8_t Channel_Count)
//函数功能: 
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Relays_Channel_Init(uint8_t Channel_Count){

    std_gpio_init_t Relay_Gpio_Init = {0};

    //配置成开漏输出
    Relay_Gpio_Init.mode = GPIO_MODE_OUTPUT;
    Relay_Gpio_Init.pull = GPIO_PULLDOWN;
    
    switch(Channel_Count){

        case 5:
           Relay_Gpio_Init.pin =  RELAYS_CHANNEL_5_PIN;
           std_gpio_init(RELAYS_CHANNEL_5_PORT, &Relay_Gpio_Init);
           Bsp_Relays_Close(RELAYS_CHANNEL_5_PORT,RELAYS_CHANNEL_5_PIN);

        case 4:
           Relay_Gpio_Init.pin =  RELAYS_CHANNEL_4_PIN;
           std_gpio_init(RELAYS_CHANNEL_4_PORT, &Relay_Gpio_Init);
           Bsp_Relays_Close(RELAYS_CHANNEL_4_PORT,RELAYS_CHANNEL_4_PIN);
        case 3:
           Relay_Gpio_Init.pin =  RELAYS_CHANNEL_3_PIN;
           std_gpio_init(RELAYS_CHANNEL_3_PORT, &Relay_Gpio_Init);
           Bsp_Relays_Close(RELAYS_CHANNEL_3_PORT,RELAYS_CHANNEL_3_PIN);
        case 2:
           Relay_Gpio_Init.pin =  RELAYS_CHANNEL_2_PIN;
           std_gpio_init(RELAYS_CHANNEL_2_PORT, &Relay_Gpio_Init);
           Bsp_Relays_Close(RELAYS_CHANNEL_2_PORT,RELAYS_CHANNEL_2_PIN);
        default:
        case 1:
           Relay_Gpio_Init.pin =  RELAYS_CHANNEL_1_PIN;
           std_gpio_init(RELAYS_CHANNEL_1_PORT, &Relay_Gpio_Init);
           Bsp_Relays_Close(RELAYS_CHANNEL_1_PORT,RELAYS_CHANNEL_1_PIN);
        break;
    }

}
//****************************************************************//
//函数名称: void Bsp_Relays_Open(GPIO_t* gpiox, uint32_t pin_mask)
//函数功能: 
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Relays_Open(GPIO_t* gpiox, uint32_t pin_mask){

    std_gpio_init_t Relay_Gpio_Init = {0};
    //配置成开漏输出
    Relay_Gpio_Init.mode = GPIO_MODE_INPUT;
    Relay_Gpio_Init.pull = GPIO_NOPULL;
    Relay_Gpio_Init.pin =  pin_mask; 
    std_gpio_init(gpiox, &Relay_Gpio_Init);
    

}
//****************************************************************//
//函数名称: void Bsp_Relays_Close(GPIO_t* gpiox, uint32_t pin_mask)
//函数功能: 
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Relays_Close(GPIO_t* gpiox, uint32_t pin_mask){

    std_gpio_init_t Relay_Gpio_Init = {0};
    //配置成开漏输出
    Relay_Gpio_Init.mode = GPIO_MODE_OUTPUT;
    Relay_Gpio_Init.pull = GPIO_PULLDOWN;
    Relay_Gpio_Init.pin =  pin_mask; 
    std_gpio_init(gpiox, &Relay_Gpio_Init);     
    std_gpio_reset_pin(gpiox,pin_mask);    

}
//****************************************************************//
//函数名称: Bsp_Power_Down_Exit_Init
//函数功能: 掉电中断配置
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Power_Down_Exit_Init(void){


    std_exti_init_t Key_Exti_init_config = {0};
    
    Key_Exti_init_config.mode =    EXTI_MODE_INTERRUPT;
    Key_Exti_init_config.trigger = EXTI_TRIGGER_FALLING;
    Key_Exti_init_config.line_id = POWER_DOWN_EXTI_LINE;
    Key_Exti_init_config.gpio_id = POWER_DOWN_EXTI_PORT; 
    std_exti_init(&Key_Exti_init_config);  
    
    NVIC_SetPriority(EXTI0_1_IRQn, NVIC_PRIO_2); 
    /* 使能中断 */
    NVIC_EnableIRQ(EXTI0_1_IRQn);
}
//****************************************************************//
//函数名称: Bsp_Power_Down_Exit_Deint
//函数功能: 
//参    数:
//返 回 值:
//说    明: 
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Power_Down_Exit_Deint(void){

    std_exti_init_t Key_Exti_init_config = {0};
    Key_Exti_init_config.mode =    EXTI_MODE_INTERRUPT;
    Key_Exti_init_config.trigger = EXTI_TRIGGER_NONE;
    Key_Exti_init_config.line_id = POWER_DOWN_EXTI_LINE;
    Key_Exti_init_config.gpio_id = POWER_DOWN_EXTI_PORT; 
    std_exti_init(&Key_Exti_init_config);  
    
}
//****************************************************************//
//函数名称: Bsp_Power_Down_Scan
//函数功能: 低压检测
//参    数:
//返 回 值:
//说    明:
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_Power_Down_Scan(void){

    return std_gpio_get_input_pin(POWER_DOWN_PORT,POWER_DOWN_PIN);
}
//****************************************************************//
//函数名称: uint8_t Bsp_Hour_Key_Read(void)
//函数功能: 返回小时按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_Hour_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_HOURS_PORT,KEY_HOURS_PIN);
    
}
//****************************************************************//
//函数名称: uint8_t Bsp_Minutes_Key_Read(void)
//函数功能: 返回分钟按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_Minutes_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_MINUTE_PORT,KEY_MINUTE_PIN);
    
}
//****************************************************************//
//函数名称: uint8_t Bsp_Weeks_Key_Read(void)
//函数功能: 返回星期按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_Weeks_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_WEEKS_PORT,KEY_WEEKS_PIN);
    
}
//****************************************************************//
//函数名称: uint8_t Bsp_Timing_Key_Read(void)
//函数功能: 返回定时按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_Timing_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_TIMING_PORT,KEY_TIMING_PIN);
    
}
//****************************************************************//
//函数名称: uint8_t Bsp_Mode_Key_Read(void)
//函数功能: 返回模式按键状态
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
uint8_t Bsp_Mode_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_MODE_PORT,KEY_MODE_PIN);
    
}

//****************************************************************//
//函数名称: uint8_t Bsp_Key_Exit_Enable(void)
//函数功能: 外部中断
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Key_Exit_Enable(void){

    std_exti_init_t Key_Exti_init_config = {0};
    
    Key_Exti_init_config.mode =    EXTI_MODE_INTERRUPT;
    Key_Exti_init_config.trigger = EXTI_TRIGGER_RISING_FALLING;
    Key_Exti_init_config.line_id = KEY_MINUTE_EXTI_LINE;
    Key_Exti_init_config.gpio_id = KEY_MINUTE_EXTI_PORT;
    
    std_exti_init(&Key_Exti_init_config);
    
    Key_Exti_init_config.line_id = KEY_TIMING_EXTI_LINE;
    Key_Exti_init_config.gpio_id = KEY_TIMING_EXTI_PORT;
    
    std_exti_init(&Key_Exti_init_config);
    
    Key_Exti_init_config.line_id = KEY_WEEKS_EXTI_LINE;
    Key_Exti_init_config.gpio_id = KEY_WEEKS_EXTI_PORT;
    
    std_exti_init(&Key_Exti_init_config);
    
    Key_Exti_init_config.line_id = KEY_MODE_EXTI_LINE;
    Key_Exti_init_config.gpio_id = KEY_MODE_EXTI_PORT;
    
    std_exti_init(&Key_Exti_init_config); 
        
    Key_Exti_init_config.line_id = KEY_HOURS_EXTI_LINE;
    Key_Exti_init_config.gpio_id = KEY_HOURS_EXTI_PORT;
    
    std_exti_init(&Key_Exti_init_config); 
    /* 配置中断优先级 */
    NVIC_SetPriority(EXTI4_15_IRQn, NVIC_PRIO_3); 
    /* 使能中断 */
    NVIC_EnableIRQ(EXTI4_15_IRQn);
    
    NVIC_SetPriority(EXTI0_1_IRQn, NVIC_PRIO_3); 
    /* 使能中断 */
    NVIC_EnableIRQ(EXTI0_1_IRQn);
    
    NVIC_SetPriority(EXTI2_3_IRQn, NVIC_PRIO_3); 
    /* 使能中断 */
    NVIC_EnableIRQ(EXTI2_3_IRQn);
}
//****************************************************************//
//函数名称: uint8_t Bsp_Key_Exit_Disable(void)
//函数功能: 外部中断
//参    数: 
//返 回 值:
//说    明:  
//修改记录: 2024.9.26 Whm创建函数
//***************************************************************//
void Bsp_Key_Exit_Disable(void){

    std_exti_deinit();

}

