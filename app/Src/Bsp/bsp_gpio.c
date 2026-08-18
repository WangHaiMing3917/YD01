#include "bsp.h"
#include "system_info.h"


//****************************************************************//
//��������: void Bsp_Wifi_Io_Init(void)
//��������: wifi Io ��ʼ��
//��    ��:
//�� �� ֵ:
//˵    ��: 
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Wifi_Io_Init(void){
    
    std_gpio_init_t Gpio_Init = {0};
   
    /*wifiģ��ʹ��*/
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_NOPULL; 
    Gpio_Init.pin =  BLUETOOTH_DETECTION_PIN;
    std_gpio_init(BLUETOOTH_DETECTION_PORT, &Gpio_Init);

}
//****************************************************************//
//��������: uint8_t Bsp_Mode_Key_Read(void)
//��������: ����ģʽ����״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_ChannelMode_Init(void){

    
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB|RCC_PERIPH_CLK_GPIOA|
                            RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD|RCC_PERIPH_CLK_GPIOF);
    
    std_gpio_init_t Gpio_Init = {0};
   
    /*wifiģ��ʹ��*/
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_PULLUP; 
    Gpio_Init.pin =  MODE_PIN;
    std_gpio_init(MODE_PORT, &Gpio_Init);

}
//****************************************************************//
//��������: uint8_t Bsp_Mode_Key_Read(void)
//��������: ����ģʽ����״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_ChannelMode_DeInit(void){

    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB|RCC_PERIPH_CLK_GPIOA|
                            RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD|RCC_PERIPH_CLK_GPIOF);
    
    std_gpio_init_t Gpio_Init = {0};
   
    /*wifiģ��ʹ��*/
    Gpio_Init.mode = GPIO_MODE_INPUT;
    Gpio_Init.pull = GPIO_PULLDOWN; 
    Gpio_Init.pin =  MODE_PIN;
    std_gpio_init(MODE_PORT, &Gpio_Init);

}
//****************************************************************//
//��������: Bsp_ChannelMode_Detect
//��������: ͨ��ģʽ���
//��    ��:
//�� �� ֵ:
//˵    ��:
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_ChannelMode_Detect(void){

    return std_gpio_get_input_pin(MODE_PORT,MODE_PIN);
}

//****************************************************************//
//��������: void Bsp_Gpio_Init(void)
//��������: io��ʼ��
//��    ��:
//�� �� ֵ:
//˵    ��: 
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Gpio_Init(void){

     std_gpio_init_t Gpio_Init = {0};
    /* ʹ��IO�r�*/
    std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOB|RCC_PERIPH_CLK_GPIOA|
                            RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD|RCC_PERIPH_CLK_GPIOF);

   
    Gpio_Init.mode = GPIO_MODE_OUTPUT;
    Gpio_Init.pull = GPIO_NOPULL; 
    Gpio_Init.output_type =  GPIO_OUTPUT_PUSHPULL;
    Gpio_Init.pin =  GPIO_PIN_6|GPIO_PIN_7;
    std_gpio_init(GPIOA, &Gpio_Init);
        
    Gpio_Init.pin =  GPIO_PIN_10;
    std_gpio_init(GPIOB, &Gpio_Init);
    Gpio_Init.pin =  GPIO_PIN_7|GPIO_PIN_12|GPIO_PIN_13;
    std_gpio_init(GPIOC, &Gpio_Init);
    Gpio_Init.pin =  GPIO_PIN_2;
    std_gpio_init(GPIOD, &Gpio_Init);
     
     
    std_gpio_reset_pin(GPIOD,GPIO_PIN_2); 
    std_gpio_reset_pin(GPIOC,GPIO_PIN_7|GPIO_PIN_12|GPIO_PIN_13); 
    std_gpio_reset_pin(GPIOB,GPIO_PIN_10); 
    std_gpio_reset_pin(GPIOA,GPIO_PIN_6|GPIO_PIN_7); 

     //������IO��ʼ�� 
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
     
    //����ʹ�ܳ�ʼ�� 
    Bsp_Wifi_Io_Init();
    //����Ƴ�ʼ�� 
    Bsp_Back_Light_Close();
    //�̵�����ʼ��


     
}

