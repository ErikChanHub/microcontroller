#include "delay.h"

void delay_int(unsigned int xms)
{
	unsigned char i, j;
	while(xms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}


void delay(float s)
{
	long k=s*10;
	while(k--);
}
