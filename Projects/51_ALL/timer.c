#include <REGX52.H>
#include "LCD1602.h"

int sec = 50, min = 59, hour = 23;

void timer0_init()
{
	TMOD=TMOD&0xF0;
	TMOD=TMOD|0x01;
	TF0=0;
	TR0=1;
	TH0=64535/256;
	TL0=(64535%256 + 1);
	ET0=1;
	EA=1;
	PT0=0;
}

//void timer0_test()
//{
//	LCD_ShowString(1,1,"Clock");
//	timer0_init();
//	
//	LCD_ShowString(2,1,"  :  :");
//	
//	while(1)
//	{
//		LCD_ShowNum(2,1,hour,2);
//		LCD_ShowNum(2,4,min,2);
//		LCD_ShowNum(2,7,sec,2);
//	}
//}


// 中断服务函数, 不占用 cpu
//void Timer0_Routine() interrupt 1
//{
//	int T0Count;
//	TH0=64535/256;
//	TL0=(64535%256 + 1);
//	T0Count++;
//	if(T0Count >= 1000)
//	{
//		T0Count = 0;
//		sec++;
//		if(sec >= 60)
//		{
//			  sec = 0;
//				min++;
//			  if(min >= 60)
//				{
//					min = 0;
//					hour++;
//					if(	hour >= 24)
//					{
//						hour = 0;
//					}
//				}
//		}
//	}
//}
