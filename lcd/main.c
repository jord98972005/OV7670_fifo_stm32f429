#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_dcmi.h"
#include "stm32f4xx_dma.h"
#include "i2c_ops.h"
#include "ov7670.h"
#include "stm32f4xx.h"
#include "misc.h"

/**************************************************************/
#include "stm32f4xx_spi.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include <stdio.h>
/**************************************************************/
volatile int32_t dma_handler_counter = 0;

uint32_t camera_frame[10]; // for 320*240 resolution

void camera_init(void)
{
    RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* Clocking of  GPIOB is enabled in i2c_init function */

    /* PA4 - HSYNC
       PA6 - PIXCLK
       PB7 - DCMI_VSYNC
       PC6 - DCMI_D0
       PC7 - DCMI_D1
       PC8 - DCMI_D2
       PC9 - DCMI_D3
       PC11 - DCMI_D4
       PB6 - DCMI_D5
       PB8 - DCMI_D6
       PB9 - DCMI_D7

       PB10 - I2C_SCL
       PB11 - I2C_SDA
     */

    /* set  gpio pins to provide DCMI access PA4    PA6*/
    GPIO_InitTypeDef dcmi_gpioa_init;
    dcmi_gpioa_init.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
    dcmi_gpioa_init.GPIO_Mode = GPIO_Mode_AF;
    dcmi_gpioa_init.GPIO_OType = GPIO_OType_PP;
    dcmi_gpioa_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    dcmi_gpioa_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &dcmi_gpioa_init);

    GPIO_InitTypeDef dcmi_gpiob_init;   //PB6   PB7     PB8     PB9
    dcmi_gpiob_init.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
    dcmi_gpiob_init.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &dcmi_gpiob_init);

    GPIO_InitTypeDef dcmi_gpioc_init;   //PC6   PC7     PC8     PC9     PC11
    dcmi_gpioc_init.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11;
    dcmi_gpioc_init.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOC, &dcmi_gpioc_init);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_DCMI);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_DCMI);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_DCMI);
    /* i2c interface init */
    GPIO_InitTypeDef i2c_gpio_init;

    i2c_gpio_init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    i2c_gpio_init.GPIO_Mode = GPIO_Mode_AF;
    i2c_gpio_init.GPIO_OType = GPIO_OType_OD;
    i2c_gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    i2c_gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOB, &i2c_gpio_init);

    GPIO_PinAFConfig (GPIOB, GPIO_PinSource10, GPIO_AF_I2C2);    // I2C2_SCL
    GPIO_PinAFConfig (GPIOB, GPIO_PinSource11, GPIO_AF_I2C2);    // I2C2_SDA
    /* gpio init to provide mco frequency */
    GPIO_InitTypeDef mco_Init;              //PA8 ??

    mco_Init.GPIO_Pin = GPIO_Pin_8;
    mco_Init.GPIO_Mode = GPIO_Mode_AF;
    mco_Init.GPIO_Speed = GPIO_Speed_100MHz;
    mco_Init.GPIO_OType = GPIO_OType_PP;

    GPIO_Init(GPIOA, &mco_Init);

    /*****************************************************************/

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* PB4 = TIM3_CH1      
     * PB5 = TIM3_CH2 */
    GPIO_InitTypeDef tim3_gpio_init;
    //GPIO_StructInit(&tim_gpio_init);
    tim3_gpio_init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
    tim3_gpio_init.GPIO_OType = GPIO_OType_PP;
    tim3_gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    tim3_gpio_init.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOB, &tim3_gpio_init);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);

    /* PA2 = TIM9_CH1
     * PA3 = TIM9_CH2 */
    GPIO_InitTypeDef tim9_gpio_init;
    //GPIO_StructInit(&tim_gpio_init);
    tim9_gpio_init.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    tim9_gpio_init.GPIO_OType = GPIO_OType_PP;
    tim9_gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    tim9_gpio_init.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &tim9_gpio_init);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);

