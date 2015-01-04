
#include "fifo.h"


void  FIFO_Set_GPIO_Config(void)
{
  
 GPIO_InitTypeDef GPIO_InitStructure;
  //Enable GPIOF clock 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin =FIFO_RD_BIT|FIFO_WRST_BIT|FIFO_RRST_BIT|FIFO_CS_BIT|FIFO_WE_BIT;                               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  //0x01,< GPIO Output Mode >
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  // 0x00, <Push-Pull mode>
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*GPIO_InitStructure.GPIO_Pin =FIFO_RD_BIT;                               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  //0x01,< GPIO Output Mode >
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  // 0x00, <Push-Pull mode>
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

 // FIFO_RRST : PE0 
  GPIO_InitStructure.GPIO_Pin =FIFO_RRST_BIT;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

// FIFO_CS : PD6 
  GPIO_InitStructure.GPIO_Pin = FIFO_CS_BIT;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // FIFO_WEN : PD3 
  GPIO_InitStructure.GPIO_Pin = FIFO_WE_BIT;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // FIFO_WRST : PB7 
  GPIO_InitStructure.GPIO_Pin = FIFO_WRST_BIT;
  GPIO_Init(GPIOB, &GPIO_InitStructure);*/
}
  

void FIFO_GPIO_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOB clock */

  /*GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//FIFO D[0-7]
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  //input floating mode
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  // 0x00, <Push-Pull mode>
 //GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL; 
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;// Pull-up
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

 GPIO_PinAFConfig(GPIOG, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource15, GPIO_AF_DCMI); //how use input floating*/

  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE); //DCMI 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB |RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);//使能DCMI的GPIO时钟

        GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);                        //DCMI D0
        GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);                        //DCMI D1
        GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);                        //DCMI D2
        GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);                        //DCMI D3
        GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);                        //DCMI D4
        GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);                        //DCMI D5
        GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);                        //DCMI D6
        GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);                        //DCMI D7

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;       
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
        GPIO_Init(GPIOC, &GPIO_InitStructure);        

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;       
        GPIO_Init(GPIOE, &GPIO_InitStructure);               

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;       
        GPIO_Init(GPIOB, &GPIO_InitStructure);         


}
