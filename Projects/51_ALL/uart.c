#include <REGX52.H>
#include "uart.h"
#include "delay.h"

void uart_init()
{
	SCON=0x50;
	PCON |= 0x80;;
	
	TMOD &= 0x0F;
	TMOD |= 0x20;
	ET1=0;      // 禁止定时器1中断
	TR1=1;     // 启动定时器
	TH1= 0xF3; //定时器初值
	TL1= 0xF3; //定时器重装值
	
	EA = 1;
	ES = 1;
}

// 发送数据，有点错误
void uart_send(char bt)
{
	SBUF=bt;
	while(TI==0);
	TI=0;
}

//int cnt;
void uart_test()
{
	uart_init();
	
	while(1)
	{
//		uart_send(cnt);
//		cnt++;
//		delay(1000);
	}
}

void UART_Routine() interrupt 4
{
	if(RI == 1)
	{	
		P2 = SBUF;
		uart_send(SBUF);
		RI=0;
	}
}