//================================ TIM3 triggered input =============
	/* configure TIM3 master mode to use OC1REF signal as trigger output */
	TIM3->CR2 |= (TIM_CR2_MMS_2);
	TIM3->CR2 &= ~(TIM_CR2_MMS_1 | TIM_CR2_MMS_0);
	/* configure OC1REF to active level on compare match */
	TIM3->CCMR1 |= (TIM_CCMR1_OC1M_0);
	TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	/* configure compare register 1 to match on 20*tline  */
	TIM3->CCR1 |= 20;
	/* set master tim prescaler to match 1*tline = 1568, need to sub 1 for PSC */
	TIM3->PSC |= (1567 * 2);
	/* configure autoreload value and enable it */
	TIM3->ARR &= 0;
	TIM3->ARR |= 508;
	TIM3->CR1 |= TIM_CR1_ARPE;
	/* configure master to reset on rising edge of input trigger SMS == 100 */
	TIM3->SMCR |= TIM_SMCR_SMS_2;
	TIM3->SMCR &= ~(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0);
	/* configure master to use TI2FP2 as input trigger TS == 110 */
	TIM3->SMCR |= (TIM_SMCR_TS_2 | TIM_SMCR_TS_1);
	TIM3->SMCR &= ~(TIM_SMCR_TS_0);

	/* enable delay on trigger input for sync between master and slave */
	TIM3->SMCR |= TIM_SMCR_MSM;

	/* enable output to  on compare on channel 1 */
	TIM3->CCER |= TIM_CCER_CC1E;

	/* test output polarity low */
	TIM3->CCER &= ~(TIM_CCER_CC1P);

	/* enable interrupt on compare channel 1 */
	TIM3->DIER |= TIM_DIER_CC1IE;
//============================== END PWM MODE TEST ==================

//================================ TIM9 triggered input =============
	/* configure input reset source 1 - ITR1, TS == 001 */
	TIM9->SMCR |= TIM_SMCR_TS_0;
	TIM9->SMCR &= ~(TIM_SMCR_TS_1 | TIM_SMCR_TS_2);

	/* configure TIM9 in reset mode SMS == 100 */
	TIM9->SMCR &= ~(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0);
	TIM9->SMCR |= (TIM_SMCR_SMS_2);

//	/* configure TIM9 in gated mode SMS == 101 */
//	TIM9->SMCR &= ~TIM_SMCR_SMS_1;
//	TIM9->SMCR |= (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_0);

//	/* configure TIM9 in trigger mode SMS == 101 */
//	TIM9->SMCR &= ~TIM_SMCR_SMS_0;
//	TIM9->SMCR |= (TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1);


//================================ PWM mode 1 on output ==============
	TIM9->PSC |= 1;

	TIM9->ARR &= 0;
	TIM9->ARR |= 1567;
	/* configure timer to enable auto-reload
	 * and choose direction downcount */
	TIM9->CR1 |= TIM_CR1_ARPE;
	/* provide capture value for channel 1 */
	TIM9->CCR1 |= 1279;

	TIM9->CCMR1 &= ~(TIM_CCMR1_OC1M_0);
	TIM9->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);


//	/* set force inactive mode on initialization */
//	TIM9->CCMR1 &= ~(TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0);
//	TIM9->CCMR1 |= TIM_CCMR1_OC1M_2;


	/* enable fast output change on compare - just in pwm mode 1 or 2*/
	TIM9->CCMR1 |= TIM_CCMR1_OC1FE;
	/* enable preload register */
	TIM9->CCMR1 |= TIM_CCMR1_OC1PE;

	/* select activity high polarity */
	TIM9->CCER &= ~(TIM_CCER_CC1P);

	/* enable the output */
	TIM9->CCER |= TIM_CCER_CC1E;
	/* enable interrupt event on compare channel 1 */
	TIM9->EGR |= TIM_EGR_CC1G | TIM_EGR_UG;
//=============================== END PWM MODE TEST ==================
	/* enable TIM9 to count */
	//TIM9->CR1 |= TIM_CR1_CEN;

