/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/

#include "Sensor.h"
#include "Sensor_config.h"
#include "stm32f4xx_conf.h"
#include "tm_stm32f4_ili9341.h"
#include "sccb.h"
extern const char OV7670_reg[OV7670_REG_NUM][2];


int Cam_init(void){
 	uint16_t i=0;

 	GPIO_InitTypeDef GPIO_InitStructure;
 	DCMI_InitTypeDef DCMI_InitStructure;
 	DMA_InitTypeDef  DMA_InitStructure;

 	
 	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);//使能DCMI的GPIO时钟  

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
       
       
        //---------------------------------------控制信号引脚定义---------------------------------------
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_6| GPIO_Pin_8;                //DCMI 2->WRST, 3->RRST, 4->WEN, 6->RCLK, 8->OE(CS)
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
        GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
        //SYSCFG->CMPCR = 0x00000001;                                                                                 //使用IO 补偿单元，
                                                                                                                                                                                                        //当GPIO 速度超过50M 的时候要考虑使用此设置       
        GPIO_Init(GPIOA, &GPIO_InitStructure);
       
       
       
        //--------------VSYNC IN ---------------------------------
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                                                                //DCMI VSYNC
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;                                                //同步信号检测IO
        GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
        //GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
        //SYSCFG->CMPCR = 0x00000001;                                                                                
        GPIO_Init(GPIOB, &GPIO_InitStructure);       


       RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);  //DCMI       
       
        DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
        DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
        DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
        DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
        DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_High;
        DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
        DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
        DCMI_Init(&DCMI_InitStructure);     

	I2C_Configuration();

// Configures the DMA2 to transfer Data from DCMI
	// Enable DMA2 clock
	RCC_AHB1PeriphClockCmd(DMA_Camera_STREAM_CLOCK, ENABLE);

	// DMA2 Stream1 Configuration
	DMA_DeInit(DMA_CameraToRAM_Stream);

while (DMA_GetCmdStatus(DMA_CameraToRAM_Stream) != DISABLE)
	{
	}
	DMA_InitStructure.DMA_Channel = DMA_Camera_Channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&RAM_Buffer;
	// DMA_InitStructure.DMA_Memory0BaseAddr = 0x60020000;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RAM_Buffer;

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
//	DMA_InitStructure.DMA_BufferSize = BuffSize;
	// DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_BufferSize = picture_x*picture_y*2/4;

	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	// DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA_CameraToRAM_Stream, &DMA_InitStructure);


 /*if( 0 == I2C_WriteByte ( 0x12, 0x80 , SCCBID_7670 ) ) // Reset SCCB 
  {
  	TM_ILI9341_Puts(20, 20, "0x12 wrong", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
     return 0 ;

  }

  delay_us(50000);

  for( i=0 ; i < OV7670_REG_NUM ; i++ )
  {												
	 if( 0 == I2C_WriteByte(  OV7670_reg[i][0], OV7670_reg[i][1] , SCCBID_7670 ) )
	 {
	 	TM_ILI9341_Puts(20, 140, "FIFOddddd set", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_GREEN2);
		return 0;
	 }
  }*/
	//uint8_t temp;
if(SCCB_WR_Reg(0x12,0x80))return 1;	//复位SCCB	  
	delay_us(50000); 
	//读取产品型号
 	/*temp=SCCB_RD_Reg(0x0b);   
	if(temp!=0x73)return 2;  
 	temp=SCCB_RD_Reg(0x0a);   
	if(temp!=0x76)return 2;
	//初始化序列	  
	for(i=0;i<sizeof(ov7670_init_reg_tbl)/sizeof(ov7670_init_reg_tbl[0]);i++)
	{
	   	SCCB_WR_Reg(ov7670_init_reg_tbl[i][0],ov7670_init_reg_tbl[i][1]);
		delay_ms(2);
 	}*/
   	return 0x00; 	//ok

  //return 1; 

}


//////////////////////////////////////////////////
////函数功能：中断配制
//guanfu_wang

void Sensor_Interrupts_Config(void)//VSYNC interrupt  misc.c
{
  NVIC_InitTypeDef NVIC_InitStructure;

    // Configure one bit for preemption priority 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  // Enable the EXTI9_5 Interrupt 
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  // set  EXTI3_IRQn interrupt
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   // set Preemption priority
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    // set Responsive priority
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   // utilize interrupt
  NVIC_Init(&NVIC_InitStructure);
   // init interrupt
}

