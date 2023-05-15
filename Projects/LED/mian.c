#include <REGX52.H>

//void delay(float s)
//{
//	long k=s*10000;
//	while(k--);
//}

// 跑马灯
//void light_led()
//{
//	while(1)
//	{
//		P2 = 0xFE;
//		delay(0.2);
//		P2 = 0xFD;
//		delay(0.4);
//		P2 = 0xFB;
//		delay(0.6);
//		P2 = 0xF7;
//		delay(0.8);
//		P2 = 0xEF;
//		delay(1);
////		P2 = 0xDF;
////		delay(1.2);
////		P2 = 0xBF;
////		delay(1.3);
////		P2 = 0x7F;
////		delay(1.6);
//	}
//}

// 独立按键
//void key_down()
//{
//	unsigned char LEDNum = 0;
//	while(1)
//	{
////		if(P3_1==0)
////		{
////			delay(0.02);
////			while(P3_1==0);
////			delay(0.02); 
////			P2_0 = ~P2_0;
////		}
//		
//		
////		if(P3_1==0){
////		  
////			delay(0.02);
////			while(P3_1==0);
////			delay(0.02); 
////			
////			LEDNum ++;
////			P2 = ~LEDNum;
////		}
//		
//		if(P3_1==0){
//		  
//			delay(0.02);
//			while(P3_1==0);
//			delay(0.02); 
//			
//			
//			if(LEDNum == 0)
//			{
//				LEDNum = 8;
//			}
//			LEDNum--;
//			P2 = ~(0x01 << LEDNum);
//		}
//		
//		if(P3_3==0){
//		  
//			delay(0.02);
//			while(P3_3==0);
//			delay(0.02); 
//			
//			LEDNum ++;
//			if(LEDNum ==8)
//			{
//				LEDNum = 0;
//			}
//			P2 = ~(0x01 << LEDNum);
//		}
//		
//	}
//}


//void nixie_locate(unsigned char locate, unsigned char number)
//{
//	P2_4 = (locate/4)<1?0:1;
//	P2_3 = ~((locate%4) | (locate%5));
//	P2_2 = locate%2;
//	P0 = 0x01011011;
//}

//// 数码管
//void nixie_tube()
//{
//	nixie_locate(2,2);
//	while(1)
//	{
//	
//	}
//}

void main()
{
//	nixie_tube();
}