//****************************************************************//
//��������: void Bsp_Back_Light_Open(void)
//��������:  �����
//��    ��:
//�� �� ֵ:
//˵    ��:
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Back_Light_Open(void){
    
    #ifndef  _NOT_CONFIG_SWD
    std_gpio_init_t Gpio_Init_STRUCT = {0};
   
   //���ÿ�©���
    Gpio_Init_STRUCT.mode = GPIO_MODE_INPUT;
    Gpio_Init_STRUCT.pull = GPIO_NOPULL;
    //����
    Gpio_Init_STRUCT.pin =  BACK_LIGHT_PIN;
    std_gpio_init(BACK_LIGHT_PORT, &Gpio_Init_STRUCT); 
   #endif
}

//****************************************************************//
//��������: void Bsp_Back_Light_Close(void)
//��������:  �����ر�
//��    ��:
//�� �� ֵ:
//˵    ��: 
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Back_Light_Close(void){
    
   #ifndef  _NOT_CONFIG_SWD
    std_gpio_init_t Gpio_Init_STRUCT = {0};
   
   //���ÿ�©���
    Gpio_Init_STRUCT.mode = GPIO_MODE_OUTPUT;
    Gpio_Init_STRUCT.pull = GPIO_PULLDOWN;
    //����
    Gpio_Init_STRUCT.pin =  BACK_LIGHT_PIN;
    std_gpio_init(BACK_LIGHT_PORT, &Gpio_Init_STRUCT);  

    std_gpio_reset_pin(BACK_LIGHT_PORT,BACK_LIGHT_PIN);
   #endif 
}

