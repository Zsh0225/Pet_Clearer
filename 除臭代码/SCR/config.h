#ifndef _CONFIG_H
#define _CONFIG_H

/* ͨ��ͷ�ļ� */
//#include <reg52.h>
//#include "stc12c5a60s2.h"
//#include <STC89C51RC_RD_PLUS.h>
//#include "stc15fxxxx.h"
#include "stc15xx.h"
#include <intrins.h>

#include "delay.h"
//#include "hc595.h"
//#include "beep.h"
#include "timer.h"
//#include "Teststep.h"
#include "IntProcess.h"
//#include "AT24C04.h"
#include "uart.h"
#include "readchipid.h"
//#include "adC.h"
#include "pwm.h"
//#include "ad7495.h"

/* �������Ͷ��� */
typedef  signed    char    int8;    // 8λ�з���������
typedef  signed    int     int16;   //16λ�з���������
typedef  signed    long    int32;   //32λ�з���������
typedef  unsigned  char    uint8;   // 8λ�޷���������
typedef  unsigned  int     uint16;  //16λ�޷���������
typedef  unsigned  long    uint32;  //32λ�޷���������

typedef unsigned char BYTE;
typedef unsigned int WORD;

/* ȫ�����в������� */
#define FOSC   11059200L  //ϵͳ��ʱ��Ƶ�ʣ�������Ƶ�ʡ�12

#define BAUD   115200		  //UART1 ������

#define F125KHZ (65536-(FOSC/2/125000/12))
extern uint8 flag;
extern uint16 cnt;
extern uint16 min;
extern uint8 Vflag;
extern uint8 Charge;
extern uint8 Workflag;
extern uint8 Fsnsflag;
extern uint8 ChargeFlag;
extern uint16 Filter_times;
extern uint8 H,H1;
void CheckVBAT(void);
void Check_Charge(void );
void Work(void);

/* IO���ŷ��䶨�� */

sbit LED = P5^5;

#endif