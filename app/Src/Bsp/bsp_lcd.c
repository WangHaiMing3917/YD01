#include "bsp.h"

//****************************************************************//
//         SEG0  SEG1   SEG2  SEG3   SEG4  SEG5  SEG6  SEG7   SEG8   SEG9
//COM0     1E    1D           2E     2D    S11   3E    3D     4E     4D
//COM1     1G    1C           2G     2C    S10   3G    3C     4G     4C
//COM2     1F    1B           2F     2B    S9    3F    3B     4F     4B
//COM3     S1    1A     S2    S8     2A    S3    S4    3A     S5     4A

//         SEG13 SEG12 SEG11 SEG10 SEG21  SEG20  SEG19 SEG18
//COM0     5E    5D     6E    6D     7E    7D    8E    8D
//COM1     5G    5C     6G    6C     7G    7C    8G    8C
//COM2     5F    5B     6F    6B     7F    7B    8F    8B
//COM3     COL   5A     S6    6A     S7    7A    S12   8A 
//****************************************************************//

//****************************************************************//
///LCD_CUL51R8T6
//
//         SEG0  SEG1   SEG2  SEG3   SEG4  SEG5  SEG6  SEG7   SEG8   SEG9
//COM0     1E    1D           2E     2D    S11   3E    3D     4E     4D
//COM1     1G    1C           2G     2C    S10   3G    3C     4G     4C
//COM2     1F    1B           2F     2B    S9    3F    3B     4F     4B
//COM3     S1    1A     S2    S8     2A    S3    S4    3A     S5     4A

