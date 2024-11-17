#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char 
	
sbit red=P1^0;
sbit yellow=P1^1;
sbit green=P1^2;

void delayms(uint t)
{
	uint i;
	while(t--)
		for(i=120;i>0;i--);
}

void light(sbit* on,sbit* off1,sbit off2)
{
	*on=1;
	*off1=0;
	*off2=0;
}

void main()
{
	red=yellow=green=0;
	while(1)
	{
		light(&red,&yellow,&green);
		delayms(1000);
		light(&yellow,&red,&green);
		delayms(1000);
		light(&green,&yellow,&red);
		delayms(1000);
	}
}