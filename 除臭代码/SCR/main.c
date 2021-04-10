#include "config.h"
uint8 Vflag=0;
uint8 Charge=0;
uint8 Workflag=0;
uint8 Fsnsflag=0;
uint8 H=0;
uint8 ChargeFlag=0;
/***************************************************************/
/*函数名：void IO_INIT(void)				    			   */
/*功能：IO口初始化                                  		   */
/*备注：													   */
/***************************************************************/
void IO_INIT(void)
{
		P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P3M0 = 0x00;
    P3M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;	
}

/***************************************************************/
/*函数名：void SysInit(void)				    			   */
/*功能：系统初始化，配置系统                        		   */
/*备注：													   */
/***************************************************************/
void SysInit(void)
{
		IO_INIT();//IO口初始化
		P3M0=0x00;
		P3M1=0x08;
		ADCCFG = 0x0f; 
		ADC_CONTR = 0x83;
		CheckVBAT();
		Check_Charge();
		Timer0_INIT();	 //定时器0初始化
}

void Work(void)
{
if(P32==1&&flag==1)
	{
		P55 = 0;
		min = 5;
		cnt = 0;
		P31=1;
	}
	if(P32==0&&flag==1)
	{
		P55=1;
		P31=1;	
	}	
	if(P32==0&&flag==0)
	{
		P55=0;
		P31=1;
	}		
}



//是否插线充电中
void Check_Charge(void)
{
		if(P30==0)   //	此处值为所选电池，充电几乎充满进入涓流充电,视为满电  //
		{
			Charge=2;					 //此时处于充满但任插电状态，蓝灯不可控制会亮;
		}
		if(P54==0)																		//
		{
			Charge=1;				   //此时处于充电状态，蓝灯不可控灭，可以控制红灯
		}
		if((P30==1)&&(P54==1))
			Charge=0;					 //此时已拔下插头，				
}
//检测电池电量
void CheckVBAT(void)
{
		ADC_CONTR |= 0x40;
		_nop_();   _nop_(); 	
		while (!(ADC_CONTR & 0x20)); 
		ADC_CONTR &= ~0x20; 
		H = ADC_RES; 
		if(H>=0xA0)				//4.15V
			Vflag=3;
		if((H<0xA0)&&(H>=130))	//	//4.15~3.68  0x8e
			Vflag=2;
		if(H<130)
			Vflag=1;								//<=3.68   10%电
}
	


void main()
{uint16 i=0;
		SysInit();	  //系统初始化	
	//Uart1_init();
	while(1)
	{	
		while((Workflag==7)||(Workflag==6)||(Workflag==5)||(Workflag==4))	//插着插头时
		{	
			P55 = 0;
			if(Workflag==7)								//插着插头并且完全充满电了
			{	
				P31=1;		//将灯关闭，蓝灯自亮
				P55=0;
				ChargeFlag=1;
				while(ChargeFlag==1)
				{
					P30=0;
					Delay_N100ms(1);
					P30=1;
					i=100;
					while(i--)
						_nop_();
					if(Charge==0)
					{
						ChargeFlag=0;
					}
				}	
			}
			if(Workflag==6)	  						//插着插头并且几乎充满了  
			{
				P31=0;											//将灯常亮
				P55 = 0;
			}
			if(Workflag==5)								//插着插头并且电有一半
			{
				P31=0;											//将灯常量
				P55=0;
			}
			if(Workflag==4)								//插着插头并且没有电了
			{
				P31=0;											//将灯常量
				P55 = 0;
			}
				P55 = 0;	
				
		}			
	
	while((Workflag==3)||(Workflag==2)||(Workflag==1)) 
		{	
			if(Workflag==3)								//没插电，但是有很多的电
			{
				Work();
			}
			if((Workflag==2)&&(Fsnsflag==0))								//没插电，有一半的电
			{
				Work();
			}				
			if(Workflag==1)						//没插电，已经没电了
			{
				P31=0;											//将灯常亮，关闭风扇
				P55=0;
				Fsnsflag=1;	
				while(Fsnsflag)
				{
					if((Charge==1)||(Charge==2))
					{
						Fsnsflag=0;
					}	
				}
			}
		}
	}		
}