//         SEG17 SEG16 SEG15 SEG14 SEG13  SEG25  SEG26 SEG27
//COM0     5E    5D     6E    6D     7E    7D    8E    8D
//COM1     5G    5C     6G    6C     7G    7C    8G    8C
//COM2     5F    5B     6F    6B     7F    7B    8F    8B
//COM3     COL   5A     S6    6A     S7    7A    S12   8A 
//****************************************************************//
LCD_RAM_ARRAY LCD_ARRAY;
#if defined(LCD_CUL51R8T6)
 LCD_SEG_COM_STRUCT CIUL051_SEG0_SEG31[SEG0_PIN_NUMBER_BY_CIUL051]={

   {HARD_LCD_SEG0,  (GPIO_t*)GpioPortA,GpioPin15},\
   {HARD_LCD_SEG1,  (GPIO_t*)GpioPortC,GpioPin10},\
   {HARD_LCD_SEG2,  (GPIO_t*)GpioPortC,GpioPin11},\
   {HARD_LCD_SEG3,  (GPIO_t*)GpioPortB,GpioPin3},\
   {HARD_LCD_SEG4,  (GPIO_t*)GpioPortB,GpioPin4},\
   {HARD_LCD_SEG5,  (GPIO_t*)GpioPortB,GpioPin5},\
   {HARD_LCD_SEG6,  (GPIO_t*)GpioPortB,GpioPin6},\
   {HARD_LCD_SEG7,  (GPIO_t*)GpioPortB,GpioPin7},\
   {HARD_LCD_SEG8,  (GPIO_t*)GpioPortB,GpioPin8},\
   {HARD_LCD_SEG9,  (GPIO_t*)GpioPortB,GpioPin9},\
   {HARD_LCD_SEG10, (GPIO_t*)GpioPortB,GpioPin10},\
   {HARD_LCD_SEG11, (GPIO_t*)GpioPortB,GpioPin11},\
   {HARD_LCD_SEG12, (GPIO_t*)GpioPortB,GpioPin12},\
   {HARD_LCD_SEG13, (GPIO_t*)GpioPortB,GpioPin13},\
   {HARD_LCD_SEG14, (GPIO_t*)GpioPortB,GpioPin14},\
   {HARD_LCD_SEG15, (GPIO_t*)GpioPortB,GpioPin15},\
   {HARD_LCD_SEG16, (GPIO_t*)GpioPortA,GpioPin8},\
   {HARD_LCD_SEG17, (GPIO_t*)GpioPortA,GpioPin9},\
   {HARD_LCD_SEG18, (GPIO_t*)GpioPortC,GpioPin0},\
   {HARD_LCD_SEG19, (GPIO_t*)GpioPortC,GpioPin1},\
   {HARD_LCD_SEG20, (GPIO_t*)GpioPortC,GpioPin2},\
   {HARD_LCD_SEG21, (GPIO_t*)GpioPortC,GpioPin3},\
   {HARD_LCD_SEG22, (GPIO_t*)GpioPortC,GpioPin4},\
   {HARD_LCD_SEG23, (GPIO_t*)GpioPortC,GpioPin5},\
   {HARD_LCD_SEG24, (GPIO_t*)GpioPortC,GpioPin6},\
   {HARD_LCD_SEG25, (GPIO_t*)GpioPortD,GpioPin3},\
   {HARD_LCD_SEG26, (GPIO_t*)GpioPortD,GpioPin4},\
   {HARD_LCD_SEG27, (GPIO_t*)GpioPortD,GpioPin5},\
   {HARD_LCD_SEG28, (GPIO_t*)GpioPortC,GpioPin7},\
   {HARD_LCD_SEG29, (GPIO_t*)GpioPortC,GpioPin8},\
   {HARD_LCD_SEG30, (GPIO_t*)GpioPortD,GpioPin0},\
   {HARD_LCD_SEG31, (GPIO_t*)GpioPortD,GpioPin1},\
    
};
LCD_SEG_COM_STRUCT CIUL051_LCD_COM[COM_PIN_NUMBER_BY_CIUL051]={

   {HARD_LCD_COM0,  (GPIO_t*)GpioPortC,GpioPin9},\
   {HARD_LCD_COM1,  (GPIO_t*)GpioPortA,GpioPin10},\
   {HARD_LCD_COM2,  (GPIO_t*)GpioPortA,GpioPin11},\
   {HARD_LCD_COM3,  (GPIO_t*)GpioPortA,GpioPin12},\
};
#else
LCD_SEG_COM_STRUCT CIUL051_SEG0_SEG31[SEG0_PIN_NUMBER_BY_CIUL051]={

   {HARD_LCD_SEG0,  (GPIO_t*)GpioPortA,GpioPin15},\
   {HARD_LCD_SEG1,  (GPIO_t*)GpioPortC,GpioPin10},\
   {HARD_LCD_SEG2,  (GPIO_t*)GpioPortC,GpioPin11},\
   {HARD_LCD_SEG3,  (GPIO_t*)GpioPortB,GpioPin3},\
   {HARD_LCD_SEG4,  (GPIO_t*)GpioPortB,GpioPin4},\
   {HARD_LCD_SEG5,  (GPIO_t*)GpioPortB,GpioPin5},\
   {HARD_LCD_SEG6,  (GPIO_t*)GpioPortB,GpioPin6},\
   {HARD_LCD_SEG7,  (GPIO_t*)GpioPortB,GpioPin7},\
   {HARD_LCD_SEG8,  (GPIO_t*)GpioPortB,GpioPin8},\
   {HARD_LCD_SEG9,  (GPIO_t*)GpioPortB,GpioPin9},\
   {HARD_LCD_SEG10, (GPIO_t*)GpioPortB,GpioPin10},\
   {HARD_LCD_SEG11, (GPIO_t*)GpioPortB,GpioPin11},\
   {HARD_LCD_SEG12, (GPIO_t*)GpioPortB,GpioPin12},\
   {HARD_LCD_SEG13, (GPIO_t*)GpioPortB,GpioPin13},\
   {HARD_LCD_SEG14, (GPIO_t*)GpioPortB,GpioPin14},\
   {HARD_LCD_SEG15, (GPIO_t*)GpioPortB,GpioPin15},\
   {HARD_LCD_SEG18, (GPIO_t*)GpioPortA,GpioPin4},\
   {HARD_LCD_SEG19, (GPIO_t*)GpioPortA,GpioPin5},\
   {HARD_LCD_SEG20, (GPIO_t*)GpioPortA,GpioPin6},\
   {HARD_LCD_SEG21, (GPIO_t*)GpioPortA,GpioPin7},\
   {HARD_LCD_SEG30, (GPIO_t*)GpioPortD,GpioPin0},\
   {HARD_LCD_SEG31, (GPIO_t*)GpioPortD,GpioPin1},\
    
};
LCD_SEG_COM_STRUCT CIUL051_LCD_COM[COM_PIN_NUMBER_BY_CIUL051]={

   {HARD_LCD_COM0,  (GPIO_t*)GpioPortC,GpioPin9},\
   {HARD_LCD_COM1,  (GPIO_t*)GpioPortA,GpioPin10},\
   {HARD_LCD_COM2,  (GPIO_t*)GpioPortA,GpioPin11},\
   {HARD_LCD_COM3,  (GPIO_t*)GpioPortA,GpioPin12},\
};
#endif

