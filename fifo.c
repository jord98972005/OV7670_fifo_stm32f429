
#include "fifo.h"


void  FIFO_Set_GPIO_Config(void)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable GPIOF clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  GPIO_InitStructure.GPIO_Pin =FIFO_RD_BIT|FIFO_WRST_BIT|FIFO_RRST_BIT|FIFO_CS_BIT|FIFO_WE_BIT;                               
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  //0x01,< GPIO Output Mode >
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  // 0x00, <Push-Pull mode>
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
  

  
}

void FIFO_GPIO_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOB clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//FIFO D[0-7]
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  //input floating mode
  // GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  // 0x00, <Push-Pull mode>
 GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;  // GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;// Pull-up
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /*GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_DCMI);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_DCMI); how use input floating*/
}
