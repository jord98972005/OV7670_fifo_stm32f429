
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
extern unsigned int  a, bn;
uint16_t CMOS_data_H=0;
uint16_t CMOS_data_L=0;
/*unsigned int  kkk=0,s=0;
uint32_t redtable[256];
uint32_t greentable[256];
uint8_t bluetable[256];
uint32_t bitarray[2400];
uint16_t iluminacion;*/

/*NVIC_InitTypeDef NVIC_InitStructure;
 
#define BufferSize  6400
 unsigned int Buffer[2][BufferSize]={0};

 
  void my_DMA(char a)
 {
    DMA_InitTypeDef    DMA_InitStructure;
   DMA_DeInit(DMA2_Channel5);
  DMA_InitStructure.DMA_PeripheralBaseAddr = 0X6C000000;
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
 }*/
 

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
//  SysTick_Init();

  TM_ILI9341_Init();
  TM_ILI9341_Rotate(TM_ILI9341_Orientation_Landscape_2);

 //Cam_init();
   
  //FIFO_Set_GPIO_Config(); //fifo.c
  //FIFO_GPIO_INPUT();  //fifo.c
  FIFO_CS_L();  //fifo.h
  FIFO_WE_H();  //fifo.h
  
  while(1!=Cam_init());
  
  Sensor_EXTI_Config(); 
  Sensor_Interrupts_Config(); 
  
   //TM_ILI9341_Puts(20, 140, "FIFO set", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
  bn=0;
 /*FIFO reset*/
  FIFO_RRST_L();  //fifo.h
  FIFO_RD_L();  //fifo.h
  FIFO_RD_H();  //fifo.h
  FIFO_RD_L();  //fifo.h
  FIFO_RRST_H();  //fifo.h
  FIFO_RD_H();  //fifo.h

 /* for(a=0;a<76800;a++)
   {
       FIFO_RD_L(); ; //fifo.h
       FIFO_RD_H();   //fifo.h
       FIFO_RD_L(); //fifo.h
       FIFO_RD_H();   //fifo.h
  }*/
 // TM_ILI9341_Puts(20, 160, "FIFO set", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
 
  ////////////////////////////////////////
  while(1)
  {
    //_Bool bitaux;
    //int16_t j;
   // int16_t i;
   // uint16_t red;
    //uint16_t green;
    //uint16_t blue; 

    //if(bn==2)   //vsync==2
    {
        /*set FIFO window 239*319 */
        //
        FIFO_RRST_L(); 
        FIFO_RD_L();
        FIFO_RD_H();
        FIFO_RD_L();
        FIFO_RRST_H();
        FIFO_RD_H();
        //TM_ILI9341_set_fifo_window();
        TM_ILI9341_SetCursorPosition(0, 0, 319, 239);
        TM_ILI9341_SendCommand(ILI9341_GRAM);

//TM_ILI9341_Puts(20, 120, &SCCB_SID_STATE, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);

    for(a=0;a<76800;a++)
        {
    /* for( j = 0; j<1; j++ )
{
for( i = 0; i<1;i++) //two loops that are equal to one loop of 76800 iterations
        {*/
		//TM_ILI9341_SendCommand(ILI9341_GRAM);
                 FIFO_RD_L(); ;
                CMOS_data_H=(GPIOE->IDR>>8);
                
                FIFO_RD_H(); 
                FIFO_RD_L();
                CMOS_data_L=(GPIOE->IDR)&0xff;
               
                FIFO_RD_H();  
                 //TM_ILI9341_SendData(CMOS_data_H);
                 //TM_ILI9341_SendData(CMOS_data_L);

               
                //TM_ILI9341_Puts(0, 0, &CMOS_data, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
                // LCD_WriteRAM(CMOS_data);
                // TM_ILI9341_DrawPixel(a,a,ILI9341_COLOR_RED);
                /* set RGB channel */
               // blue=(CMOS_data &0x001f)<<1;//only blue channel
              //  red=(CMOS_data&0xf800)>>10;//only red channel;//only blue channel
               // green=(CMOS_data&0x07e0)>>5;
             

                //set iluminacion 
             //   iluminacion=red+green+blue; 

              /*if(iluminacion<24)// if ilumination is too low i discard data
              {
                     red=64;
                     green=64;
                    //blue=64;
              }
              else
              {   
                 red=(red<<8)/iluminacion;
                green=(green<<8)/iluminacion;
    //          blue=(blue<<8)/iluminacion;
               }

             bitaux=(redtable[red])&&(greentable[green]);

            //if(((GPIOG->IDR )==0)&&(bitaux))//if i press a button i dump image to usart to the LABView grabberif 

            CMOS_data=ILI9341_COLOR_MAGENTA;      //this is useful if you want to visualize the segmentation pixels are painted blue
            bitarray[j]|=(bitaux<<i);//i create a "boolean image" stored in "bitarray" a variable consisting of 
                        //2400 spaces of 32bit-data, each BIT is each pixel of the segmentation*/
            //LCD_RAM=CMOS_data;
          //  TM_ILI9341_DrawPixel(j,i,red);
            //LCD_SetColorKeying(CMOS_data);
           //TM_ILI9341_write_reg(0x2C, blue);
         }
         bn=0;
       //}
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
	/****************************************
	 *SystemFrequency/1000      1ms中断一次  *
	 *SystemFrequency/100000    10us中断一次 *
	 *SystemFrequency/1000000   1us中断一次  *
	 *****************************************/
   /* if (SysTick_Config(SystemCoreClock / 1000000))  //SysTick end of count event each 10ms 
    { 
        while (1);
    }*/
         while(SysTick_Config(SystemCoreClock/1000000)!=0);    //设置系统节拍时钟为1us中断一次
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


