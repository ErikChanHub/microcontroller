#include <REGX52.H> 
#include "delay.h"
#include "LCD1602.h"
#include "intrrupt.h"

unsigned int res;

unsigned char num;
unsigned char address;
unsigned char command;

unsigned int  IR_Time = 0;
unsigned char IR_State = 0;

unsigned char IR_Data[4];
unsigned char IR_pData = 0;

unsigned char IR_DataFlag = 0;
unsigned char IR_RepeatFlag = 0;
unsigned char IR_Address = 0;
unsigned char IR_Command = 0;

void timer_demo_init()
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TF0=0;
	TR0=0;
	TH0=0;
	TL0=0;
}

/**
  * @brief  ��ʱ��0���ü�����ֵ
  * @param  Value��Ҫ���õļ�����ֵ����Χ��0~65535
  * @retval ��
  */
void timer_setcnt(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}

/**
  * @brief  ��ʱ��0��ȡ������ֵ
  * @param  ��
  * @retval ������ֵ����Χ��0~65535
  */
unsigned int timer_getcnt(void)
{
	return (TH0<<8)|TL0;
}

/**
  * @brief  ��ʱ��0����ֹͣ����
  * @param  Flag ����ֹͣ��־��1Ϊ������0Ϊֹͣ
  * @retval ��
  */
void timer_run(unsigned char Flag)
{
	TR0=Flag;
}

/**
  * @brief  ����ң�ػ�ȡ�յ�����֡��־λ
  * @param  ��
  * @retval �Ƿ��յ�����֡��1Ϊ�յ���0Ϊδ�յ�
  */
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief  ����ң�ػ�ȡ�յ�����֡��־λ
  * @param  ��
  * @retval �Ƿ��յ�����֡��1Ϊ�յ���0Ϊδ�յ�
  */
unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}

/**
  * @brief  ����ң�ػ�ȡ�յ��ĵ�ַ����
  * @param  ��
  * @retval �յ��ĵ�ַ����
  */
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}

/**
  * @brief  ����ң�ػ�ȡ�յ�����������
  * @param  ��
  * @retval �յ�����������
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}

void demo_test()
{
	LCD_Init();
	
	timer_demo_init();
	Int0_Init();

	
	while(1)
	{
		if(IR_GetDataFlag())
		{
			address = IR_GetAddress();
			command = IR_GetCommand();
			
			LCD_ShowHexNum(2,1,address,2);
			LCD_ShowHexNum(2,5,command,2);
		}
	}
}

void Int0_Routine(void) interrupt 0
{
	if(IR_State == 0)
	{
		P2 = IR_State;
		timer_setcnt(0);
		timer_run(1);
		IR_State = 1;
	}
	else if(IR_State == 1)
	{
		IR_Time = timer_getcnt();
		P2 = IR_State;
//		LCD_ShowNum(2,1, IR_Time ,5);
		timer_setcnt(0);
		if(IR_Time>13500-500 && IR_Time<13500+500)
		{
			P2 = 0x11;
//			LCD_ShowHexNum(1,1,0x88,2);
			IR_State = 2;
		}
		else if(IR_Time>11250-500 && IR_Time<11250+500)
		{
			IR_RepeatFlag = 1;
			timer_run(0);
			IR_State = 0;
		}
		else
		{
			IR_State = 1;
		}
	}
	else if(IR_State == 2)
	{
		IR_Time = timer_getcnt();
		timer_setcnt(0);
		if(IR_Time>1120-500 && IR_Time<1120+500)
		{
			IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
			IR_pData++;
		}
		//�����ʱΪ2250us������յ�������1���ж�ֵ��12MHz������Ϊ2250����11.0592MHz������Ϊ2074��
		else if(IR_Time>2250-500 && IR_Time<2250+500)
		{
			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//���ݶ�Ӧλ��1
			IR_pData++;			//����λ��ָ������
		}
		else					//���ճ���
		{
			IR_pData=0;			//����λ��ָ����0
			IR_State=1;			//��״̬Ϊ1
		}
		
		if(IR_pData>=32)
		{
			IR_pData = 0;
			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))	//������֤
			{
				IR_Address=IR_Data[0];	//ת������
				IR_Command=IR_Data[2];
				IR_DataFlag=1;	//���յ�����֡��־λΪ1
			}
			timer_run(0);		//��ʱ��ֹͣ
			IR_State=0;			//��״̬Ϊ0
		}
	}
}
