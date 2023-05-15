//#include <REGX52.H>
//#include "delay.h"
//#include "remote.h"
//#include "intrrupt.h"
//#include "LCD1602.h"

//unsigned char num;
//unsigned char address;
//unsigned char command;

//unsigned int IR_Time;
//unsigned char IR_State;

//unsigned char IR_Data[4];
//unsigned char IR_pData;

//unsigned char IR_DataFlag;
//unsigned char IR_RepeatFlag;
//unsigned char IR_Address;
//unsigned char IR_Command;

//void timer_remote_init()
//{
//	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
//	TMOD |= 0x01;		//���ö�ʱ��ģʽ
//	TF0=0;
//	TR0=0;
//	TH0=0;
//	TL0=0;
//}

///**
//  * @brief  ��ʱ��0���ü�����ֵ
//  * @param  Value��Ҫ���õļ�����ֵ����Χ��0~65535
//  * @retval ��
//  */
//void timer_setcnt(unsigned int Value)
//{
//	TH0=Value/256;
//	TL0=Value%256;
//}

///**
//  * @brief  ��ʱ��0��ȡ������ֵ
//  * @param  ��
//  * @retval ������ֵ����Χ��0~65535
//  */
//unsigned int timer_getcnt(void)
//{
//	return (TH0<<8)|TL0;
//}

///**
//  * @brief  ��ʱ��0����ֹͣ����
//  * @param  Flag ����ֹͣ��־��1Ϊ������0Ϊֹͣ
//  * @retval ��
//  */
//void timer_run(unsigned char Flag)
//{
//	TR0=Flag;
//}

///**
//  * @brief  ����ң�ػ�ȡ�յ�����֡��־λ
//  * @param  ��
//  * @retval �Ƿ��յ�����֡��1Ϊ�յ���0Ϊδ�յ�
//  */
//unsigned char IR_GetDataFlag(void)
//{
//	if(IR_DataFlag)
//	{
//		IR_DataFlag=0;
//		return 1;
//	}
//	return 0;
//}

///**
//  * @brief  ����ң�ػ�ȡ�յ�����֡��־λ
//  * @param  ��
//  * @retval �Ƿ��յ�����֡��1Ϊ�յ���0Ϊδ�յ�
//  */
//unsigned char IR_GetRepeatFlag(void)
//{
//	if(IR_RepeatFlag)
//	{
//		IR_RepeatFlag=0;
//		return 1;
//	}
//	return 0;
//}

///**
//  * @brief  ����ң�ػ�ȡ�յ��ĵ�ַ����
//  * @param  ��
//  * @retval �յ��ĵ�ַ����
//  */
//unsigned char IR_GetAddress(void)
//{
//	return IR_Address;
//}

///**
//  * @brief  ����ң�ػ�ȡ�յ�����������
//  * @param  ��
//  * @retval �յ�����������
//  */
//unsigned char IR_GetCommand(void)
//{
//	return IR_Command;
//}

//void remote_test()
//{
//	LCD_Init();
//	LCD_ShowString(1,1,"ADDR  CMD  NUM");
//	LCD_ShowString(2,1,"00    00   000");
////	LCD_ShowString();
//	
//	timer_remote_init();
//	Int0_Init();

//	while(1)
//	{
//		if(IR_GetDataFlag() || IR_GetRepeatFlag())	//����յ�����֡�����յ�����֡
//		{
//			address=IR_GetAddress();		//��ȡң������ַ��
//			command=IR_GetCommand();		//��ȡң����������
//			
//			LCD_ShowHexNum(2,1,address,2);	//��ʾң������ַ��
//			LCD_ShowHexNum(2,7,command,2);	//��ʾң����������
//			
//			if(command==IR_VOL_MINUS)		//���ң����VOL-��������
//			{
//				num--;						//Num�Լ�
//			}
//			if(command==IR_VOL_ADD)			//���ң����VOL+��������
//			{
//				num++;						//Num����
//			}
//			
//			LCD_ShowNum(2,12,num,3);		//��ʾNum
//		}
//	}
//}


//void Int0_Routine(void) interrupt 0
//{
//	P2 = 0x01;
//	LCD_ShowHexNum(2,3,0x01,2);
//	if(IR_State == 0)
//	{
//		LCD_ShowHexNum(2,3,0x02,2);
//		timer_setcnt(0);
//		timer_run(1);
//		IR_State = 1;
//	}
//	else if(IR_State == 1)
//	{
//		LCD_ShowHexNum(2,3,0x03,2);
//		IR_Time = timer_getcnt();
//		timer_setcnt(0);
//		if(IR_Time>13500-500 && IR_Time<13500+500)
//		{
//			IR_State = 2;
//		}
//		else if(IR_Time>11250-500 && IR_Time<11250+500)
//		{
//			IR_RepeatFlag = 1;
//			timer_run(0);
//			IR_State = 0;
//		}
//		else
//		{
//			IR_State = 1;
//		}
//	}
//	else if(IR_State == 2)
//	{
//		P2 = 0x04;
//		IR_Time = timer_getcnt();
//		timer_setcnt(0);
//		if(IR_Time>1120-500 && IR_Time<1120+500)
//		{
//			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
//			IR_pData++;
//		}
//		//�����ʱΪ2250us������յ�������1���ж�ֵ��12MHz������Ϊ2250����11.0592MHz������Ϊ2074��
//		else if(IR_Time>2250-500 && IR_Time<2250+500)
//		{
//			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//���ݶ�Ӧλ��1
//			IR_pData++;			//����λ��ָ������
//		}
//		else					//���ճ���
//		{
//			IR_pData=0;			//����λ��ָ����0
//			IR_State=1;			//��״̬Ϊ1
//		}
//		
//		if(IR_pData>=32)
//		{
//			IR_pData = 0;
//			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))	//������֤
//			{
//				IR_Address=IR_Data[0];	//ת������
//				IR_Command=IR_Data[2];
//				IR_DataFlag=1;	//���յ�����֡��־λΪ1
//			}
//			timer_run(0);		//��ʱ��ֹͣ
//			IR_State=0;			//��״̬Ϊ0
//		}
//	}
//}
