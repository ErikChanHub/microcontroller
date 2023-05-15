#include <REGX52.H>
#include "dianzhen.h"
#include "delay.h"

sbit RCK=P3^5;
sbit SCK=P3^6;
sbit SER=P3^4;

unsigned char hello[] = {
	0xFF,0x08,0x08,0x08,0xFF,0x00,0x0E,0x15,0x15,0x15,0x08,0x00,0x7E,0x01,0x02,0x00,
	0x7E,0x01,0x02,0x00,0x0E,0x11,0x11,0x0E,0x00,0xFD,0x00,0x00,0x00,0x00,0x00,0x00,
};

void _74HC595_write(unsigned char byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SER=byte&(0x80>>i);
		SCK=1;
		SCK=0;
	}
	RCK=1;
	RCK=0;
}

void MatrixLED_Column(unsigned char column, dta)
{
	_74HC595_write(dta);
	P0 = ~(0x80>>column);
	delay(1);
	P0 = 0xFF;
}

void dianzhen_test()
{
	unsigned char i, offset=0, cnt=0;
	
	SCK=0;
	RCK=0;
	
	while(1)
	{
		for(i=0;i<8;i++)
		{
			MatrixLED_Column(i, hello[i+offset]);
			cnt++;
			if(cnt > 100)
			{
				cnt=0;
				offset++;
				if(offset>24)
				{
					offset = 0;
				}
			}
		}
	}
}