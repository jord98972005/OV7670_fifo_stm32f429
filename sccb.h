#ifndef _sccb_H
#define _sccb_H

#include "stm32f4xx_gpio.h"

#define SCCB_SIC_BIT     GPIO_Pin_2		  //  ((uint16_t)0x0004)  Pin 2 selected 
#define SCCB_SID_BIT    GPIO_Pin_4	 //GPIO_Pin_3		 //   (uint16_t)0x0008)   Pin 3 selected 


#define SCCB_SIC_H()     GPIOD->BSRRH = SCCB_SIC_BIT;//stm32f4xx.h
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define SCCB_SIC_L()     GPIOD->BSRRL =  SCCB_SIC_BIT;
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define SCCB_SID_H()     GPIOD->BSRRH = SCCB_SID_BIT;
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define SCCB_SID_L()     GPIOD->BSRRL =  SCCB_SID_BIT;
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define SCCB_SID_IN      SCCB_SID_GPIO_INPUT();
#define SCCB_SID_OUT     SCCB_SID_GPIO_OUTPUT();



#define SCCB_SID_STATE	 GPIOD->IDR&0x10
 /*!< GPIO port input data register,         Address offset: 0x10      */


///////////////////////////////////////////
void SCCB_GPIO_Config(void);
void SCCB_SID_GPIO_OUTPUT(void);
void SCCB_SID_GPIO_INPUT(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);


#endif /* _IIC_H */


