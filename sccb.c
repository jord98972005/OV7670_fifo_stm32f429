/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/

#include "sccb.h"
#include "delay.h"


/*
-----------------------------------------------
   功能: 初始化模拟SCCB接口
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void SCCB_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIO_D  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SIC_BIT|SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void SCCB_SID_GPIO_OUTPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIOD  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void SCCB_SID_GPIO_INPUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   /* Enable GPIOD  clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SCCB_SID_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  //input mode
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  //上拉 若无外部上拉电阻 必须内部有上拉
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*
-----------------------------------------------
   功能: start命令,SCCB的起始信号
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void startSCCB(void)
{
    SCCB_SID_H();     //数据线高电平
    delay_us(500);

    SCCB_SIC_H();	   //在时钟线高的时候数据线由高至低
    delay_us(500);
 
    SCCB_SID_L();
    delay_us(500);

    SCCB_SIC_L();	 //数据线恢复低电平，单操作函数必要
    delay_us(500);


}
/*
-----------------------------------------------
   功能: stop命令,SCCB的停止信号
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void stopSCCB(void)
{
    SCCB_SID_L();
    delay_us(500);
 
    SCCB_SIC_H();	
    delay_us(500);
  

    SCCB_SID_H();	
    delay_us(500);
   
}

/*
-----------------------------------------------
   功能: noAck,用于连续读取中的最后一个结束周期
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void noAck(void)
{
	
	SCCB_SID_H();	
	delay_us(500);
	
	SCCB_SIC_H();	
	delay_us(500);
	
	SCCB_SIC_L();	
	delay_us(500);
	
	SCCB_SID_L();	
	delay_us(500);

}

/*
-----------------------------------------------
   功能: 写入一个字节的数据到SCCB
   参数: 写入数据
 返回值: 发送成功返回1，发送失败返回0
-----------------------------------------------
*/
unsigned char SCCBwriteByte(unsigned char m_data)
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
		delay_us(500);
		SCCB_SIC_H();	
		delay_us(500);
		SCCB_SIC_L();	
		delay_us(500);

	}
	delay_us(100);
	SCCB_SID_IN;/*设置SDA为输入*/
	delay_us(500);
	SCCB_SIC_H();	
	delay_us(100);
	if(SCCB_SID_STATE){tem=0;}   //SDA=1发送失败，返回0}
	else {tem=1;}   //SDA=0发送成功，返回1
	SCCB_SIC_L();	
	delay_us(500);	
        SCCB_SID_OUT;/*设置SDA为输出*/

	return (tem);  
}

/*
-----------------------------------------------
   功能: 一个字节数据读取并且返回
   参数: 无
 返回值: 读取到的数据
-----------------------------------------------
*/
unsigned char SCCBreadByte(void)
{
	unsigned char read,j;
	read=0x00;
	
	SCCB_SID_IN;/*设置SDA为输入*/
	delay_us(500);
	for(j=8;j>0;j--) //循环8次接收数据
	{		     
		delay_us(500);
		SCCB_SIC_H();
		delay_us(500);
		read=read<<1;
		if(SCCB_SID_STATE) 
		{
			read=read+1;
		}
		SCCB_SIC_L();
		delay_us(500);
	}	
        SCCB_SID_OUT;/*设置SDA为输出*/
	return(read);
}