//****************************************************************//
//函数名称: void Bsp_Lcd_Gpio_Config(void)
//函数功能: LCD端口配置
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Lcd_Gpio_Config(void){

   std_gpio_init_t  lcd_gpio_config = {0};
  
   /* GPIO时钟使能 */
   std_rcc_gpio_clk_enable(RCC_PERIPH_CLK_GPIOA | RCC_PERIPH_CLK_GPIOB | RCC_PERIPH_CLK_GPIOC|RCC_PERIPH_CLK_GPIOD);
            
   lcd_gpio_config.mode = GPIO_MODE_ALTERNATE;
   lcd_gpio_config.alternate = GPIO_AF3_LCD; 
   //配置SEG0-SEG31的有效PIN
   for(uint8_t j=0;j<SEG0_PIN_NUMBER_BY_CIUL051;j++){

      if((LCD_SEG_0_31)&CIUL051_SEG0_SEG31[j].ordef_number){
          
        lcd_gpio_config.pin = CIUL051_SEG0_SEG31[j].pin;
        std_gpio_init(CIUL051_SEG0_SEG31[j].port_t, &lcd_gpio_config);
      
      }
   }

   //配置COM0-COM3的有效PIN
   for(uint8_t j=0;j<COM_PIN_NUMBER_BY_CIUL051;j++){

      if((LCD_COM)&CIUL051_LCD_COM[j].ordef_number) {
          
        lcd_gpio_config.pin = CIUL051_LCD_COM[j].pin;
        std_gpio_init(CIUL051_LCD_COM[j].port_t, &lcd_gpio_config);
          
      }

   }

}
//****************************************************************//
//函数名称: void Bsp_Lcd_Init(void)
//函数功能: LCD初始化
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Lcd_Init(void){

    std_lcd_init_t lcd_config = {0};
    
    Bsp_Lcd_Gpio_Config();

    std_rcc_apb1_clk_enable(RCC_PERIPH_CLK_LCD); 
    /* LCD防极化 */
    std_lcd_set_anti_polar(LCD_ANTIPOLAR_GND);
    /* LCD输出禁止，COM和SEG端子在LCD使能后连接到GND */
    std_lcd_set_scoc(LCD_SCOC_GND);

    /* VLCD、LCD_V1、LCD_V2引脚外接电容配置 */
    std_lcd_v1_cap_enable();
    std_lcd_v2_cap_enable();
    std_lcd_vlcd_cap_enable();

    /* 片外电容分压时钟分频 */
    std_lcd_set_chargepump_clock(LCD_CPCLK_DIV4);

    /* LCD参数配置 */
    lcd_config.mux_segment = LCD_MUX_SEGMENT_ENABLE;        /* 1/6 和 1/4duty需使能区段多路复用，1/8duty为无关项 */
    lcd_config.bias = LCD_BIAS_1_3;
    lcd_config.duty = LCD_DUTY_1_4;
    lcd_config.driver_mode = LCD_DRIVER_MODE_CHARGE_PUMP;
    lcd_config.prescaler = LCD_PRESCALER_4;                 /* 帧速率配置为32Hz */
    lcd_config.divider = LCD_DIVIDER_31;
    lcd_config.vlcd_voltage = LCD_CHAGE_PUMP_1_3_BIAS_3_30V;/* VLCD电压3.3V */
 
    /* LCD 初始化 */
    std_lcd_init(&lcd_config);

    /* 等待输出驱动电压稳定 
       当前为电荷泵时钟4分频下的输出驱动电压稳定时间 */
    std_delayms(LCD_DRIVER_VOLTAGE_DELAY);
    
    /* LCD COM和SEG波形输出 */
    std_lcd_set_scoc(LCD_SCOC_OUT);
}

