#ifndef _SYSTEM_EXTERN_H_
#define _SYSTEM_EXTERN_H_

#include "ciu32l051.h"
#include "ciu32l051_std_gpio.h"



/**
 *******************************************************************************
 ** \brief GPIO PORT类型定义
 ******************************************************************************/
typedef enum en_gpio_port
{
    GpioPortA = GPIOA_BASE,                 ///< GPIO PORT A
    GpioPortB = GPIOB_BASE,                 ///< GPIO PORT B
    GpioPortC = GPIOC_BASE,                 ///< GPIO PORT C
    GpioPortD = GPIOD_BASE,                 ///< GPIO PORT D
    GpioPortF = GPIOF_BASE,                 ///< GPIO PORT F 
}en_gpio_port_t;
 /**
 *******************************************************************************
 ** \brief GPIO PIN类型定义
 ******************************************************************************/
typedef enum en_gpio_pin
{
    GpioPin0  = GPIO_PIN_0,                 ///< GPIO PIN0 
    GpioPin1  = GPIO_PIN_1,                 ///< GPIO PIN1 
    GpioPin2  = GPIO_PIN_2,                 ///< GPIO PIN2 
    GpioPin3  = GPIO_PIN_3,                 ///< GPIO PIN3 
    GpioPin4  = GPIO_PIN_4,                 ///< GPIO PIN4 
    GpioPin5  = GPIO_PIN_5,                 ///< GPIO PIN5 
    GpioPin6  = GPIO_PIN_6,                 ///< GPIO PIN6 
    GpioPin7  = GPIO_PIN_7,                 ///< GPIO PIN7 
    GpioPin8  = GPIO_PIN_8,                 ///< GPIO PIN8 
    GpioPin9  = GPIO_PIN_9,                 ///< GPIO PIN9 
    GpioPin10 = GPIO_PIN_10,                ///< GPIO PIN10
    GpioPin11 = GPIO_PIN_11,                ///< GPIO PIN11
    GpioPin12 = GPIO_PIN_12,                ///< GPIO PIN12
    GpioPin13 = GPIO_PIN_13,                ///< GPIO PIN13
    GpioPin14 = GPIO_PIN_14,                ///< GPIO PIN14
    GpioPin15 = GPIO_PIN_15,                ///< GPIO PIN15
}en_gpio_pin_t; 









#endif
