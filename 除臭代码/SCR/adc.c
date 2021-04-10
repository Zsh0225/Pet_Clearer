/*                        -- 渡河蚂蚁电子工作室 --                        */
/*
*   说    明: STC15W4K32S4 DEMO程序
*   开发平台: STC15W4K32S4     
*   淘宝网店: 
*
//  文件名：main.c                                                              
//  说明：供客户测试模块通信使用程序                                                                  
//  编写人员：Duhemayi                                                                   
//  编写日期：2018-09-16                                                               
//  程序维护：
//  维护记录：
//	版    本: V1.0
//                                                          
// 免责声明：该程序仅用于学习与交流 
// (c) Duhemayi Corporation. All rights reserved.     
******************************************************************************/
#include "adc.h"

#define     URMD    0           //0:使用定时器2作为波特率发生器
                                //1:使用定时器1的模式0(16位自动重载模式)作为波特率发生器
                                //2:使用定时器1的模式2(8位自动重载模式)作为波特率发生器



#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

/*----------------------------
软件延时
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
初始化ADC
----------------------------*/
void InitADC(void)
{
    P1ASF = 0xff;                   //设置P1口为AD口
    ADC_RES = 0;                    //清除结果寄存器
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC上电并延时
}

/*----------------------------
读取ADC结果
----------------------------*/
BYTE GetADCResult(BYTE ch)
{
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ch | ADC_START;
    _nop_();                        //等待4个NOP
    _nop_();
    _nop_();
    _nop_();
    while (!(ADC_CONTR & ADC_FLAG));//等待ADC转换完成
    ADC_CONTR &= ~ADC_FLAG;         //Close ADC

    return ADC_RES;                 //返回ADC结果
}

/*----------------------------
发送ADC结果到PC
----------------------------*/
void ShowResult(BYTE ch)
{
    Uart1_SendData(ch);                   //显示通道号
    Uart1_SendData(GetADCResult(ch));     //显示ADC高8位结果

//    SendData(ADC_LOW2);           //显示低2位结果
}

void ADC_play(void)
{
    InitADC();                      //初始化ADC
    while (1)
    {
        ShowResult(0);              //显示通道0
        ShowResult(1);              //显示通道1
        ShowResult(2);              //显示通道2
        ShowResult(3);              //显示通道3
        ShowResult(4);              //显示通道4
        ShowResult(5);              //显示通道5
        ShowResult(6);              //显示通道6
        ShowResult(7);              //显示通道7
    }
}



