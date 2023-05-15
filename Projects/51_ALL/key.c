#include <REGX52.H>
#include "delay.h"

unsigned char get_key()
{
	unsigned char key_num = 0;
	
	if(P3_1==0){delay(20); while(P3_1==0); delay(20);key_num=1;}
	if(P3_0==0){delay(20); while(P3_0==0); delay(20);key_num=2;}
	if(P3_2==0){delay(20); while(P3_2==0); delay(20);key_num=3;}
	if(P3_3==0){delay(20); while(P3_3==0); delay(20);key_num=4;}
	
	return key_num;
}
