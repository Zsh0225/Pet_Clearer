#include "IntProcess.h"

unsigned char Int0Cnt,Int1Cnt,Int2Cnt,Int3Cnt;

void InterruptInit(void)
{
	IT0 = 1;	 //外部中断0下降沿触发
	IT1 = 1;	 //外部中断1下降沿触发
	EX0 = 0;	 //外部中断0禁止
	EX1 = 0;	 //外部中断1禁止

//	EX2 = 0;	 //外部中断2禁止
//	IT2 = 1;	 //外部中断2下降沿触发
//
//	EX3 = 0;	 //外部中断2禁止
//	IT3 = 1;	 //外部中断2下降沿触发

	EA  = 1;//开总中断
}
/*INT0作为绿色LED的计数*/	  //P3^2
void Int0Process(void) interrupt 0
{
	Int0Cnt++;
}
/*INT1作为黄色LED的计数*/	   //P3^3
void Int1Process(void) interrupt 2
{
	Int1Cnt++;
}

///*INT2作为红色 LED的计数*/	   //P4^3
//void Int2Process(void) interrupt 6
//{
//	Int2Cnt++;			
//}
//
///*INT3作为闪光灯的计数*/	   //P4^2
//void Int3Process(void) interrupt 7
//{
//	Int3Cnt++;
//}