////////////////////////////////////////////////////////////////////////
void Sensor_EXTI_Config(void)//VSYNC interrupt
{
  EXTI_InitTypeDef EXTI_InitStructure;
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource7); //link exti-E3
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  // set EXTI_Line0 external interrupt
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  // set interrupt mode
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising ;
  // use rising trigger
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
   // use external interrupt
  EXTI_Init(&EXTI_InitStructure);
  // init external interrupt
  //EXTI_GenerateSWInterrupt(EXTI_Line3);

}
/*void DMA_init_config(void)
{

	RCC_AHB1PeriphClockCmd(DMA_Camera_STREAM_CLOCK, ENABLE);
	DMA_DeInit(DMA_CameraToRAM_Stream);
	DMA_InitTypeDef  DMA_InitStructure;

	
  	while (DMA_GetCmdStatus(DMA_CameraToRAM_Stream) != DISABLE)
	{
	}
	DMA_InitStructure.DMA_Channel = DMA_Camera_Channel;
	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RAM_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = picture_x*picture_y*2/4;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

	DMA_Init(DMA_CameraToRAM_Stream, &DMA_InitStructure);

}

////////////////////////////
//HSE high speed external clock
//功能：提供时钟
//guanfu_wang
void XCLK_init_ON(void)
{
  
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
    // init GPIOA  XCLK PA8
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF ; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
   RCC_MCO1Config(RCC_MCO1Source_HSE,RCC_MCO1Div_1  );//hsi
    //RCC_MCO1Config(RCC_MCO1Source_PLLCLK,RCC_MCO1Div_3  );//hsi
}

void PowerDown(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//PF15:PWRDOWN
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; 
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ; 
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOF, GPIO_Pin_15);//power on
}
/////////////////////////////
//VSYNC GPIO INIT
//guanfu_wang
void Sensor_GPIO_Init(void)//
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
   // Enable GPIOC  clock
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //VSYNC E3
  GPIO_InitStructure.GPIO_Pin =  Sensor_VSYNC_BIT;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
////上拉 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
}




///////////////////////////////////////////////////////////////////////////
//功能：写OV7660寄存器
//返回：1-成功	0-失败
//guanfu_wang
unsigned char wr_Sensor_Reg(unsigned char regID, unsigned char regDat)
{
		startSCCB();//发送SCCB 总线开始传输命令
	if(0==SCCBwriteByte(0x42))//写地址
	{
		stopSCCB();//发送SCCB 总线停止传输命令
		return(0);//错误返回
	}
	delay_us(10);
  	if(0==SCCBwriteByte(regID))//积存器ID
	{
		stopSCCB();//发送SCCB 总线停止传输命令
		return(0);//错误返回
	}
	delay_us(10);
  	if(0==SCCBwriteByte(regDat))//写数据到积存器
	{
		stopSCCB();//发送SCCB 总线停止传输命令
		return(0);//错误返回
	}
  	stopSCCB();//发送SCCB 总线停止传输命令
	
  	return(1);//成功返回
}
////////////////////////////
//功能：读OV7660寄存器
//返回：1-成功	0-失败
//guanfu_wang
unsigned char rd_Sensor_Reg(unsigned char regID, unsigned char *regDat)
{
	//通过写操作设置寄存器地址
	startSCCB();
	if(0==SCCBwriteByte(0x42))//写地址 0X42  =OV7670的ID
	{
		stopSCCB();//发送SCCB 总线停止传输命令
		return(0);//错误返回
	}
	delay_us(10);
  	if(0==SCCBwriteByte(regID))//积存器ID
	{
		stopSCCB();//发送SCCB 总线停止传输命令
		return(0);//错误返回
	}
	stopSCCB();//发送SCCB 总线停止传输命令
	
	delay_us(10);
	
	//设置寄存器地址后，才是读
	startSCCB();
	if(0==SCCBwriteByte(0x43))//读地址
	{
		stopSCCB();//发送SCCB 总线停止传输命令
		return(0);//错误返回
	}
	delay_us(10);
  	*regDat=SCCBreadByte();//返回读到的值
  	noAck();//发送NACK命令
  	stopSCCB();//发送SCCB 总线停止传输命令
  	return(1);//成功返回
}

// Sensor_init() 
//返回1成功，返回0失败
//guanfu_wang
unsigned char Sensor_init(void)
{
	unsigned char temp;
	unsigned int i=0;

	DCMI_init_config();
	DMA_init_config();
	PowerDown();
	
           XCLK_init_ON();//开启MCO功能 提供时钟给CMOS传感器
	//uchar ovidmsb=0,ovidlsb=0;
	Sensor_GPIO_Init();
	SCCB_GPIO_Config();//io init..
        
	temp=0x80;
	if(0==wr_Sensor_Reg(0x12, temp)) //Reset SCCB
	{
          return 0 ;//错误返回
	}
        Delay(10);
	if(0==rd_Sensor_Reg(0x0b, &temp))//读ID
	{
		return 0 ;//错误返回
	}
        
         if(temp==0x73)//OV7670
	 {
	   for(i=0;i<OV7670_REG_NUM;i++)
	   {
		if( 0==wr_Sensor_Reg(OV7670_reg[i][0],OV7670_reg[i][1]))
		{
			return 0;//错误返回
		}
	    }
   	  
	  }
	  
	return 1; //ok

} */


