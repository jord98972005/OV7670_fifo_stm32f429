/*
wangguanfu@163.com
QQ:21578936
δ����������ɽ�ֹ�κ���ҵ��;
http://shop37116146.taobao.com/
*/

#include "sccb.h"
#include "delay.h"
#include "tm_stm32f4_ili9341.h"

/*
-----------------------------------------------
   ����: ��ʼ��ģ��SCCB�ӿ�
   ����: ��
 ����ֵ: ��
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
  //���� �����ⲿ�������� �����ڲ�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}*/

/*
-----------------------------------------------
   ����: start����,SCCB����ʼ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
//void startSCCB(void)
/*unsigned char start SCCB(void)
{
    SCCB_SID_H();     //�����߸ߵ�ƽ
    delay_us(50);

    SCCB_SIC_H();	   //��ʱ���߸ߵ�ʱ���������ɸ�����
    delay_us(50);
 
    SCCB_SID_L();
    delay_us(50);

    SCCB_SIC_L();	 //�����߻ָ��͵�ƽ��������������Ҫ
    delay_us(50);

 return SCCB_STATE_ACK;                //SUCCESS;
}*/

/*-----------------------------------------------
   ����: stop����,SCCB��ֹͣ�ź�
   ����: ��
 ����ֵ: ��
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
   ����: noAck,����������ȡ�е����һ����������
   ����: ��
 ����ֵ: ��
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
   ����: д��һ���ֽڵ����ݵ�SCCB
   ����: д������
 ����ֵ: ���ͳɹ�����1������ʧ�ܷ���0
-----------------------------------------------
*/
/*unsigned char SCCBwriteByte(unsigned char m_data)
{
	unsigned char j,tem;

	for(j=0;j<8;j++) //ѭ��8�η�������
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
	SCCB_SID_IN;//����SDAΪ����
	delay_us(50);
	SCCB_SIC_H();	
	delay_us(10);
	if(SCCB_SID_STATE){tem=0;}   //SDA=1����ʧ�ܣ�����0}
	else {tem=1;}   //SDA=0���ͳɹ�������1
	SCCB_SIC_L();	
	delay_us(50);	
        SCCB_SID_OUT;//����SDAΪ���

	return (tem);  
}
*/
/*
-----------------------------------------------
   ����: һ���ֽ����ݶ�ȡ���ҷ���
   ����: ��
 ����ֵ: ��ȡ��������
-----------------------------------------------
*/
/*unsigned char SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SCCB_SID_IN;//����SDAΪ����
	delay_us(50);
	for(j=8;j>0;j--) //ѭ��8�ν�������
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
        SCCB_SID_OUT;//����SDAΪ���
	return(read);
}*/

/*******************************************************************************
* Function Name  : I2C_Configuration
* Description    : EEPROM�ܽ�����
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
* Description    : �ӳ�ʱ��
* Input          : None
* Output         : None
* Return         : None
* Attention    : None
*******************************************************************************/
static void I2C_delay(void)
{ 
//   uint8_t i = 250; /* ��������Ż��ٶ� */
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
  if(!(SDA_read))return DISABLE;  /* SDA��Ϊ�͵�ƽ������æ,�˳� */

  SDA_L;
  I2C_delay();
  if(SDA_read) return DISABLE;  /* SDA��Ϊ�ߵ�ƽ�����߳���,�˳� */
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
* Return         : ����Ϊ:=1��ACK,=0��ACK
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
* Description    : ���ݴӸ�λ����λ
* Input          : - SendByte: ���͵�����
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
* Description    : ���ݴӸ�λ����λ
* Input          : None
* Output         : None
* Return         : I2C���߷��ص�����
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
* Description    : дһ�ֽ�����
* Input          : - WriteAddress: ��д���ַ
*                - SendByte: ��д������
*                  - DeviceAddress: ��������
* Output         : None
* Return         : ����Ϊ:=1�ɹ�д��,=0ʧ��
* Attention    : None
*******************************************************************************/           
int I2C_WriteByte( uint16_t WriteAddress , uint8_t SendByte , uint8_t DeviceAddress)
{   
    if(!I2C_Start()){
      return DISABLE;
    }
    I2C_SendByte( DeviceAddress );                    /* ������ַ */
    if(!I2C_WaitAck()){
    	I2C_Stop(); 
    	TM_ILI9341_Puts(20, 100, "device disable", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
    	return DISABLE;}
    I2C_SendByte((uint8_t)(WriteAddress & 0x00FF));   /* ���õ���ʼ��ַ */      
    I2C_WaitAck();  
    I2C_SendByte(SendByte);
    I2C_WaitAck();   
    I2C_Stop(); 
  /* ע�⣺��Ϊ����Ҫ�ȴ�EEPROMд�꣬���Բ��ò�ѯ����ʱ��ʽ(10ms) */
    /* Systick_Delay_1ms(10); */
    return ENABLE;
}                  

/*******************************************************************************
* Function Name  : I2C_ReadByte
* Description    : ��ȡһ������
* Input          : - pBuffer: ��Ŷ�������
*                - length: ����������
*                  - ReadAddress: ��������ַ
*                  - DeviceAddress: ��������
* Output         : None
* Return         : ����Ϊ:=1�ɹ�����,=0ʧ��
* Attention    : None
*******************************************************************************/          
int I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress)
{   
    if(!I2C_Start())return DISABLE;
    I2C_SendByte( DeviceAddress + 1 );               /* ������ַ */ 
    if(!I2C_WaitAck()){I2C_Stop(); return DISABLE;}
    I2C_SendByte((uint8_t)(ReadAddress & 0x00FF));   /* ���õ���ʼ��ַ */      
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