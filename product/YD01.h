#ifndef _P30_H_
#define _P30_H_


#include "CIU32R8T6.h"


//软件版本
#define VERSION_H                  1u
#define VERSION_L                  0.0
//文件名
#define BIN_FILE_NAME(x)           uint8_t x = {"P30WXM.bin"}

//#define MODEL_NAME(y)              char y= {" cnph.plug.p30wxm"}
//app_pid
//#define DEVICE_PID                 31968u                     
//对应app_软件版本
#define DEVICE_VERSION             1u

#define MCU_VERSION                1u
//编译时间
#define AP_DATE                    {'2','0','2','6','0','4','1','4'}


//LCD_SEG脚配置
#define LCD_SEG_0_31               0x00|HARD_LCD_SEG0   \
                                       |HARD_LCD_SEG1   \
                                       |HARD_LCD_SEG2   \
                                       |HARD_LCD_SEG3   \
                                       |HARD_LCD_SEG4   \
                                       |HARD_LCD_SEG5   \
                                       |HARD_LCD_SEG6   \
                                       |HARD_LCD_SEG7   \
                                       |HARD_LCD_SEG8   \
                                       |HARD_LCD_SEG9   \
                                       |HARD_LCD_SEG13  \
                                       |HARD_LCD_SEG14  \
                                       |HARD_LCD_SEG15  \
                                       |HARD_LCD_SEG16  \
                                       |HARD_LCD_SEG17  \
                                       |HARD_LCD_SEG25  \
                                       |HARD_LCD_SEG26  \
                                       |HARD_LCD_SEG27  \

#define LCD_SEG_32_35              0x00
//LCD_COM脚配置
#define LCD_COM                    0x00|HARD_LCD_COM0   \
                                       |HARD_LCD_COM1   \
                                       |HARD_LCD_COM2   \
                                       |HARD_LCD_COM3
                                       
//通道数量                                       
#define CHANNEL_NUMBER                 3u
//使用R8T6芯片
#define LCD_CUL51R8T6
//使用串口1
#define USED_USART_1

#define KEY_MINUTE_PORT                GPIOB
#define KEY_MINUTE_PIN                 GPIO_PIN_11
#define KEY_MINUTE_EXTI_PORT           EXTI_GPIOB
#define KEY_MINUTE_EXTI_LINE           EXTI_LINE_GPIO_PIN11

#define KEY_TIMING_PORT                GPIOC
#define KEY_TIMING_PIN                 GPIO_PIN_2
#define KEY_TIMING_EXTI_PORT           EXTI_GPIOC
#define KEY_TIMING_EXTI_LINE           EXTI_LINE_GPIO_PIN2

#define KEY_WEEKS_PORT                 GPIOC
#define KEY_WEEKS_PIN                  GPIO_PIN_0 
#define KEY_WEEKS_EXTI_PORT            EXTI_GPIOC
#define KEY_WEEKS_EXTI_LINE            EXTI_LINE_GPIO_PIN0

#define KEY_MODE_PORT                  GPIOC
#define KEY_MODE_PIN                   GPIO_PIN_1
#define KEY_MODE_EXTI_PORT             EXTI_GPIOC
#define KEY_MODE_EXTI_LINE             EXTI_LINE_GPIO_PIN1

#define KEY_HOURS_PORT                 GPIOB
#define KEY_HOURS_PIN                  GPIO_PIN_12
#define KEY_HOURS_EXTI_PORT            EXTI_GPIOB
#define KEY_HOURS_EXTI_LINE            EXTI_LINE_GPIO_PIN12

#define RELAYS_CHANNEL_1_PORT          GPIOA
#define RELAYS_CHANNEL_1_PIN           GPIO_PIN_5

#define RELAYS_CHANNEL_2_PORT          GPIOA
#define RELAYS_CHANNEL_2_PIN           GPIO_PIN_4

#define RELAYS_CHANNEL_3_PORT          GPIOC
#define RELAYS_CHANNEL_3_PIN           GPIO_PIN_6

#define RELAYS_CHANNEL_4_PORT          GPIOC
#define RELAYS_CHANNEL_4_PIN           GPIO_PIN_5

#define RELAYS_CHANNEL_5_PORT          GPIOC
#define RELAYS_CHANNEL_5_PIN           GPIO_PIN_4

#define BACK_LIGHT_PORT                GPIOC
#define BACK_LIGHT_PIN                 GPIO_PIN_8

#define USART_TX_PORT                  GPIOA
#define USART_TX_PIN                   GPIO_PIN_2

#define USART_RX_PORT                  GPIOA
#define USART_RX_PIN                   GPIO_PIN_1

#define POWER_DOWN_PORT                GPIOA
#define POWER_DOWN_PIN                 GPIO_PIN_0
#define POWER_DOWN_EXTI_PORT           EXTI_GPIOA
#define POWER_DOWN_EXTI_LINE           EXTI_LINE_GPIO_PIN0

#define MODE_PORT                      GPIOC
#define MODE_PIN                       GPIO_PIN_3

#define BLUETOOTH_DETECTION_PORT       GPIOA
#define BLUETOOTH_DETECTION_PIN        GPIO_PIN_3













#endif
