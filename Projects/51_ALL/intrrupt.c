#include <REGX52.H>


/**
  * @brief  �ⲿ�ж�0��ʼ��
  * @param  ��
  * @retval ��
  */
void Int0_Init(void)
{
	IT0=1;
	IE0=0;
	EX0=1;
	EA=1;
	PX0=1;
}
