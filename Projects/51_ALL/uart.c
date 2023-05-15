#include <REGX52.H>
#include "uart.h"
#include "delay.h"

void uart_init()
{
	SCON=0x50;
	PCON |= 0x80;;
	
	TMOD &= 0x0F;
	TMOD |= 0x20;
	ET1=0;      // ��ֹ��ʱ��1�ж�
	TR1=1;     // ������ʱ��
	TH1= 0xF3; //��ʱ����ֵ
	TL1= 0xF3; //��ʱ����װֵ
	
	EA = 1;
	ES = 1;
}

// �������ݣ��е����
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
