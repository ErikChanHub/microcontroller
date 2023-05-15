#include <REGX52.H> 
#include "delay.h"
#include "LCD1602.h"

unsigned char MatrixKey()
{
	unsigned char keyNum = 0;
	
	P1 = 0xFF;
	P1_3 = 0;
	if(P1_7 == 0){delay(20);while(P1_7 == 0); delay(20); keyNum = 1;}
	if(P1_6 == 0){delay(20);while(P1_6 == 0); delay(20); keyNum = 5;}
	if(P1_5 == 0){delay(20);while(P1_5 == 0); delay(20); keyNum = 9;}
	if(P1_4 == 0){delay(20);while(P1_4 == 0); delay(20); keyNum = 13;}
	
	P1 = 0xFF;
	P1_2 = 0;
	if(P1_7 == 0){delay(20);while(P1_7 == 0); delay(20); keyNum = 2;}
	if(P1_6 == 0){delay(20);while(P1_6 == 0); delay(20); keyNum = 6;}
	if(P1_5 == 0){delay(20);while(P1_5 == 0); delay(20); keyNum = 10;}
	if(P1_4 == 0){delay(20);while(P1_4 == 0); delay(20); keyNum = 14;}
	
	P1 = 0xFF;
	P1_1 = 0;
	if(P1_7 == 0){delay(20);while(P1_7 == 0); delay(20); keyNum = 3;}
	if(P1_6 == 0){delay(20);while(P1_6 == 0); delay(20); keyNum = 7;}
	if(P1_5 == 0){delay(20);while(P1_5 == 0); delay(20); keyNum = 11;}
	if(P1_4 == 0){delay(20);while(P1_4 == 0); delay(20); keyNum = 15;}
	
	P1 = 0xFF;
	P1_0 = 0;
	if(P1_7 == 0){delay(20);while(P1_7 == 0); delay(20); keyNum = 4;}
	if(P1_6 == 0){delay(20);while(P1_6 == 0); delay(20); keyNum = 8;}
	if(P1_5 == 0){delay(20);while(P1_5 == 0); delay(20); keyNum = 12;}
	if(P1_4 == 0){delay(20);while(P1_4 == 0); delay(20); keyNum = 16;}
	
	return keyNum;
}


unsigned char keyNum;
int password = 6789;
int input = 0;

void clear_pwd()
{
	input = 0;
	LCD_ShowNum(2,1,input,4);
}


void matrix_test()
{
	LCD_ShowString(1,1,"Password");
	while(1)
	{
			keyNum = MatrixKey();
		
			if(keyNum && keyNum == 16) // 确认
			{
				if(password == input){
					LCD_ShowString(1,14,"YES");
					clear_pwd();
				}
				else
				{
					LCD_ShowString(1,14,"ERR");
					clear_pwd();
				}
			}
			
			if(keyNum == 15) // 取消
			{
				clear_pwd();
				LCD_ShowString(1,14,"");
			}
			
			if(keyNum && keyNum <= 10)
			{
				keyNum = keyNum%10;
				input *= 10;
				input += keyNum;
				if(input<=9999)
				{
					LCD_ShowNum(2,1,input,4);
				}
        else
				{
					input -= keyNum;
					input /= 10;
				}
			}
	}
}