//****************************************************************//
//��������: void Bsp_Relays_Channel_Init(uint8_t Channel_Count)
//��������: 
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Relays_Channel_Init(uint8_t Channel_Count){

    std_gpio_init_t Relay_Gpio_Init = {0};

    //���óɿ�©���
    Relay_Gpio_Init.mode = GPIO_MODE_OUTPUT;
    Relay_Gpio_Init.pull = GPIO_NOPULL;
    Relay_Gpio_Init.output_type = GPIO_OUTPUT_PUSHPULL;
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
    if(SystemInfo.ChannelCount==3){
    
      Relay_Gpio_Init.pin =  RELAYS_CHANNEL_5_PIN;
      std_gpio_init(RELAYS_CHANNEL_5_PORT, &Relay_Gpio_Init);
        
      Relay_Gpio_Init.pin =  RELAYS_CHANNEL_4_PIN;
      std_gpio_init(RELAYS_CHANNEL_4_PORT, &Relay_Gpio_Init);
        
      std_gpio_reset_pin(RELAYS_CHANNEL_4_PORT,RELAYS_CHANNEL_4_PIN); 
      std_gpio_reset_pin(RELAYS_CHANNEL_5_PORT,RELAYS_CHANNEL_5_PIN); 
    }
}
//****************************************************************//
//��������: void Bsp_Relays_Open(GPIO_t* gpiox, uint32_t pin_mask)
//��������: 
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Relays_Open(GPIO_t* gpiox, uint32_t pin_mask){

    std_gpio_init_t Relay_Gpio_Init = {0};
    //���óɿ�©���
    Relay_Gpio_Init.mode = GPIO_MODE_OUTPUT;
    Relay_Gpio_Init.pull = GPIO_NOPULL;
    Relay_Gpio_Init.output_type=  GPIO_OUTPUT_PUSHPULL;
    Relay_Gpio_Init.pin =  pin_mask; 
    std_gpio_init(gpiox, &Relay_Gpio_Init);
    std_gpio_set_pin(gpiox,pin_mask);

}
//****************************************************************//
//��������: void Bsp_Relays_Close(GPIO_t* gpiox, uint32_t pin_mask)
//��������: 
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Relays_Close(GPIO_t* gpiox, uint32_t pin_mask){

    std_gpio_init_t Relay_Gpio_Init = {0};
    //���óɿ�©���
    Relay_Gpio_Init.mode = GPIO_MODE_OUTPUT;
    Relay_Gpio_Init.pull = GPIO_NOPULL;
    Relay_Gpio_Init.output_type=  GPIO_OUTPUT_PUSHPULL;
    Relay_Gpio_Init.pin =  pin_mask; 
    std_gpio_init(gpiox, &Relay_Gpio_Init);     
    std_gpio_reset_pin(gpiox,pin_mask);    

}
//****************************************************************//
//��������: Bsp_Power_Down_Exit_Init
//��������: �����ж�����
//��    ��:
//�� �� ֵ:
//˵    ��: 
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Power_Down_Exit_Init(void){


    std_exti_init_t Key_Exti_init_config = {0};
    
    Key_Exti_init_config.mode =    EXTI_MODE_INTERRUPT;
    Key_Exti_init_config.trigger = EXTI_TRIGGER_FALLING;
    Key_Exti_init_config.line_id = POWER_DOWN_EXTI_LINE;
    Key_Exti_init_config.gpio_id = POWER_DOWN_EXTI_PORT; 
    std_exti_init(&Key_Exti_init_config);  
    
    NVIC_SetPriority(EXTI0_1_IRQn, NVIC_PRIO_2); 
    /* ʹ���ж� */
    NVIC_EnableIRQ(EXTI0_1_IRQn);
}
//****************************************************************//
//��������: Bsp_Power_Down_Exit_Deint
//��������: 
//��    ��:
//�� �� ֵ:
//˵    ��: 
//�޸ļ�¼: 2024.9.26 Whm��������
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
//��������: Bsp_Power_Down_Scan
//��������: ��ѹ���
//��    ��:
//�� �� ֵ:
//˵    ��:
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_Power_Down_Scan(void){

    return std_gpio_get_input_pin(POWER_DOWN_PORT,POWER_DOWN_PIN);
}
//****************************************************************//
//��������: uint8_t Bsp_Hour_Key_Read(void)
//��������: ����Сʱ����״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_Hour_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_HOURS_PORT,KEY_HOURS_PIN);
    
}
//****************************************************************//
//��������: uint8_t Bsp_Minutes_Key_Read(void)
//��������: ���ط��Ӱ���״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_Minutes_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_MINUTE_PORT,KEY_MINUTE_PIN);
    
}
//****************************************************************//
//��������: uint8_t Bsp_Weeks_Key_Read(void)
//��������: �������ڰ���״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_Weeks_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_WEEKS_PORT,KEY_WEEKS_PIN);
    
}
//****************************************************************//
//��������: uint8_t Bsp_Timing_Key_Read(void)
//��������: ���ض�ʱ����״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_Timing_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_TIMING_PORT,KEY_TIMING_PIN);
    
}
//****************************************************************//
//��������: uint8_t Bsp_Mode_Key_Read(void)
//��������: ����ģʽ����״̬
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
uint8_t Bsp_Mode_Key_Read(void){

    
    return std_gpio_get_input_pin(KEY_MODE_PORT,KEY_MODE_PIN);
    
}

//****************************************************************//
//��������: uint8_t Bsp_Key_Exit_Enable(void)
//��������: �ⲿ�ж�
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
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
    /* �����ж����ȼ� */
    NVIC_SetPriority(EXTI4_15_IRQn, NVIC_PRIO_3); 
    /* ʹ���ж� */
    NVIC_EnableIRQ(EXTI4_15_IRQn);
    
    NVIC_SetPriority(EXTI0_1_IRQn, NVIC_PRIO_3); 
    /* ʹ���ж� */
    NVIC_EnableIRQ(EXTI0_1_IRQn);
    
    NVIC_SetPriority(EXTI2_3_IRQn, NVIC_PRIO_3); 
    /* ʹ���ж� */
    NVIC_EnableIRQ(EXTI2_3_IRQn);
}
//****************************************************************//
//��������: uint8_t Bsp_Key_Exit_Disable(void)
//��������: �ⲿ�ж�
//��    ��: 
//�� �� ֵ:
//˵    ��:  
//�޸ļ�¼: 2024.9.26 Whm��������
//***************************************************************//
void Bsp_Key_Exit_Disable(void){

    std_exti_deinit();

}

