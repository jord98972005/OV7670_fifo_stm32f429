#ifndef _sccb_H
#define _sccb_H

#include "stm32f4xx_gpio.h"


#define SCCBID_7670                           0x42                                                 //OV7670的ID

#define SCCB_SCL_BIT     GPIO_Pin_2	  //  ((uint16_t)0x0004)  Pin 2 selected 
#define SCCB_SDA_BIT    GPIO_Pin_3	 //GPIO_Pin_3		 //   (uint16_t)0x0008)   Pin 3 selected 


#define SCL_H	GPIO_SetBits(GPIOE,SCCB_SCL_BIT)		//stm32f4xx.h
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define SCL_L     GPIO_ResetBits(GPIOE,SCCB_SCL_BIT)
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */


#define SDA_H       GPIO_SetBits(GPIOE,SCCB_SDA_BIT)
/*!< GPIO port bit set/reset high register, Address offset: 0x1A      */
#define SDA_L      GPIO_ResetBits(GPIOE,SCCB_SDA_BIT)
  /*!< GPIO port bit set/reset low register,  Address offset: 0x18      */

//#define SCCB_SDA_IN      SCCB_SID_GPIO_INPUT();
//#define SCCB_SDA_OUT     SCCB_SID_GPIO_OUTPUT();

#define SDA_read	 GPIOE->IDR&GPIO_Pin_3           //GPIO_Pin_3 =0x08
#define SCL_read	 GPIOE->IDR&GPIO_Pin_2           //GPIO_Pin_3 =0x08
 /*!< GPIO port input data register,         Address offset: 0x10      */


////////////////////////////////////////////
/*void SCCB_GPIO_Config(void);

void SCCB_SID_GPIO_OUTPUT(void);
void SCCB_SID_GPIO_INPUT(void);
//void startSCCB(void);
void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char SCCBwriteByte(unsigned char m_data);
unsigned char SCCBreadByte(void);*/
void I2C_Configuration(void);
int I2C_WriteByte( uint16_t WriteAddress , uint8_t SendByte , uint8_t DeviceAddress);
int I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress);

/*************************************************roman joe*/

/*#define i2c_dev I2C2
 void Delay(uint32_t volatile DelayTime_uS);
 void I2C_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
 void I2C_write(I2C_TypeDef* I2Cx, uint8_t data);
 uint8_t I2C_read_ack(I2C_TypeDef* I2Cx);
 uint8_t I2C_read_nack(I2C_TypeDef* I2Cx);
 void I2C_stop(I2C_TypeDef* I2Cx);
 uint8_t I2C_writereg(uint32_t reg, uint32_t data);
 uint8_t I2C_readreg(uint32_t reg);*/


/*************************************************roman joe*/



