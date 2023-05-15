#include <REGX52.H>
#include "delay.h"

char table[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00 };

void nixie_locate(unsigned int locate, number)
{
	P2_4 = (locate/4)<1?1:0;
	P2_3 = (locate == 4 | locate == 5 | locate==1 | locate==0)?1:0;
	P2_2 = locate%2 ? 0:1;
	P0 = table[number];
	delay(1);
	P0 = 0x00;
}


// ÊýÂë¹Ü 11011010
void nixie_tube()
{
	while(1)
	{
		nixie_locate(0, 5);
//		delay(0.02);
		nixie_locate(1, 6);
		nixie_locate(2, 7);	
		nixie_locate(3, 8);	
		nixie_locate(4, 9);	
		nixie_locate(5, 10);	
		nixie_locate(6, 11);
		nixie_locate(7, 12);
	}
}
