
/*
wangguanfu@163.com
QQ:21578936
脦麓戮颅鹿媒卤戮脠脣脨铆驴脡陆没脰鹿脠脦潞脦脡脤脪碌脫脙脥戮
http://shop37116146.taobao.com/
*/
/**************************************************************/
#include "stm32f4xx.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include <stdio.h>
/**************************************************************/

#include "main.h"
volatile int32_t dma_handler_counter = 0;
static volatile ErrorStatus HSEStartUpStatus = SUCCESS;
__IO uint32_t TimingDelay;
static volatile uint32_t SELStatus = 0;
extern unsigned int  a, bn,c_data;
unsigned int  kkk=0,s=0;

//NVIC_InitTypeDef NVIC_InitStructure;
 
//#define BufferSize  6400
 //unsigned int Buffer[2][BufferSize]={0};

 /*
  void my_DMA(char a)
 {
    DMA_InitTypeDef    DMA_InitStructure;
   DMA_DeInit(DMA2_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = 0X6C000002;
  if(a==0)DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Buffer[0][0];    
   if(a==1)DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Buffer[1][0];  
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = BufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
  DMA_Init(DMA2_Channel5, &DMA_InitStructure);

  DMA_Cmd(DMA2_Channel5, ENABLE);
  while(!DMA_GetFlagStatus(DMA2_FLAG_TC5));
  DMA_ClearFlag(DMA2_FLAG_TC5);
 }
 */

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
 
 
int main(void)
{
  /*Intialize the STM32 SYSTEM_Init */
  SystemInit();//main.c
  LCD_firm_init();

  //LCD_SetDisplayWindow(0,319,320,240);
   //Set LCDBackground Layer  
 /* LCD_write_english_string(5,66+16,"CMOS Sensor Init.....",0Xf800,0X0000);  //lcd.c
  LCD_write_english_string(5,66,"GUANFU_WANG 2011-04015",0Xf800,0X0000);  //lcd.c*/
  FIFO_Set_GPIO_Config(); //fifo.c
  FIFO_GPIO_INPUT();  //fifo.c
  FIFO_CS_L();  //fifo.h
  FIFO_WE_H();  //fifo.h
  //while(0!=Sensor_init());//鲁玫脢录禄炉CMOS Sensor sensor.c
   
 TM_ILI9341_Puts(65, 130, "NCKU embedded 2015", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
  //LCD_write_english_string(5,66+16,"CMOS Sensor Init...ok",0Xf800,0X0000);  //lcd.c
  Sensor_EXTI_Config(); //VSYNC 脰脨露脧 Sensor.c
  Sensor_Interrupts_Config(); //VSYNC 脰脨露脧 Sensor.c
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
         /*LCD_WriteReg(0x0020,239);//GRAM水平起始位置 lcd.c
        LCD_WriteReg(0x0021,319);      
         LCD_WriteReg(0x0050,0x00);//水平 GRAM起始位置
        LCD_WriteReg(0x0051,239);//水平GRAM终止位置
        LCD_WriteReg(0x0052,0x00);//垂直GRAM起始位置
        LCD_WriteReg(0x0053,319);//垂直GRAM终止位置 
        LCD_WriteReg(0x0003,0x1008);
        LCD_WriteRAM_Prepare();  Prepare to write GRAM  lcd.c */
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
     }
}


