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
//	TMOD &= 0xF0;		//设置定时器模式
//	TMOD |= 0x01;		//设置定时器模式
//	TF0=0;
//	TR0=0;
//	TH0=0;
//	TL0=0;
//}

///**
//  * @brief  定时器0设置计数器值
//  * @param  Value，要设置的计数器值，范围：0~65535
//  * @retval 无
//  */
//void timer_setcnt(unsigned int Value)
//{
//	TH0=Value/256;
//	TL0=Value%256;
//}

///**
//  * @brief  定时器0获取计数器值
//  * @param  无
//  * @retval 计数器值，范围：0~65535
//  */
//unsigned int timer_getcnt(void)
//{
//	return (TH0<<8)|TL0;
//}

///**
//  * @brief  定时器0启动停止控制
//  * @param  Flag 启动停止标志，1为启动，0为停止
//  * @retval 无
//  */
//void timer_run(unsigned char Flag)
//{
//	TR0=Flag;
//}

///**
//  * @brief  红外遥控获取收到数据帧标志位
//  * @param  无
//  * @retval 是否收到数据帧，1为收到，0为未收到
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
//  * @brief  红外遥控获取收到连发帧标志位
//  * @param  无
//  * @retval 是否收到连发帧，1为收到，0为未收到
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
//  * @brief  红外遥控获取收到的地址数据
//  * @param  无
//  * @retval 收到的地址数据
//  */
//unsigned char IR_GetAddress(void)
//{
//	return IR_Address;
//}

///**
//  * @brief  红外遥控获取收到的命令数据
//  * @param  无
//  * @retval 收到的命令数据
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
//		if(IR_GetDataFlag() || IR_GetRepeatFlag())	//如果收到数据帧或者收到连发帧
//		{
//			address=IR_GetAddress();		//获取遥控器地址码
//			command=IR_GetCommand();		//获取遥控器命令码
//			
//			LCD_ShowHexNum(2,1,address,2);	//显示遥控器地址码
//			LCD_ShowHexNum(2,7,command,2);	//显示遥控器命令码
//			
//			if(command==IR_VOL_MINUS)		//如果遥控器VOL-按键按下
//			{
//				num--;						//Num自减
//			}
//			if(command==IR_VOL_ADD)			//如果遥控器VOL+按键按下
//			{
//				num++;						//Num自增
//			}
//			
//			LCD_ShowNum(2,12,num,3);		//显示Num
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
//		//如果计时为2250us，则接收到了数据1（判定值在12MHz晶振下为2250，在11.0592MHz晶振下为2074）
//		else if(IR_Time>2250-500 && IR_Time<2250+500)
//		{
//			IR_Data[IR_pData/8]|=(0x01<<(IR_pData%8));	//数据对应位置1
//			IR_pData++;			//数据位置指针自增
//		}
//		else					//接收出错
//		{
//			IR_pData=0;			//数据位置指针清0
//			IR_State=1;			//置状态为1
//		}
//		
//		if(IR_pData>=32)
//		{
//			IR_pData = 0;
//			if((IR_Data[0]==~IR_Data[1]) && (IR_Data[2]==~IR_Data[3]))	//数据验证
//			{
//				IR_Address=IR_Data[0];	//转存数据
//				IR_Command=IR_Data[2];
//				IR_DataFlag=1;	//置收到连发帧标志位为1
//			}
//			timer_run(0);		//定时器停止
//			IR_State=0;			//置状态为0
//		}
//	}
//}
