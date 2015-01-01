/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "fifo.h"
#include "Sensor.h"
#include "delay.h"
#include "stm32f4xx_conf.h"
//#include "stm32f429i_discovery_lcd.h"

#define LCD_RAM              (*((volatile unsigned short *) 0x6c000002)) /* RS = 1 */

void SYSTEM_Init(void);	
void RCC_Config(void);
void GPIO_Config(void);

/*****declare in main.c*********/
void SysTick_Init(void);
void Delay(__IO uint32_t nTime);
void Decrement_TimingDelay(void);
void Set_SELStatus(void);
void LCD_firm_init(void);
/*************************/

#endif /* __MAIN_H */


