/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/

#ifndef _OV7670_H
#define _OV7670_H


#include "sccb.h"
#include "main.h"
#include "stm32f4xx_exti.h"

#define OV7670_REG_NUM  167

 #define Sensor_VSYNC_BIT    GPIO_Pin_3
  #define GPIO_VSYNC_CMOS                   GPIOE// GPIOC
  #define RCC_AHB1Periph_GPIO_VSYNC_CMOS     RCC_AHB1Periph_GPIOE//RCC_AHB1Periph_GPIOC
  #define GPIO_PIN_VSYNC_CMOS                GPIO_Pin_3
  #define EXTI_LINE_VSYNC_CMOS               EXTI_Line3
  #define GPIO_PORT_SOURCE_VSYNC_CMOS        EXTI_PortSourceGPIOE//EXTI_PortSourceGPIOC
  #define GPIO_PIN_SOURCE_VSYNC_CMOS         EXTI_PinSource3


/////////////////////////////////////////
void XCLK_init_ON(void);//STM32 mco功能开启 输出时钟给CMOS传感器 sensor.c

unsigned char wr_Sensor_Reg(unsigned char regID, unsigned char regDat);	//sensor.c
unsigned char rd_Sensor_Reg(unsigned char regID, unsigned char *regDat);	//sensor.c

unsigned char Sensor_init(void);	//sensor.c
void Sensor_GPIO_Init(void);	//sensor.c
void Sensor_EXTI_Config(void);	//sensor.c
void Sensor_Interrupts_Config(void);	//sensor.c

#endif /* _OV7670_H */



