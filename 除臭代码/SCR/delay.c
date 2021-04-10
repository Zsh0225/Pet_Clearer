#include "delay.h"

void Delay100ms(void)		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void Delay_N100ms(uint8 n)
{
	while(n--)
	{
		Delay100ms();
	}
}
