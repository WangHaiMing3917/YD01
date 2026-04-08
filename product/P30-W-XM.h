#ifndef _P30_H_
#define _P30_H_


#include "CIU32CT8X.h"


//软件版本
#define VERSION_H                  1u
#define VERSION_L                  0.0


//文件名
#define BIN_FILE_NAME(x)           uint8_t x = {"P30WXM.bin"}

#define MODEL_NAME(y)              char y= {" cnph.plug.p30wxm"}
//app_pid
#define DEVICE_PID                 21584u
//对应app_软件版本
#define DEVICE_VERSION             1u

#define MCU_VERSION                42u
//编译时间
#define AP_DATE                    {'2','0','2','5','0','9','1','0'}


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
                                       |HARD_LCD_SEG10  \
                                       |HARD_LCD_SEG11  \
                                       |HARD_LCD_SEG12  \
                                       |HARD_LCD_SEG13  \
                                       |HARD_LCD_SEG18  \
                                       |HARD_LCD_SEG19  \
                                       |HARD_LCD_SEG20  \
                                       |HARD_LCD_SEG21  \

#define LCD_SEG_32_35              0x00
//LCD_COM脚配置
#define LCD_COM                    0x00|HARD_LCD_COM0   \
                                       |HARD_LCD_COM1   \
                                       |HARD_LCD_COM2   \
                                       |HARD_LCD_COM3
                                       
//通道数量                                       
#define CHANNEL_NUMBER                 1u

#define KEY_MINUTE_PORT                GPIOB
#define KEY_MINUTE_PIN                 GPIO_PIN_15
#define KEY_MINUTE_EXTI_PORT           EXTI_GPIOB 
#define KEY_MINUTE_EXTI_LINE           EXTI_LINE_GPIO_PIN15

#define KEY_TIMING_PORT                GPIOB
#define KEY_TIMING_PIN                 GPIO_PIN_2
#define KEY_TIMING_EXTI_PORT           EXTI_GPIOB
#define KEY_TIMING_EXTI_LINE           EXTI_LINE_GPIO_PIN2

#define KEY_WEEKS_PORT                 GPIOF
#define KEY_WEEKS_PIN                  GPIO_PIN_0 
#define KEY_WEEKS_EXTI_PORT            EXTI_GPIOF
#define KEY_WEEKS_EXTI_LINE            EXTI_LINE_GPIO_PIN0

#define KEY_MODE_PORT                  GPIOF
#define KEY_MODE_PIN                   GPIO_PIN_1
#define KEY_MODE_EXTI_PORT             EXTI_GPIOF
#define KEY_MODE_EXTI_LINE             EXTI_LINE_GPIO_PIN1

#define KEY_HOURS_PORT                 GPIOB
#define KEY_HOURS_PIN                  GPIO_PIN_14
#define KEY_HOURS_EXTI_PORT            EXTI_GPIOB
#define KEY_HOURS_EXTI_LINE            EXTI_LINE_GPIO_PIN14

#define RELAYS_CHANNEL_1_PORT          GPIOC
#define RELAYS_CHANNEL_1_PIN           GPIO_PIN_13

#define BACK_LIGHT_PORT                GPIOA
#define BACK_LIGHT_PIN                 GPIO_PIN_14

#define RELASY_LED_1_PORT              GPIOA
#define RELASY_LED_1_PIN               GPIO_PIN_13

#define USART_TX_PORT                  GPIOA
#define USART_TX_PIN                   GPIO_PIN_3

#define USART_RX_PORT                  GPIOA
#define USART_RX_PIN                   GPIO_PIN_2

#define POWER_DOWN_PORT                GPIOA
#define POWER_DOWN_PIN                 GPIO_PIN_0
#define POWER_DOWN_EXTI_PORT           EXTI_GPIOA
#define POWER_DOWN_EXTI_LINE           EXTI_LINE_GPIO_PIN0


#define BLUETOOTH_DETECTION_PORT       GPIOA
#define BLUETOOTH_DETECTION_PIN        GPIO_PIN_1













#endif