//****************************************************************//
//函数名称: void Bsp_Disp_A(uint8_t pos)
//函数功能: 显示A
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_A(uint8_t pos){

 #if defined(LCD_CUL51R8T6)
   switch(pos){
    
    case Sec_Unit:
      //8A   
      LCD_ARRAY.RAM3|=BIT27;
     break;
    case Sec_Decade:
      //7A   
      LCD_ARRAY.RAM3|=BIT25;
     break;
    case Minute_Unit:
      //6A   
      LCD_ARRAY.RAM3|=BIT14;
     break;
    case Minute_Decade:
      //5A   
      LCD_ARRAY.RAM3|=BIT16;
     break;
    case Hours_Unit:
      //4A   
      LCD_ARRAY.RAM3|=BIT9;
     break;    
    case Hours_Decade:
      //3A   
      LCD_ARRAY.RAM3|=BIT7;
     break;
    case Timing_Unit:
      //2A 
      LCD_ARRAY.RAM3|=BIT4;
     break;
    case Timing_Decade:
      //1A 
      LCD_ARRAY.RAM3|=BIT1;
     break;
    default:
     break;
  } 
 #else
  switch(pos){
    
    case Sec_Unit:
      //8A   
      LCD_ARRAY.RAM3|=0x00040000;    
     break;
    case Sec_Decade:
      //7A   
      LCD_ARRAY.RAM3|=0x00100000;        
     break;
    case Minute_Unit:
      //6A   
      LCD_ARRAY.RAM3|=0x00000400;     
     break;
    case Minute_Decade:
      //5A   
      LCD_ARRAY.RAM3|=0x00001000;    
     break;
    case Hours_Unit:
      //4A   
      LCD_ARRAY.RAM3|=0x00000200;
     break;    
    case Hours_Decade:
      //3A   
      LCD_ARRAY.RAM3|=0x00000080;       
     break;
    case Timing_Unit:
      //2A 
      LCD_ARRAY.RAM3|=0x00000010;
     break;
    case Timing_Decade:
      //1A 
      LCD_ARRAY.RAM3|=0x00000002;
     break;
    default:
     break;
  }
 #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_B(uint8_t pos)
//函数功能: 显示B
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_B(uint8_t pos){

 #if defined(LCD_CUL51R8T6)
   switch(pos){
    
    case Sec_Unit:
      //8B 
      LCD_ARRAY.RAM2|=BIT27;            
     break;
    case Sec_Decade:
     //7B 
      LCD_ARRAY.RAM2|=BIT25;      
     break;
    case Minute_Unit:
     //6B 
      LCD_ARRAY.RAM2|=BIT14;      
     break;
    case Minute_Decade:
     //5B 
      LCD_ARRAY.RAM2|=BIT16;     
     break;
    case Hours_Unit:
      //4B 
      LCD_ARRAY.RAM2|=BIT9;   
     break;    
    case Hours_Decade:
      //3B 
      LCD_ARRAY.RAM2|=BIT7;         
     break;
    case Timing_Unit:
      //2B 
      LCD_ARRAY.RAM2|=BIT4;     
     break;
    case Timing_Decade:
      //1B 
      LCD_ARRAY.RAM2|=BIT1;    
     break;
    default:
     break;
  }
 #else
  switch(pos){
    
    case Sec_Unit:
      //8B 
      LCD_ARRAY.RAM2|=0x00040000;            
     break;
    case Sec_Decade:
     //7B 
      LCD_ARRAY.RAM2|=0x00100000;      
     break;
    case Minute_Unit:
     //6B 
      LCD_ARRAY.RAM2|=0x00000400;      
     break;
    case Minute_Decade:
     //5B 
      LCD_ARRAY.RAM2|=0x00001000;     
     break;
    case Hours_Unit:
      //4B 
      LCD_ARRAY.RAM2|=0x00000200;   
     break;    
    case Hours_Decade:
      //3B 
      LCD_ARRAY.RAM2|=0x00000080;         
     break;
    case Timing_Unit:
      //2B 
      LCD_ARRAY.RAM2|=0x00000010;     
     break;
    case Timing_Decade:
      //1B 
      LCD_ARRAY.RAM2|=0x00000002;    
     break;
    default:
     break;
  }
  #endif

}
//****************************************************************//
//函数名称: void Bsp_Disp_C(uint8_t pos)
//函数功能: 显示C
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_C(uint8_t pos){

 #if defined(LCD_CUL51R8T6)
    switch(pos){
    
    case Sec_Unit:
      //8C 
      LCD_ARRAY.RAM1|=BIT27;       
     break;
    case Sec_Decade:
      //7C 
      LCD_ARRAY.RAM1|=BIT25;     
     break;
    case Minute_Unit:
     //6C 
      LCD_ARRAY.RAM1|=BIT14;    
     break;
    case Minute_Decade:
     //5C 
      LCD_ARRAY.RAM1|=BIT16;      
     break;
    case Hours_Unit:
     //4C 
      LCD_ARRAY.RAM1|=BIT9;     
     break;    
    case Hours_Decade:
     //3C 
      LCD_ARRAY.RAM1|=BIT7;     
     break;
    case Timing_Unit:
     //2C 
      LCD_ARRAY.RAM1|=BIT4;
     break;
    case Timing_Decade:
      //1C
      LCD_ARRAY.RAM1|=BIT1;
     break;
    default:
     break;
  }
 #else    
    switch(pos){
    
    case Sec_Unit:
      //8C 
      LCD_ARRAY.RAM1|=0x00040000;       
     break;
    case Sec_Decade:
      //7C 
      LCD_ARRAY.RAM1|=0x00100000;     
     break;
    case Minute_Unit:
     //6C 
      LCD_ARRAY.RAM1|=0x00000400;    
     break;
    case Minute_Decade:
     //5C 
      LCD_ARRAY.RAM1|=0x00001000;      
     break;
    case Hours_Unit:
     //4C 
      LCD_ARRAY.RAM1|=0x00000200;     
     break;    
    case Hours_Decade:
     //3C 
      LCD_ARRAY.RAM1|=0x00000080;     
     break;
    case Timing_Unit:
     //2C 
      LCD_ARRAY.RAM1|=0x00000010;
     break;
    case Timing_Decade:
      //1C
      LCD_ARRAY.RAM1|=0x00000002;
     break;
    default:
     break;
  }
#endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_D(uint8_t pos)
//函数功能: 显示D
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_D(uint8_t pos){

    
  #if defined(LCD_CUL51R8T6)
  switch(pos){
    
    case Sec_Unit:
      //8D 
      LCD_ARRAY.RAM0|=BIT27;
     break;
    case Sec_Decade:
      //7D 
      LCD_ARRAY.RAM0|=BIT25;
     break;
    case Minute_Unit:
      //6D 
      LCD_ARRAY.RAM0|=BIT14;     
     break;
    case Minute_Decade:
     //5D 
      LCD_ARRAY.RAM0|=BIT16;       
     break;
    case Hours_Unit:
     //4D 
      LCD_ARRAY.RAM0|=BIT9;      
     break;    
    case Hours_Decade:
     //3D 
      LCD_ARRAY.RAM0|=BIT7;         
     break;
    case Timing_Unit:
      //2D 
      LCD_ARRAY.RAM0|=BIT4;   
     break;
    case Timing_Decade:
      //1D 
      LCD_ARRAY.RAM0|=BIT1;     
     break;
    default:
     break;
  }
 #else
   switch(pos){
    
    case Sec_Unit:
      //8D 
      LCD_ARRAY.RAM0|=0x00040000;
     break;
    case Sec_Decade:
      //7D 
      LCD_ARRAY.RAM0|=0x00100000;
     break;
    case Minute_Unit:
      //6D 
      LCD_ARRAY.RAM0|=0x00000400;     
     break;
    case Minute_Decade:
     //5D 
      LCD_ARRAY.RAM0|=0x00001000;       
     break;
    case Hours_Unit:
     //4D 
      LCD_ARRAY.RAM0|=0x00000200;      
     break;    
    case Hours_Decade:
     //3D 
      LCD_ARRAY.RAM0|=0x00000080;         
     break;
    case Timing_Unit:
      //2D 
      LCD_ARRAY.RAM0|=0x00000010;   
     break;
    case Timing_Decade:
      //1D 
      LCD_ARRAY.RAM0|=0x00000002;     
     break;
    default:
     break;
  } 
 #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_E(uint8_t pos)
//函数功能: 显示E
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_E(uint8_t pos){

  #if defined(LCD_CUL51R8T6)
  switch(pos){
    
    case Sec_Unit:
     //8E 
     LCD_ARRAY.RAM0|=BIT26;       
     break;
    case Sec_Decade:
     //7E 
     LCD_ARRAY.RAM0|=BIT13;    
     break;
    case Minute_Unit:
     //6E 
     LCD_ARRAY.RAM0|=BIT15;     
     break;
    case Minute_Decade:
     //5E 
     LCD_ARRAY.RAM0|=BIT17;       
     break;
    case Hours_Unit:
     //4E 
     LCD_ARRAY.RAM0|=BIT8;    
     break;    
    case Hours_Decade:
    //3E 
     LCD_ARRAY.RAM0|=BIT6;       
     break;
    case Timing_Unit:
     //2E 
     LCD_ARRAY.RAM0|=BIT3;    
     break;
    case Timing_Decade:
     //1E 
     LCD_ARRAY.RAM0|=BIT0;     
     break;
    default:
     break;
  }
  #else
  switch(pos){
    
    case Sec_Unit:
     //8E 
     LCD_ARRAY.RAM0|=0x00080000;       
     break;
    case Sec_Decade:
     //7E 
     LCD_ARRAY.RAM0|=0x00200000;    
     break;
    case Minute_Unit:
     //6E 
     LCD_ARRAY.RAM0|=0x00000800;     
     break;
    case Minute_Decade:
     //5E 
     LCD_ARRAY.RAM0|=0x00002000;       
     break;
    case Hours_Unit:
     //4E 
     LCD_ARRAY.RAM0|=0x00000100;    
     break;    
    case Hours_Decade:
    //3E 
     LCD_ARRAY.RAM0|=0x00000040;       
     break;
    case Timing_Unit:
     //2E 
     LCD_ARRAY.RAM0|=0x00000008;    
     break;
    case Timing_Decade:
     //1E 
     LCD_ARRAY.RAM0|=0x00000001;     
     break;
    default:
     break;
  }
  #endif

}
//****************************************************************//
//函数名称: void Bsp_Disp_F(uint8_t pos)
//函数功能: 显示F
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_F(uint8_t pos){

  #if defined(LCD_CUL51R8T6)
  switch(pos){
    
    case Sec_Unit:
     //8F 
     LCD_ARRAY.RAM2|=BIT26;     
     break;
    case Sec_Decade:
     //7F 
     LCD_ARRAY.RAM2|=BIT13;      
     break;
    case Minute_Unit:
     //6F 
     LCD_ARRAY.RAM2|=BIT15;      
     break;
    case Minute_Decade:
     //5F 
     LCD_ARRAY.RAM2|=BIT17;          
     break;
    case Hours_Unit:
     //4F 
     LCD_ARRAY.RAM2|=BIT8;    
     break;    
    case Hours_Decade:
     //3F 
     LCD_ARRAY.RAM2|=BIT6;        
     break;
    case Timing_Unit:
     //2F 
     LCD_ARRAY.RAM2|=BIT3;    
     break;
    case Timing_Decade:
     //1F 
     LCD_ARRAY.RAM2|=BIT0;     
     break;
    default:
     break;
  }
#else
  switch(pos){
    
    case Sec_Unit:
     //8F 
     LCD_ARRAY.RAM2|=0x00080000;     
     break;
    case Sec_Decade:
     //7F 
     LCD_ARRAY.RAM2|=0x00200000;      
     break;
    case Minute_Unit:
     //6F 
     LCD_ARRAY.RAM2|=0x00000800;      
     break;
    case Minute_Decade:
     //5F 
     LCD_ARRAY.RAM2|=0x00002000;          
     break;
    case Hours_Unit:
     //4F 
     LCD_ARRAY.RAM2|=0x00000100;    
     break;    
    case Hours_Decade:
     //3F 
     LCD_ARRAY.RAM2|=0x00000040;        
     break;
    case Timing_Unit:
     //2F 
     LCD_ARRAY.RAM2|=0x00000008;    
     break;
    case Timing_Decade:
     //1F 
     LCD_ARRAY.RAM2|=0x00000001;     
     break;
    default:
     break;
  }
#endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_G(uint8_t pos)
//函数功能: 显示G
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_G(uint8_t pos){

  #if defined(LCD_CUL51R8T6)
  switch(pos){
    
    case Sec_Unit:
     //8G 
     LCD_ARRAY.RAM1|=BIT26;     
     break;
    case Sec_Decade:
     //7G 
     LCD_ARRAY.RAM1|=BIT13;      
     break;
    case Minute_Unit:
     //6G 
     LCD_ARRAY.RAM1|=BIT15;          
     break;
    case Minute_Decade:
     //5G
     LCD_ARRAY.RAM1|=BIT17;     
     break;
    case Hours_Unit:
     //4G 
     LCD_ARRAY.RAM1|=BIT8;     
     break;    
    case Hours_Decade:
     //3G 
     LCD_ARRAY.RAM1|=BIT6;
     break;
    case Timing_Unit:
     //2G 
     LCD_ARRAY.RAM1|=BIT3;
     break;
    case Timing_Decade:
     //1G 
     LCD_ARRAY.RAM1|=BIT0;
     break;
    default:
     break;
  }
  #else
  switch(pos){
    
    case Sec_Unit:
     //8G 
     LCD_ARRAY.RAM1|=0x00080000;     
     break;
    case Sec_Decade:
     //7G 
     LCD_ARRAY.RAM1|=0x00200000;      
     break;
    case Minute_Unit:
     //6G 
     LCD_ARRAY.RAM1|=0x00000800;          
     break;
    case Minute_Decade:
     //5G
     LCD_ARRAY.RAM1|=0x00002000;     
     break;
    case Hours_Unit:
     //4G 
     LCD_ARRAY.RAM1|=0x00000100;     
     break;    
    case Hours_Decade:
     //3G 
     LCD_ARRAY.RAM1|=0x00000040;
     break;
    case Timing_Unit:
     //2G 
     LCD_ARRAY.RAM1|=0x00000008;
     break;
    case Timing_Decade:
     //1G 
     LCD_ARRAY.RAM1|=0x00000001;
     break;
    default:
     break;
  }
  #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Col(void)
//函数功能: 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Col(void){
    
   #if defined(LCD_CUL51R8T6)
        //COL
     LCD_ARRAY.RAM3|=BIT17;    
   #else
        //COL
     LCD_ARRAY.RAM3|=0x00002000;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Monday(void)
//函数功能: 显示星期1
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Monday(void){

   #if defined(LCD_CUL51R8T6)

    LCD_ARRAY.RAM3|=BIT0;    
   #else
    LCD_ARRAY.RAM3|=0x00000001;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Tuesday(void)
//函数功能: 显示星期2
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Tuesday(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM3|=BIT2;    
   #else
   LCD_ARRAY.RAM3|=0x00000004;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Wednesday(void)
//函数功能: 显示星期3
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Wednesday(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM3|=BIT5;    
   #else
   LCD_ARRAY.RAM3|=0x00000020;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Thursday(void)
//函数功能: 显示星期4
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Thursday(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM3|=BIT6;    
   #else
   LCD_ARRAY.RAM3|=0x00000040;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Friday(void)
//函数功能: 显示星期5
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Friday(void){

   #if defined(LCD_CUL51R8T6)
    LCD_ARRAY.RAM3|=BIT8;    
   #else
    LCD_ARRAY.RAM3|=0x00000100;   
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Saturday(void)
//函数功能: 显示星期6
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Saturday(void){

  #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM3|=BIT15;    
  #else
   LCD_ARRAY.RAM3|=0x00000800;  
  #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Sunday(void)
//函数功能: 显示星期天
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Sunday(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM3|=BIT13;    
   #else
   LCD_ARRAY.RAM3|=0x00200000;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Bluetooth(void)
//函数功能: 显示蓝牙
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Bluetooth(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM3|=BIT3;    
   #else
   LCD_ARRAY.RAM3|=0x00000008;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_TimingOpen(void)
//函数功能: 显示开
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_TimingOpen(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM1|=BIT5;    
   #else
   LCD_ARRAY.RAM1|=0x00000020;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_TimingClose(void)
//函数功能: 显示关
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_TimingClose(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM0|=BIT5;    
   #else
   LCD_ARRAY.RAM0|=0x00000020;    
   #endif
}
 //****************************************************************//
//函数名称: void Bsp_Disp_TimingAuto(void)
//函数功能: 显示自动
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_TimingAuto(void){

   #if defined(LCD_CUL51R8T6)
   LCD_ARRAY.RAM2|=BIT5;    
   #else
   LCD_ARRAY.RAM2|=0x00000020;    
   #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Lock(void)
//函数功能: 显示锁
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_Lock(void){
    
  #if defined(LCD_CUL51R8T6)
    LCD_ARRAY.RAM3|=BIT26;   
  #else
    LCD_ARRAY.RAM3|=0x00080000;   
  #endif
}
//****************************************************************//
//函数名称: void Bsp_Disp_Lock(void)
//函数功能: 显示锁
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Write_To_LCD_RAM(uint32_t *data){

   
   for(uint8_t RamIndex=0u;RamIndex<4;RamIndex++)
     //0-4
     std_lcd_write(RamIndex,~LCD->RAM[RamIndex],*(data+RamIndex));
    

}
//****************************************************************//
//函数名称: void Bsp_Clear_Lcd_Ram_Arrary(void)
//函数功能: 清除顯示
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Clear_Lcd_Ram_Arrary(void){

    uint32_t *Ram=NULL;
    Ram=(uint32_t*)&LCD_ARRAY.RAM0;
    for(uint8_t i=0u;i<4u;i++)
        *(Ram+i)=0u;
}
//****************************************************************//
//函数名称: void Bsp_Disp_All(void)
//函数功能: 显示所有
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_All(void){

  uint32_t data[4];
  for(uint8_t i=0u;i<4u;i++)
   data[i]=0xffffffff;  
  Bsp_Write_To_LCD_RAM(data);
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_A(uint8_t Pos)
//函数功能: 显示ASCII A
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_A(uint8_t Pos){

    Bsp_Disp_A(Pos);
    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);

}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_B(uint8_t Pos)
//函数功能: 显示ASCII B
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_B(uint8_t Pos){


    Bsp_Disp_C(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);

}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_C(uint8_t Pos)
//函数功能: 显示ASCII C
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_C(uint8_t Pos){


    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_A(Pos);

}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_D(uint8_t Pos)
//函数功能: 显示ASCII D
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_D(uint8_t Pos){


    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_B(Pos);
    Bsp_Disp_G(Pos);
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_E(uint8_t Pos)
//函数功能: 显示ASCII E
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_E(uint8_t Pos){


    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_A(Pos);
    Bsp_Disp_G(Pos);
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_F(uint8_t Pos)
//函数功能: 显示ASCII F
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_F(uint8_t Pos){



    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_A(Pos);
    Bsp_Disp_G(Pos);
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_G(uint8_t Pos)
//函数功能: 显示ASCII G
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_G(uint8_t Pos){



    Bsp_Disp_A(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);

}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_H(uint8_t Pos)
//函数功能: 显示ASCII H
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_H(uint8_t Pos){

    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_I(uint8_t Pos)
//函数功能: 显示ASCII I
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_I(uint8_t Pos){

    Bsp_Disp_E(Pos);

}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_J(uint8_t Pos)
//函数功能: 显示ASCII J
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_J(uint8_t Pos){

    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_D(Pos);
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_K(uint8_t Pos)
//函数功能: 显示ASCII K
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_K(uint8_t Pos){

    Bsp_Disp_B(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_L(uint8_t Pos)
//函数功能: 显示ASCII L
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_L(uint8_t Pos){


    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    
}

//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_M(uint8_t Pos)
//函数功能: 显示ASCII M
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_M(uint8_t Pos){


    Bsp_Disp_A(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_N(uint8_t Pos)
//函数功能: 显示ASCII N
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_N(uint8_t Pos){

    Bsp_Disp_C(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_O(uint8_t Pos)
//函数功能: 显示ASCII O
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_O(uint8_t Pos){


    Bsp_Disp_C(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_P(uint8_t Pos)
//函数功能: 显示ASCII P
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_P(uint8_t Pos){


    Bsp_Disp_A(Pos);
    Bsp_Disp_B(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_Q(uint8_t Pos)
//函数功能: 显示ASCII Q
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_Q(uint8_t Pos){


    Bsp_Disp_A(Pos);
    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_R(uint8_t Pos)
//函数功能: 显示ASCII R
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_R(uint8_t Pos){

    Bsp_Disp_E(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_S(uint8_t Pos)
//函数功能: 显示ASCII S
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_S(uint8_t Pos){

    Bsp_Disp_C(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_T(uint8_t Pos)
//函数功能: 显示ASCII T 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_T(uint8_t Pos){

    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_U(uint8_t Pos)
//函数功能: 显示ASCII U 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_U(uint8_t Pos){


    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_V(uint8_t Pos)
//函数功能: 显示ASCII V 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_V(uint8_t Pos){

    Bsp_Disp_B(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_W(uint8_t Pos)
//函数功能: 显示ASCII W 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_W(uint8_t Pos){


    Bsp_Disp_B(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_X(uint8_t Pos)
//函数功能: 显示ASCII X 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_X(uint8_t Pos){

    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_E(Pos);
    Bsp_Disp_F(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_Y(uint8_t Pos)
//函数功能: 显示ASCII Y 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_Y(uint8_t Pos){

    Bsp_Disp_B(Pos);
    Bsp_Disp_C(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_F(Pos);
    Bsp_Disp_G(Pos);
    
}
//****************************************************************//
//函数名称: void Bsp_Disp_ASCII_Y(uint8_t Pos)
//函数功能: 显示ASCII Y 
//参    数: 
//返 回 值: 
//说    明：
//修改记录: 2024.09.27,whm创建函数  
//***************************************************************//
void Bsp_Disp_ASCII_Z(uint8_t Pos){


    Bsp_Disp_A(Pos);
    Bsp_Disp_D(Pos);
    Bsp_Disp_G(Pos);
    
}






