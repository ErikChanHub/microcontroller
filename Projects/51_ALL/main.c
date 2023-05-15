#include <REGX52.H> 
#include "delay.h"
#include "nixie_tube.h"
#include "LCD1602.h"
#include "matrix.h"
#include "timer.h"
#include "uart.h"
#include "dianzhen.h"
#include "beep.h"
#include "pwm.h"
#include "remote.h"
#include "demo.h"

//void lcd_test()
//{
//	LCD_Init();
//	LCD_ShowChar(1,1,'B');
//	LCD_ShowString(1,3,"Hello");
//	LCD_ShowNum(1,9,123,3);
//	LCD_ShowHexNum(2,1,0xA9,2);
//	LCD_ShowBinNum(2,4,0xA9,8);
//}


void main()
{
//	LCD_Init();
//	nixie_tube();
//	lcd_test();
//	matrix_test();
//	timer0_test();
//	uart_test();
//  	dianzhen_test();
//	  beep_test();
//	  pwm_test();
//	  remote_test();
	demo_test();
}

