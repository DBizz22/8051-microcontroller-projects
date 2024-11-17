#include<reg51.h>
#define uint unsigned int
	
sbit s=P1^0;
sbit bulb=P0^0;

void delayms(uint t)
{
	uint i;
	while(t--)
	{
		for(i=120;i>0;i--);
	}
}

void main()
{
	s=1;
	bulb=1;
	while(1)
	{
		if(s==0)
		{
			bulb=1;
			delayms(1000);
		}
		else
			bulb=0;
	}
}