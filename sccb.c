/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/

#include "sccb.h"
#include "delay.h"
#include "tm_stm32f4_ili9341.h"

/*
-----------------------------------------------
   功能: 初始化模拟SCCB接口
   参数: 无
 返回值: 无
-----------------------------------------------
*/
/*void SCCB_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  // Configure I2C2 pins: PB10->SCL and PB11->SDA 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SCL_BIT|SCCB_SDA_BIT; //SCL:PE2    SDA:PE3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void SCCB_SID_GPIO_OUTPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   // Enable GPIOD  clock 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SDA_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void SCCB_SID_GPIO_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   //Enable GPIOD  clock 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  //input mode
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  //上拉 若无外部上拉电阻 必须内部有上拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}*/

/*
-----------------------------------------------
   功能: start命令,SCCB的起始信号
   参数: 无
 返回值: 无
-----------------------------------------------
*/
//void startSCCB(void)
/*unsigned char start SCCB(void)
{
    SCCB_SID_H();     //数据线高电平
    delay_us(50);

    SCCB_SIC_H();	   //在时钟线高的时候数据线由高至低
    delay_us(50);
 
    SCCB_SID_L();
    delay_us(50);

    SCCB_SIC_L();	 //数据线恢复低电平，单操作函数必要
    delay_us(50);

 return SCCB_STATE_ACK;                //SUCCESS;
}*/

/*-----------------------------------------------
   功能: stop命令,SCCB的停止信号
   参数: 无
 返回值: 无
-----------------------------------------------*/

/*void stopSCCB(void)
{
    SCCB_SID_L();
    delay_us(50);
 
    SCCB_SIC_H();	
    delay_us(50);
  

    SCCB_SID_H();	
    delay_us(50);
   
}*/

/*
-----------------------------------------------
   功能: noAck,用于连续读取中的最后一个结束周期
   参数: 无
 返回值: 无
-----------------------------------------------
*/
/*void noAck(void)
{
	
	SCCB_SID_H();	
	delay_us(50);
	
	SCCB_SIC_H();	
	delay_us(50);
	
	SCCB_SIC_L();	
	delay_us(50);
	
	SCCB_SID_L();	
	delay_us(50);

}*/

/*
-----------------------------------------------
   功能: 写入一个字节的数据到SCCB
   参数: 写入数据
 返回值: 发送成功返回1，发送失败返回0
-----------------------------------------------
*/
/*unsigned char SCCBwriteByte(unsigned char m_data)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) //循环8次发送数据
	{
		if((m_data<<j)&0x80)
		{
			SCCB_SID_H();	
		}
		else
		{
			SCCB_SID_L();	
		}
		delay_us(50);
		SCCB_SIC_H();	
		delay_us(50);
		SCCB_SIC_L();	
		delay_us(50);

	}
	delay_us(10);
	SCCB_SID_IN;//设置SDA为输入
	delay_us(50);
	SCCB_SIC_H();	
	delay_us(10);
	if(SCCB_SID_STATE){tem=0;}   //SDA=1发送失败，返回0}
	else {tem=1;}   //SDA=0发送成功，返回1
	SCCB_SIC_L();	
	delay_us(50);	
        SCCB_SID_OUT;//设置SDA为输出

	return (tem);  
}
*/
/*
-----------------------------------------------
   功能: 一个字节数据读取并且返回
   参数: 无
 返回值: 读取到的数据
-----------------------------------------------
*/
/*unsigned char SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SCCB_SID_IN;//设置SDA为输入
	delay_us(50);
	for(j=8;j>0;j--) //循环8次接收数据
	{		     
		delay_us(50);
		SCCB_SIC_H();
		delay_us(50);
		read=read<<1;
		if(SCCB_SID_STATE) 
		{
			read=read+1;
		}
		SCCB_SIC_L();
		delay_us(50);
	}	
        SCCB_SID_OUT;//设置SDA为输出
	return(read);
}*/

/*******************************************************************************
* Function Name  : I2C_Configuration
* Description    : EEPROM管脚配置
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
void I2C_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  // Configure I2C2 pins: PB10->SCL and PB11->SDA 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SCL_BIT|SCCB_SDA_BIT; //SCL:PE2    SDA:PE3
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  //GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

/*SCL_H;
delay_us(10);
SDA_H;
delay_us(5);*/

}

/*******************************************************************************
* Function Name  : I2C_delay
* Description    : 延迟时间
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static void I2C_delay(void)
{ 
//   uint8_t i = 250; /* 这里可以优化速度 */
//   while(i) 
//   { 
//     i--; 
//   } 
delay_us(500); 
}

