#include "IntProcess.h"

unsigned char Int0Cnt,Int1Cnt,Int2Cnt,Int3Cnt;

void InterruptInit(void)
{
	IT0 = 1;	 //�ⲿ�ж�0�½��ش���
	IT1 = 1;	 //�ⲿ�ж�1�½��ش���
	EX0 = 0;	 //�ⲿ�ж�0��ֹ
	EX1 = 0;	 //�ⲿ�ж�1��ֹ

//	EX2 = 0;	 //�ⲿ�ж�2��ֹ
//	IT2 = 1;	 //�ⲿ�ж�2�½��ش���
//
//	EX3 = 0;	 //�ⲿ�ж�2��ֹ
//	IT3 = 1;	 //�ⲿ�ж�2�½��ش���

	EA  = 1;//�����ж�
}
/*INT0��Ϊ��ɫLED�ļ���*/	  //P3^2
void Int0Process(void) interrupt 0
{
	Int0Cnt++;
}
/*INT1��Ϊ��ɫLED�ļ���*/	   //P3^3
void Int1Process(void) interrupt 2
{
	Int1Cnt++;
}

///*INT2��Ϊ��ɫ LED�ļ���*/	   //P4^3
//void Int2Process(void) interrupt 6
//{
//	Int2Cnt++;			
//}
//
///*INT3��Ϊ����Ƶļ���*/	   //P4^2
//void Int3Process(void) interrupt 7
//{
//	Int3Cnt++;
//}