/*******************************************************************************
* Function Name  : SYSTEM_Init
* Description    : Intializes the STM32 SYSTEM_Init.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SYSTEM_Init(void)
{
  /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration -----------------------------*/  
  /* RCC system reset(for debug purpose) */
  RCC_DeInit(); //stm32f4xx_rcc.c

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);  //stm32f4xx_rcc.c


  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); //stm32f4xx_rcc.c

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(ENABLE); //stm32f4xx_flash.c

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);  //stm32f4xx_flash.c
    
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  //stm32f4xx_rcc.c
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);   //stm32f4xx_rcc.c
 
    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2); //stm32f4xx_rcc.c
 
    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE, 8,192,2,4); //stm32f4xx_rcc.c
 
    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE); //stm32f4xx_rcc.c
 
    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)  //stm32f4xx_rcc.c
    {
    }
 
    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  //stm32f4xx_rcc.c
 
    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)  //stm32f4xx_rcc.c
    {
    }
  }

  /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG and AFIO clocks */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |RCC_AHB1Periph_GPIOC 
         | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG 
          , ENABLE); //stm32f4xx_rcc.c
  
  /* DMA1 and DMA2 clock enable */
  //RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 | RCC_AHBPeriph_DMA2, ENABLE);
    
  SysTick_Init(); //main.c

/*------------------- Drivers Initialization -------------------------------*/
  /* Initialize the LCD */
  //LCD_Init(); //lcd.c

  /* Clear the LCD */ 
  //LCD_Clear(0x0); //lcd.c
}


/*******************************************************************************
* Function Name  : SysTick_Init
* Description    : Configure a SysTick Base time to 10 ms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void SysTick_Init(void)
{
    if (SysTick_Config(SystemCoreClock / 100))  //SysTick end of count event each 10ms 
    { 
        while (1); //鍒濆鍖栧け璐
    }
}


/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length (time base 10 ms).
* Output         : None
* Return         : None
*******************************************************************************/
void Delay(__IO uint32_t nTime)
{ 
    TimingDelay = nTime;
    
    while(TimingDelay != 0);
}

/*******************************************************************************
* Function Name  : Decrement_TimingDelay
* Description    : Decrements the TimingDelay variable.
* Input          : None
* Output         : TimingDelay
* Return         : None
*******************************************************************************/
void Decrement_TimingDelay(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}




/*******************************************************************************
* Function Name  : Set_SELStatus
* Description    : Sets the SELStatus variable.
* Input          : None
* Output         : SELStatus
* Return         : None
*******************************************************************************/
void Set_SELStatus(void)
{
  SELStatus = 1;
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description:    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/*void LCD_all_init(void){
  Initialize the LCD 
  LCD_Init();
LCD_LayerInit();
  // Enablethe LTDC 
LTDC_Cmd(ENABLE); 
  // Set LCDBackground Layer  
LCD_SetLayer(LCD_BACKGROUND_LAYER);
  // Clearthe Background Layer 
LCD_Clear(LCD_COLOR_WHITE);  
  //Configure the transparency for background 
LCD_SetTransparency(255);
         LCD_SetTextColor(LCD_COLOR_BLUE);
LCD_DrawFullCircle(85, 55, 52);
         LCD_SetTextColor(LCD_COLOR_RED);
LCD_DrawFullCircle(85, 160, 52);
         LCD_SetTextColor(LCD_COLOR_YELLOW);
LCD_DrawFullCircle(85, 265, 52);
  // Set LCDForeground Layer  
LCD_SetLayer(LCD_FOREGROUND_LAYER);
  //Configure the transparency for foreground 
LCD_SetTransparency(127);  
  // Clearthe Foreground Layer 
LCD_Clear(LCD_COLOR_WHITE);
         LCD_SetTextColor(LCD_COLOR_RED);
LCD_DrawFullCircle(155, 55, 52);
         LCD_SetTextColor(LCD_COLOR_YELLOW);
  LCD_DrawFullCircle(155, 160, 52);
         LCD_SetTextColor(LCD_COLOR_BLUE);
LCD_DrawFullCircle(155, 265, 52);
}*/

void LCD_firm_init(void)
{
        //Initialize ILI9341
    TM_ILI9341_Init();
    //Rotate LCD for 90 degrees
    TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);
    
    //Put string with black foreground color and blue background with 11x18px font
   TM_ILI9341_Puts(65, 130, "NCKU embedded 2015", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);

   
    
    while (1) {
        
    }

}