/*******************************************************************************
* Function Name  : I2C_Start
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static int I2C_Start(void)
{
	I2C_Configuration();
  SDA_H;
  SCL_H;
  
  I2C_delay();
  if(!(SDA_read))return DISABLE;  /* SDA线为低电平则总线忙,退出 */

  SDA_L;
  I2C_delay();
  if(SDA_read) return DISABLE;  /* SDA线为高电平则总线出错,退出 */
  SDA_L;
  I2C_delay();

  return ENABLE;
}

/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static void I2C_Stop(void)
{
  SCL_L;
  I2C_delay();
  SDA_L;
  I2C_delay();
  SCL_H;
  I2C_delay();
  SDA_H;
  I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static void I2C_Ack(void)
{ 
  SCL_L;
  I2C_delay();
  SDA_L;
  I2C_delay();
  SCL_H;
  I2C_delay();
  SCL_L;
  I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : None
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static void I2C_NoAck(void)
{ 
  SCL_L;
  I2C_delay();
  SDA_H;
  I2C_delay();
  SCL_H;
  I2C_delay();
  SCL_L;
  I2C_delay();
}

/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : None
* Input          : None
* Output         : None
* Return         : 返回为:=1有ACK,=0无ACK
* Attention    : None
*******************************************************************************/
static int I2C_WaitAck(void)  
{
  SCL_L;
  I2C_delay();
  SDA_H;      
  I2C_delay();
  SCL_H;
  I2C_delay();
  if(SDA_read)
  {
      SCL_L;
      TM_ILI9341_Puts(20, 60, "wait ack disable", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
      return DISABLE;
  }
  SCL_L;
  return ENABLE;
}

 /*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : 数据从高位到低位
* Input          : - SendByte: 发送的数据
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static void I2C_SendByte(uint8_t SendByte) 
{
    uint8_t i=8;
    // Write data bit by bit on SCCB/I2C
    while(i--)
    {
        SCL_L;
        I2C_delay();
      if((SendByte&0x80)==0x80)	// If bit in Data is high, write high on SCCB/I2C
      {
        SDA_H;  
      }
      else 
      {
        SDA_L;
       }   
        SendByte<<=1;	// Rotate Data for write next bit
        I2C_delay();
    SCL_H;
        I2C_delay();
    }
    SCL_L;
    I2C_delay();
}


/*******************************************************************************
* Function Name  : I2C_ReceiveByte
* Description    : 数据从高位到低位
* Input          : None
* Output         : None
* Return         : I2C总线返回的数据
* Attention    : None
*******************************************************************************/
static int I2C_ReceiveByte(void)  
{ 
    uint8_t i=8;
    uint8_t ReceiveByte=0;

    SDA_H;        
    while(i--)
    {
      ReceiveByte<<=1;      
      SCL_L;
      I2C_delay();
    SCL_H;
      I2C_delay();  
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
    }
    SCL_L;
    return ReceiveByte;
}

/*******************************************************************************
* Function Name  : I2C_WriteByte
* Description    : 写一字节数据
* Input          : - WriteAddress: 待写入地址
*                - SendByte: 待写入数据
*                  - DeviceAddress: 器件类型
* Output         : None
* Return         : 返回为:=1成功写入,=0失败
* Attention    : None
*******************************************************************************/           
int I2C_WriteByte( uint16_t WriteAddress , uint8_t SendByte , uint8_t DeviceAddress)
{   
    if(!I2C_Start()){
      return DISABLE;
    }
    I2C_SendByte( DeviceAddress );                    /* 器件地址 */
    if(!I2C_WaitAck()){
    	I2C_Stop(); 
    	TM_ILI9341_Puts(20, 100, "device disable", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
    	return DISABLE;}
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* 设置低起始地址 */      
    I2C_WaitAck();  
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
  /* 注意：因为这里要等待EEPROM写完，可以采用查询或延时方式(10ms) */
    /* Systick_Delay_1ms(10); */
    return ENABLE;
}                  

/*******************************************************************************
* Function Name  : I2C_ReadByte
* Description    : 读取一串数据
* Input          : - pBuffer: 存放读出数据
*                - length: 待读出长度
*                  - ReadAddress: 待读出地址
*                  - DeviceAddress: 器件类型
* Output         : None
* Return         : 返回为:=1成功读入,=0失败
* Attention    : None
*******************************************************************************/          
int I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress)
{   
    if(!I2C_Start())return DISABLE;
    I2C_SendByte( DeviceAddress + 1 );               /* 器件地址 */ 
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(ReadAddress & 0x00FF));   /* 设置低起始地址 */      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(((ReadAddress & 0x0700) >>7) | DeviceAddress | 0x0001);
    I2C_WaitAck();
    while(length)
    {
      *pBuffer = I2C_ReceiveByte();
      if(length == 1)I2C_NoAck();
      else I2C_Ack(); 
      pBuffer++;
      length--;
    }
    I2C_Stop();
    return ENABLE;
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/