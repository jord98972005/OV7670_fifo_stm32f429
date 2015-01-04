
/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/

#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"



#define FIFO_CS_BIT         GPIO_Pin_8	// GPIO_Pin_7  //  ((uint16_t)0x0080)       	   Pin 7 selected  stm32f4xx_gpio.h
#define FIFO_WRST_BIT    GPIO_Pin_2   //GPIO_Pin_8  //   ((uint16_t)0x0100) 	   Pin 8 selected 
#define FIFO_RRST_BIT    GPIO_Pin_3	//GPIO_Pin_9 //  ((uint16_t)0x0200)   	   Pin 9 selected 
#define FIFO_RD_BIT         GPIO_Pin_6	//GPIO_Pin_10  // ((uint16_t)0x0400) 		   Pin 10 selected 
#define FIFO_WE_BIT          GPIO_Pin_4	//GPIO_Pin_11  // ((uint16_t)0x0800)  		   Pin 11 selected 


#define FIFO_CS_H()    GPIOA->BSRRH =FIFO_CS_BIT	//stm32f4xx.h
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define FIFO_CS_L()    GPIOA->BSRRL  =FIFO_CS_BIT
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define FIFO_WRST_H()  GPIOA->BSRRH =FIFO_WRST_BIT
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define FIFO_WRST_L()  GPIOA->BSRRL  =FIFO_WRST_BIT
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define FIFO_RRST_H()  GPIOA->BSRRH =FIFO_RRST_BIT
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define FIFO_RRST_L()  GPIOA->BSRRL  =FIFO_RRST_BIT
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define FIFO_RD_H()    GPIOA->BSRRH =FIFO_RD_BIT
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define FIFO_RD_L()    GPIOA->BSRRL  =FIFO_RD_BIT
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define FIFO_WE_H()    GPIOA->BSRRH =FIFO_WE_BIT
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define FIFO_WE_L()    GPIOA->BSRRL  =FIFO_WE_BIT
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


void  FIFO_Set_GPIO_Config(void);
void FIFO_GPIO_INPUT(void);