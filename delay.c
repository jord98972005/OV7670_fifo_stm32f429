/*
wangguanfu@163.com
QQ:21578936
δ����������ɽ�ֹ�κ���ҵ��;
http://shop37116146.taobao.com/
*/
#include "delay.h"

void delay_us(unsigned long Time)
{
   unsigned long i = 0;
   while(Time--)
   {
	   // Calculate for 168MHz sysclk
	   i = 5;	//72Mhz i = 10		35
	   while(i--) ;
   }
}

