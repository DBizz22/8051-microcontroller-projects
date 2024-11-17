#include<reg51.h>
#define LED P2

unsigned int i;
void main()
{
	EA=1;
	ET0=1;
	TMOD=0x01;
	TH0=0xD8;
	TL0=0xF0;
	TR0=1;
	LED=0x0F;
	i=0;
	while(1);
}

void timer0() interrupt 1
{
	i++;
	if(i==25)
	{
		LED=~LED;
		i=0;
	}
	TH0=0xD8;
	TL0=0xF0;
	TF0=0;
}