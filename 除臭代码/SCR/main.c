#include "config.h"
uint8 Vflag=0;
uint8 Charge=0;
uint8 Workflag=0;
uint8 Fsnsflag=0;
uint8 H=0;
uint8 ChargeFlag=0;
/***************************************************************/
/*��������void IO_INIT(void)				    			   */
/*���ܣ�IO�ڳ�ʼ��                                  		   */
/*��ע��													   */
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
/*��������void SysInit(void)				    			   */
/*���ܣ�ϵͳ��ʼ��������ϵͳ                        		   */
/*��ע��													   */
/***************************************************************/
void SysInit(void)
{
		IO_INIT();//IO�ڳ�ʼ��
		P3M0=0x00;
		P3M1=0x08;
		ADCCFG = 0x0f; 
		ADC_CONTR = 0x83;
		CheckVBAT();
		Check_Charge();
		Timer0_INIT();	 //��ʱ��0��ʼ��
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



//�Ƿ���߳����
void Check_Charge(void)
{
		if(P30==0)   //	�˴�ֵΪ��ѡ��أ���缸����������������,��Ϊ����  //
		{
			Charge=2;					 //��ʱ���ڳ������β��״̬�����Ʋ��ɿ��ƻ���;
		}
		if(P54==0)																		//
		{
			Charge=1;				   //��ʱ���ڳ��״̬�����Ʋ��ɿ��𣬿��Կ��ƺ��
		}
		if((P30==1)&&(P54==1))
			Charge=0;					 //��ʱ�Ѱ��²�ͷ��				
}
//����ص���
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
			Vflag=1;								//<=3.68   10%��
}
	


void main()
{uint16 i=0;
		SysInit();	  //ϵͳ��ʼ��	
	//Uart1_init();
	while(1)
	{	
		while((Workflag==7)||(Workflag==6)||(Workflag==5)||(Workflag==4))	//���Ų�ͷʱ
		{	
			P55 = 0;
			if(Workflag==7)								//���Ų�ͷ������ȫ��������
			{	
				P31=1;		//���ƹرգ���������
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
			if(Workflag==6)	  						//���Ų�ͷ���Ҽ���������  
			{
				P31=0;											//���Ƴ���
				P55 = 0;
			}
			if(Workflag==5)								//���Ų�ͷ���ҵ���һ��
			{
				P31=0;											//���Ƴ���
				P55=0;
			}
			if(Workflag==4)								//���Ų�ͷ����û�е���
			{
				P31=0;											//���Ƴ���
				P55 = 0;
			}
				P55 = 0;	
				
		}			
	
	while((Workflag==3)||(Workflag==2)||(Workflag==1)) 
		{	
			if(Workflag==3)								//û��磬�����кܶ�ĵ�
			{
				Work();
			}
			if((Workflag==2)&&(Fsnsflag==0))								//û��磬��һ��ĵ�
			{
				Work();
			}				
			if(Workflag==1)						//û��磬�Ѿ�û����
			{
				P31=0;											//���Ƴ������رշ���
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