// ================================= COMPARE MODE ==================
//	TIM9->ARR &= 0;
//	TIM9->ARR |= 1280;
//	/* configure timer to enable auto-reload
//	 * and choose direction downcount */
//	TIM9->CR1 |= TIM_CR1_ARPE | TIM_CR1_DIR;
//	/* provide capture value for channel 1 */
//	TIM9->CCR1 |= 1;
//	/* choose OC1 to toggling on compare */
//	TIM9->CCMR1 &= ~(TIM_CCMR1_OC1M_2);
//	TIM9->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0);
//	/* disable preload register */
//	TIM9->CCMR1 &= ~(TIM_CCMR1_OC1PE);
//	/* select activity high polarity */
//	TIM9->CCER &= ~(TIM_CCER_CC1P);
//	/* enable the output */
//	TIM9->CCER |= TIM_CCER_CC1E;
//	/* enable interrupt event on compare channel 1 */
//	TIM9->DIER |= TIM_DIER_CC1IE;
// =========================================================
	NVIC_InitTypeDef tim3_nvic_init;
	tim3_nvic_init.NVIC_IRQChannel = TIM3_IRQn;
	tim3_nvic_init.NVIC_IRQChannelCmd = DISABLE;
	tim3_nvic_init.NVIC_IRQChannelPreemptionPriority = 1;
	tim3_nvic_init.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&tim3_nvic_init);

    /*****************************************************************/

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);

    /* dcmi interface init */
    DCMI_InitTypeDef camera_init;

    camera_init.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
    camera_init.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
    camera_init.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
    camera_init.DCMI_HSPolarity = DCMI_HSPolarity_High;
    camera_init.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
    camera_init.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
    camera_init.DCMI_VSPolarity = DCMI_VSPolarity_High;

    DCMI_StructInit(&camera_init);
    // enable DCMI interface
    DCMI_Cmd(ENABLE);

    NVIC_InitTypeDef camera_irq;
    camera_irq.NVIC_IRQChannel = DCMI_IRQn;
    camera_irq.NVIC_IRQChannelPreemptionPriority = 0;
    camera_irq.NVIC_IRQChannelSubPriority = 1;
    camera_irq.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&camera_irq);

    DCMI_ITConfig(DCMI_IT_ERR | DCMI_IT_FRAME | DCMI_IT_LINE |
                  DCMI_IT_OVF | DCMI_IT_VSYNC, ENABLE);

    I2C_InitTypeDef i2c_init;

    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    i2c_init.I2C_ClockSpeed = 100000;
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_OwnAddress1 = 21;

    I2C_Init(I2C2, &i2c_init);
    // enable I2C interface
    I2C_Cmd(I2C2, ENABLE);
}

void TIM3_IRQHandler(void)
{
	static volatile uint32_t flag = 0;

	if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
	{
		if(flag == 0)
		{
			TIM3->CCR1 &= 0;
			TIM3->CCR1 |= 499;

			/* set inactive level on TRGO on compare match OC1M == 010*/
			TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_2);
			TIM3->CCMR1 |= TIM_CCMR1_OC1M_1;

//			TIM9->CCER |= TIM_CCER_CC1E;

//			/* choose OC1 to work in PWM generation mode 1 */
//			TIM9->CCMR1 &= ~(TIM_CCMR1_OC1M_0);
//			TIM9->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
//
			TIM9->CR1 |= TIM_CR1_CEN;

			flag = 1;
		}
		else
		{
			TIM3->CCR1 &= 0;
			TIM3->CCR1 |= 20;
			/* set active level on TRGO on compare match OC1M == 010*/
			TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
			TIM3->CCMR1 |= TIM_CCMR1_OC1M_0;

//			TIM9->CCER &= ~TIM_CCER_CC1E;

			TIM9->CR1 &= ~TIM_CR1_CEN;

//			// DEBUG force inactive
//			TIM9->CCMR1 &= ~(TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_0);
//			TIM9->CCMR1 |= TIM_CCMR1_OC1M_2;

			flag = 0;
		}
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
	}
}


//void i2c_init(void)
//{
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
//
//    I2C_InitTypeDef i2c_init;
//
//    i2c_init.I2C_Ack = I2C_Ack_Enable;
//    i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//    i2c_init.I2C_ClockSpeed = 100000;
//    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;
//    i2c_init.I2C_Mode = I2C_Mode_I2C;
//    i2c_init.I2C_OwnAddress1 = 21;
//
//    I2C_Init(I2C2, &i2c_init);
//    // enable I2C interface
//    I2C_Cmd(I2C2, ENABLE);
//}

void dma_init(void)
{
    DMA_DeInit(DMA2_Stream1);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    DMA_InitTypeDef dma_init;

    dma_init.DMA_Channel = DMA_Channel_1;
    dma_init.DMA_PeripheralBaseAddr = (uint32_t) &(DCMI->DR);
    dma_init.DMA_Memory0BaseAddr = (uint32_t) camera_frame;
    dma_init.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma_init.DMA_BufferSize = 10;
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    dma_init.DMA_Mode = DMA_Mode_Normal;
    dma_init.DMA_Priority = DMA_Priority_High;
    dma_init.DMA_FIFOMode = DMA_FIFOMode_Enable;
    dma_init.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    dma_init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_init.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

    DMA_Init(DMA2_Stream1, &dma_init);

    DMA_ITConfig(DMA2_Stream1, DMA_IT_TC | DMA_IT_FE, ENABLE);

    NVIC_InitTypeDef dma_stream1_irq;

    dma_stream1_irq.NVIC_IRQChannel = DMA2_Stream1_IRQn;
    dma_stream1_irq.NVIC_IRQChannelPreemptionPriority = 0;
    dma_stream1_irq.NVIC_IRQChannelSubPriority = 0;
    dma_stream1_irq.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&dma_stream1_irq);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

void DMA2_Stream1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1) != RESET)
    {
        dma_handler_counter++;
        DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);
    }
}

