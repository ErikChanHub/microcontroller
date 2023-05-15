#include <REGX52.H>
#include "pwm.h"
#include "delay.h"
#include "nixie_tube.h"
#include "key.h"

sbit  LED = P1^0;

void Delay0(unsigned int t)
{
	while(t--);
}

void breath()
{
		unsigned char time, i;
//	unsigned int left;
	while(1)
	{
		for(time=0; time<100; time++)
		{
			for(i=0; i<20; i++)
			{
				LED=0;
//				left = 100-time;
//				while(time--);
				Delay0(time);
				LED=1;
//				while(left--);
				Delay0(100-time);
			}
		}
		for(time=100; time>0; time--)
		{
			for(i=0; i<20; i++)
			{
				LED=0;
//				left = 100-time;
//				while(time--);
				Delay0(time);
				LED=1;
//				while(left--);
				Delay0(100-time);
			}
		}
	}
}

void timer_init()
{
	TMOD=TMOD&0xF0;
	TMOD=TMOD|0x01;
	TF0=0;
	TR0=1;
	TH0=0xFF;
	TL0=0x9C;
	ET0=1;
	EA=1;
	PT0=0;
}

unsigned char cnt, cmp;
unsigned char key, speed;

void dianji()
{
	timer_init();
	cmp = 50;
	while(1)
	{
		key = get_key();
		if(key == 1)
		{
			speed++;
			speed%=4;
			if(speed == 0) {cmp = 0;}
			if(speed == 1) {cmp = 40;}
			if(speed == 2) {cmp = 60;}
			if(speed == 3) {cmp = 90;}
		}
		nixie_locate(0, speed);
	}
}

void pwm_test()
{
	dianji();
}

void Timer0_Routine() interrupt 1
{
	TH0=0xFF;
	TL0=0x9C;
	cnt++;
	cnt%=100;
	if(cnt < cmp)
	{
		LED = 1;
	}
	else
	{
		LED = 0;
	}
}
