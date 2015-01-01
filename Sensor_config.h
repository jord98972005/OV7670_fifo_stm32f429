

/*
wangguanfu@163.com
QQ:21578936
未经过本人许可禁止任何商业用途
http://shop37116146.taobao.com/
*/


#include"Sensor.h"

const  char OV7670_reg[OV7670_REG_NUM][2]=
{	 
       //以下为OV7670 QVGA RGB565参数  
  	{0x3a, 0x04},//Line Buffer Test Option
	{0x40, 0x10},//**RGB565 0x10 =010000 
	{0x12, 0x14},//QVGA &RGB565
	{0x32, 0x80},//HREF control
	{0x17, 0x17},//**HSTART-Output Format-horizontal
	{0x18, 0x05},//**HSTOP-Output Format-horizontal
	{0x19, 0x02},//VSTRT-Output Format-vertical
	{0x1a, 0x7b},//VSTOP-Output Format-vertical
	{0x03, 0x0a},//**Vertical Frame Control
	{0x0c, 0x0c},//**Scale & DCW enable
	{0x3e, 0x00},//PCLK divider (0x00:divided by 1)
	{0x70, 0x00},//scaling_xsc horizontal scale factor=0
	{0x71, 0x01},//**scaling_ysc vertical scale factor=1
	{0x72, 0x11},//scaling-dcwctr dcw control -Horizontal down sample by 2  &Vertical down sample by 2
	{0x73, 0x09},//**scaling_pclk_div  Bypass clock divider &Divided by 2
	{0xa2, 0x02},//scaling_pclk_delay Pixel Clock Delay
	{0x11, 0x00},//**CLKRC internal clock (0x40:use external clock)
	{0x7a, 0x20},//SLOP Gamma Curve Highest Segment Slope
	{0x7b, 0x1c},//Gamma Curve 1st Segment Input End Point 0x04 Output Value
	{0x7c, 0x28},//Gamma Curve 2nd Segment Input End Point 0x04 Output Value
	{0x7d, 0x3c},//Gamma Curve 3rd Segment Input End Point 0x04 Output Value
	{0x7e, 0x55},//Gamma Curve 4th Segment Input End Point 0x04 Output Value
	{0x7f, 0x68},//Gamma Curve 5th Segment Input End Point 0x04 Output Value
	{0x80, 0x76},//Gamma Curve 6th Segment Input End Point 0x04 Output Value
	{0x81, 0x80},//Gamma Curve 7th Segment Input End Point 0x04 Output Value
	{0x82, 0x88},//Gamma Curve 8th Segment Input End Point 0x04 Output Value
	{0x83, 0x8f},//Gamma Curve 9th Segment Input End Point 0x04 Output Value
	{0x84, 0x96},//Gamma Curve 10th Segment Input End Point 0x04 Output Value
	{0x85, 0xa3},//Gamma Curve 11th Segment Input End Point 0x04 Output Value
	{0x86, 0xaf},//Gamma Curve 12th Segment Input End Point 0x04 Output Value
	{0x87, 0xc4},//Gamma Curve 13th Segment Input End Point 0x04 Output Value
	{0x88, 0xd7},//Gamma Curve 14th Segment Input End Point 0x04 Output Value
	{0x89, 0xe8},//Gamma Curve 15th Segment Input End Point 0x04 Output Value
	{0x13, 0xe0},//bandind filter ON &Enable AEC algorithm & AEC unlimited step size
	{0x00, 0x00},//GAIN AGC-Gain control
	{0x10, 0x00},//AECH Exposure Value
	{0x0d, 0x00},//NC
	{0x14, 0x10},//**Automatic Gain ceiling -Max AGC value =2x
	{0xa5, 0x05},//BD50MAX 50Hz banding step limit
	{0xab, 0x07},//BD60Max 60Hz banding step limit
	{0x24, 0x75},//AEW AGC/AEC stable Operating Region(upper limit)
	{0x25, 0x63},//AEW AGC/AEC stable Operating Region(lower limit)
	{0x26, 0xA5},//VPT AGC/AEC Fast Mode Oerating Region 
	{0x9f, 0x78},//HAECC1 Histogram-based AEC/AGC control1
	{0xa0, 0x68},//HAECC2  Histogram-based AEC/AGC control2
	{0xa1, 0x03},//RSVD Reserved
	{0xa6, 0xdf},//HAECC3 Histogram-based AEC/AGC Control 3
	{0xa7, 0xdf},//HAECC4 Histogram-based AEC/AGC Control 4
	{0xa8, 0xf0},//HAECC5 Histogram-based AEC/AGC Control 5
	{0xa9, 0x90},//HAECC6 Histogram-based AEC/AGC Control 6
	{0xaa, 0x94},//HAECC7 Histogram-based AEC/AGC Control 7,1: Histogram-based AEC algorithm
	{0x13, 0xe5},//??Enable AGC/AEC algorithm
	{0x0e, 0x61},//Reserved NC
	{0x0f, 0x4b},//Disable HREF at optical black&Resets timing when format changes
	{0x16, 0x02},//Reserved
	{0x1e, 0x27},//**MVFP-Mirror/Vflip Enable  Mirror image&black sun enable
	{0x21, 0x02},//ADCCTR1 Reserved
	{0x22, 0x91},//ADCCTR2 Reserved
	{0x29, 0x07},//Reserved
	{0x33, 0x0b},//CHLF Array Current Control 
	{0x35, 0x0b},//Reserved
	{0x37, 0x1d},//ADC ADC Control
	{0x38, 0x71},//ACOM ADC and Analog Common Mode Control
	{0x39, 0x2a},//OFON ADC offset Control
	{0x3c, 0x78},//No HREF when VSYNC is low
	{0x4d, 0x40},//Reserved
	{0x4e, 0x20},//Reserved
	{0x69, 0x5d},//**GFIX Fix gain for B channel:1.25x&R channel:1.75x&Gb channel:1.25x&Gr channel:1.25x
	{0x6b, 0x40},//**DBLV PLL control Input clock x4  &Enable internal regulator
	{0x74, 0x19},//REG74 Digital gain manual control:1x&DG_Manu:Digital gain control by REG74[1:0]
	{0x8d, 0x4f},//Reserved
	{0x8e, 0x00},//Reserved
	{0x8f, 0x00},//Reserved
	{0x90, 0x00},//Reserved
	{0x91, 0x00},//Reserved
	{0x92, 0x00},//DM_LNL Dummy Line low 8 bits
	{0x96, 0x00},//Reserved
	{0x9a, 0x80},//Reserved
	{0xb0, 0x84},//Reserved
	{0xb1, 0x0c},//ABLC1 Enable ABLC function
	{0xb2, 0x0e},//Reserved
	{0xb3, 0x82},//THL_ST ABLC Target
	{0xb8, 0x0a},//Reserved
	{0x43, 0x14},//Reserved(AWBC1)
	{0x44, 0xf0},//Reserved(AWBC2)
	{0x45, 0x34},//Reserved(AWBC3)
	{0x46, 0x58},//Reserved(AWBC4)
	{0x47, 0x28},//Reserved(AWBC5)
	{0x48, 0x3a},//Reserved(AWBC6)
	{0x59, 0x88},//Reserved(AWB Control)
	{0x5a, 0x88},//Reserved(AWB Control)
	{0x5b, 0x44},//Reserved(AWB Control)
	{0x5c, 0x67},//Reserved(AWB Control)
	{0x5d, 0x49},//Reserved(AWB Control)
	{0x5e, 0x0e},//Reserved(AWB Control)
	{0x64, 0x04},//LCC3 Lens Correction Option 3(R, G, and B Channel Compensation Coefficient)
	{0x65, 0x20},//LCC4 Lens Correction Option 4 (Radius of the circular section where no compensation applies)
	{0x66, 0x05},//LCC5 Lens correction enable& R, G, and B channel compensation coefficient is set by registers LCC6, LCC3, and LCC7
	{0x94, 0x04},//LCC6  Lens Correction Option 6
	{0x95, 0x08},//LCC7 Lens Correction Option 7
	{0x6c, 0x0a},//AWBCTR3 AWB control3
	{0x6d, 0x55},//AWBCTR2 AWB control2
	{0x6e, 0x11},//AWBCTR1 AWB control1
	{0x6f, 0x9f},//AWBCTR0 AWB control0
	{0x6a, 0x40},//GGAIN G Channel AWB Gain
	//{0x01, 0x60}, AWB – Blue channel gain setting
	//{0x02, 0x60}, AWB – Red channel gain setting
	{0x13, 0xe7},//AEC&AWB&AGC&Banding filter Enable & unlimited step size
	{0x15, 0x00},//0: Free running PCLK&0: VSYNC changes on falling edge of PCLK
	{0x4f, 0x80},//MTX1 Matrix Coefficient 1
	{0x50, 0x80},//MTX2 Matrix Coefficient 2
	{0x51, 0x00},//MTX3 Matrix Coefficient 3
	{0x52, 0x22},//MTX4 Matrix Coefficient 4
	{0x53, 0x5e},//MTX5 Matrix Coefficient 5
	{0x54, 0x80},//MTX6 Matrix Coefficient 6
          {0x55, 0x00},//亮度 Brightness Control
          {0x56, 0x60},//对比度 Contrast Control
          {0x57, 0x90},//0x40,  Contrast Center,change according to Jim's request	
	{0x58, 0x9e},//MTXS  	Matrix Coefficient Sign for Coefficient 5 to 0&Enable, register CONTRAS-CENTER is updated automatically
	{0x41, 0x08},//Original Color matrix coefficient&AWB gain enable

	{0x3f, 0x05},//**边缘增强调整 Edge Enhancement Adjustment
	{0x75, 0x05},//REG75 Edge enhancement lower limit
	{0x76, 0xe1},//REG76 Edge enhancement higher limit &White/Black pixel correction enable
	{0x4c, 0x0F},//**噪声抑制强度  DNSTH  De-noise Strength
	{0x77, 0x0a},//**REG77  De-noise offset
	{0x3d, 0xc2},//10: U Y V Y,UV swap (use with register TSLB[3] (0x3A))TSLB[3], COM13[0]&Gamma enable&UV saturation level 1
	{0x4b, 0x09},//REG4B UV average enable
	{0xc9, 0xc8},//**SATCTR  Saturation Control UV saturation control min 1100 &UV saturation control result 1000
	{0x41, 0x38},//**Enable edge enhancement /Denoise threshold auto-adjustment for YUV output Enable
	
	{0x34, 0x11},//ARBLM Array Reference Control
	{0x3b, 0x02},//0: Select BD60ST[7:0] (0x9E) as Banding Filter Value&0: Disable 50/60 Hz auto detection&00: Same as normal mode frame rate&0: Night mode disable
	{0xa4, 0x89},//NT_CTRL Auto frame rate adjustment switch point:dummy row at 4x gain &1:Reduce frame rate by half
	{0x96, 0x00},//Reserved
	{0x97, 0x30},//Reserved
	{0x98, 0x20},//Reserved
	{0x99, 0x30},//Reserved
	{0x9a, 0x84},//Reserved
	{0x9b, 0x29},//Reserved
	{0x9c, 0x03},//Reserved
	{0x9d, 0x4c},//BD50ST 50 Hz Banding Filter Value 
	{0x9e, 0x3f},//BD60ST 60 Hz Banding Filter Value
	{0x78, 0x04},//Reserved

	{0x79, 0x01},//Reserved
	{0xc8, 0xf0},//Reserved
	{0x79, 0x0f},//Reserved
	{0xc8, 0x00},//Reserved
	{0x79, 0x10},//Reserved
	{0xc8, 0x7e},//Reserved
	{0x79, 0x0a},//Reserved
	{0xc8, 0x80},//Reserved
	{0x79, 0x0b},//Reserved
	{0xc8, 0x01},//Reserved
	{0x79, 0x0c},//Reserved
	{0xc8, 0x0f},//Reserved
	{0x79, 0x0d},//Reserved
	{0xc8, 0x20},//Reserved
	{0x79, 0x09},//Reserved
	{0xc8, 0x80},//Reserved
	{0x79, 0x02},//Reserved
	{0xc8, 0xc0},//Reserved
	{0x79, 0x03},//Reserved
	{0xc8, 0x40},//Reserved
	{0x79, 0x05},//Reserved
	{0xc8, 0x30},//Reserved why 79 c8 ????
	{0x69, 0xaa},//**GFIX Fix gain for B channel:1.5x&R channel:1.5x&Gb channel:1.5x&Gr channel:1.5x
	{0x09, 0x00},//Output drive capability:1x
	{0x3b, 0x42},//0: Select BD60ST[7:0] (0x9E) as Banding Filter Value&0: Disable 50/60 Hz auto detection&10: 1/4 of normal mode frame rate&0: Night mode disable
          {0x2d, 0x01},//ADVFL LSB of Insert Dummy Lines in Vertical Direction (1 bit equals 1 line)

};