void LCD_init(void)
{
        //Initialize ILI9341
    TM_ILI9341_Init();
    //Rotate LCD for 90 degrees
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
    
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(65, 130, "MLN why you so Low Can", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
    //Put string with black foreground color and blue background with 11x18px font
    TM_ILI9341_Puts(60, 150, "AQ's LOL is Poor", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE2);
    //Put string with black foreground color and red background with 11x18px font
    TM_ILI9341_Puts(60, 170, "NN is korean handsome man", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
    
    while (1) {
        
    }

}





int main(void)
{
    uint8_t c = 0;
    SystemInit();

//Initialize system
    SystemInit();
    LCD_init();
  /* Intialize the STM32 SYSTEM_Init *
  LCD_write_english_string(5,66+16,"CMOS Sensor Init.....",0Xf800,0X0000);  //lcd.c
  LCD_write_english_string(5,66,"GUANFU_WANG 2011-04015",0Xf800,0X0000);  //lcd.c
  //kkk=LCD_ReadID();
  FIFO_Set_GPIO_Config(); //fifo.c
  FIFO_GPIO_INPUT();  //fifo.c
  FIFO_CS_L();  //fifo.h
  FIFO_WE_H();  //fifo.h
  while(1!=Sensor_init());//初始化CMOS Sensor sensor.c
  LCD_write_english_string(5,66+16,"CMOS Sensor Init...ok",0Xf800,0X0000);  //lcd.c
  Sensor_EXTI_Config(); //VSYNC 中断 Sensor.c
  Sensor_Interrupts_Config(); //VSYNC 中断 Sensor.c
  bn=0;
 ////////////////////////////////////////
  FIFO_RRST_L();  //fifo.h
  FIFO_RD_L();  //fifo.h
  FIFO_RD_H();  //fifo.h
  FIFO_RD_L();  //fifo.h
  FIFO_RRST_H();  //fifo.h
  FIFO_RD_H();  //fifo.h
  for(a=0;a<76800;a++)
   {
       FIFO_RD_L(); ; //fifo.h
       FIFO_RD_H();   //fifo.h
       FIFO_RD_L(); //fifo.h
       FIFO_RD_H();   //fifo.h
  }
  ////////////////////////////////////////
  while(1)
  {
    if(bn==2)
    {
        LCD_WriteReg(0x0020,239);//GRAM水平起始位置 lcd.c
        LCD_WriteReg(0x0021,319);      
         LCD_WriteReg(0x0050,0x00);//水平 GRAM起始位置
        LCD_WriteReg(0x0051,239);//水平GRAM终止位置
        LCD_WriteReg(0x0052,0x00);//垂直GRAM起始位置
        LCD_WriteReg(0x0053,319);//垂直GRAM终止位置 
        LCD_WriteReg(0x0003,0x1008);
        LCD_WriteRAM_Prepare(); // Prepare to write GRAM  lcd.c 
        FIFO_RRST_L(); 
        FIFO_RD_L();
        FIFO_RD_H();
        FIFO_RD_L();
        FIFO_RRST_H();
        FIFO_RD_H();
        for(a=0;a<76800;a++)
        {

             FIFO_RD_L(); ;
             c_data=GPIOB->IDR&0xff00;//读高位
             FIFO_RD_H(); 
             FIFO_RD_L();
             c_data|=(GPIOB->IDR>>8)&0x00ff;//读低位
             FIFO_RD_H();  
            // LCD_WriteRAM(c_data);//写RGB数据到TFT GRAM
             LCD_RAM=c_data;
          
         }
         bn=0;
       }
     }*/
     

    RCC_APB2PeriphClockCmd (RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    GPIO_InitTypeDef GPIOD_Init;

    GPIOD_Init.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIOD_Init.GPIO_Mode = GPIO_Mode_OUT;
    GPIOD_Init.GPIO_OType = GPIO_OType_PP;
    GPIOD_Init.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_Init(GPIOD, &GPIOD_Init);
    camera_init();
//    Delay(1000);
    //i2c_init();
    //camera_init();
    //dma_init();
    c = I2C_readreg(0x0a);
    NVIC_EnableIRQ(TIM3_IRQn);

//    TIM9->CR1 |= TIM_CR1_CEN;
    TIM3->CR1 |= TIM_CR1_CEN;

    if(c == 0x76)
    {
        ov7670_init();
        GPIO_SetBits(GPIOD, GPIO_Pin_13);
    }

//    DMA_Cmd(DMA2_Stream2, ENABLE);

    while(1)
    {
        if(dma_handler_counter == 10)
            GPIO_SetBits(GPIOD, GPIO_Pin_15);
    }


    return 0;
}
