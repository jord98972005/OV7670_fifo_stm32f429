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

#define OV7670_REG_NUM  167

 #define Sensor_VSYNC_BIT    GPIO_Pin_7
//#define DCMI_DR_ADDRESS       	0x50050028   
//#define FSMC_LCD_ADDRESS      	0x60020000
/////////////////////////////////////////
void XCLK_init_ON(void);//STM32 mco功能开启 输出时钟给CMOS传感器 sensor.c

unsigned char wr_Sensor_Reg(unsigned char regID, unsigned char regDat);	//sensor.c
unsigned char rd_Sensor_Reg(unsigned char regID, unsigned char *regDat);	//sensor.c

unsigned char Sensor_init(void);	//sensor.c
void Sensor_GPIO_Init(void);	//sensor.c
void Sensor_EXTI_Config(void);	//sensor.c
void Sensor_Interrupts_Config(void);	//sensor.c
void PowerDown(void);
void DMA_init_config(void);
void DCMI_init_config(void);

int Cam_init(void);
// Na pokusy
#define BuffSize		48000

// DMA Stream parameters definitions. You can modify these parameters to select
// a different DMA Stream and/or channel.
// But note that only DMA2 Streams are capable of Memory to Memory transfers.
#define DMA_CameraToRAM_Stream   		DMA2_Stream7
#define DMA_Camera_Channel         		DMA_Channel_1
#define DMA_Camera_STREAM_CLOCK    		RCC_AHB1Periph_DMA2
#define DMA_Camera_STREAM_IRQ      		DMA2_Stream7_IRQn
#define DMA_Camera_IT_TCIF         		DMA_IT_TCIF7
#define DMA_Camera_STREAM_IRQHANDLER    DMA2_Stream7_IRQHandler
#define picture_x 320
#define picture_y 240 
#define DCMI_DR_ADDRESS       0x50050028
__IO uint16_t RAM_Buffer[picture_x*picture_y];

#endif /* _OV7670_H */



