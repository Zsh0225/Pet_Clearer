#ifndef _CONFIG_H
#define _CONFIG_H

/* 通用头文件 */
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

/* 数据类型定义 */
typedef  signed    char    int8;    // 8位有符号整型数
typedef  signed    int     int16;   //16位有符号整型数
typedef  signed    long    int32;   //32位有符号整型数
typedef  unsigned  char    uint8;   // 8位无符号整型数
typedef  unsigned  int     uint16;  //16位无符号整型数
typedef  unsigned  long    uint32;  //32位无符号整型数

typedef unsigned char BYTE;
typedef unsigned int WORD;

/* 全局运行参数定义 */
#define FOSC   11059200L  //系统主时钟频率，即振荡器频率÷12

#define BAUD   115200		  //UART1 波特率

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

/* IO引脚分配定义 */

sbit LED = P5^5;

#endif