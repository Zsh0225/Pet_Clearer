/*                        -- �ɺ����ϵ��ӹ����� --                        */
/*
*   ˵    ��: STC15W4K32S4 DEMO����
*   ����ƽ̨: STC15W4K32S4     
*   �Ա�����: 
*
//  �ļ�����main.c                                                              
//  ˵�������ͻ�����ģ��ͨ��ʹ�ó���                                                                  
//  ��д��Ա��Duhemayi                                                                   
//  ��д���ڣ�2018-09-16                                                               
//  ����ά����
//  ά����¼��
//	��    ��: V1.0
//                                                          
// �����������ó��������ѧϰ�뽻�� 
// (c) Duhemayi Corporation. All rights reserved.     
******************************************************************************/
#include "adc.h"

#define     URMD    0           //0:ʹ�ö�ʱ��2��Ϊ�����ʷ�����
                                //1:ʹ�ö�ʱ��1��ģʽ0(16λ�Զ�����ģʽ)��Ϊ�����ʷ�����
                                //2:ʹ�ö�ʱ��1��ģʽ2(8λ�Զ�����ģʽ)��Ϊ�����ʷ�����



#define ADC_POWER   0x80            //ADC��Դ����λ
#define ADC_FLAG    0x10            //ADC��ɱ�־
#define ADC_START   0x08            //ADC��ʼ����λ
#define ADC_SPEEDLL 0x00            //540��ʱ��
#define ADC_SPEEDL  0x20            //360��ʱ��
#define ADC_SPEEDH  0x40            //180��ʱ��
#define ADC_SPEEDHH 0x60            //90��ʱ��

/*----------------------------
�����ʱ
----------------------------*/
void Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

/*----------------------------
��ʼ��ADC
----------------------------*/
void InitADC(void)
{
    P1ASF = 0xff;                   //����P1��ΪAD��
    ADC_RES = 0;                    //�������Ĵ���
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC�ϵ粢��ʱ
}

/*----------------------------
��ȡADC���
----------------------------*/
BYTE GetADCResult(BYTE ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //�ȴ�4��NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//�ȴ�ADCת�����
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return ADC_RES;                 //����ADC���
}

/*----------------------------
����ADC�����PC
----------------------------*/
void ShowResult(BYTE ch)
{
    Uart1_SendData(ch);                   //��ʾͨ����
    Uart1_SendData(GetADCResult(ch));     //��ʾADC��8λ���

//    SendData(ADC_LOW2);           //��ʾ��2λ���
}

void ADC_play(void)
{
    InitADC();                      //��ʼ��ADC
    while (1)
    {
        ShowResult(0);              //��ʾͨ��0
        ShowResult(1);              //��ʾͨ��1
        ShowResult(2);              //��ʾͨ��2
        ShowResult(3);              //��ʾͨ��3
        ShowResult(4);              //��ʾͨ��4
        ShowResult(5);              //��ʾͨ��5
        ShowResult(6);              //��ʾͨ��6
        ShowResult(7);              //��ʾͨ��7
    }
}



