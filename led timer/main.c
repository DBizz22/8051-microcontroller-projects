#include<reg51.h>
#define LED P2

void main()
{
	unsigned int i;
	TMOD=0x01;
	TH0=0xD8;
	TL0=0xF0;
	TR0=1;
	LED=0x0F;
	while(1)
	{
		i=0;
		while(i<25)
		{
			while(~TF0);
			TF0=0;
			TH0=0xD8;
			TL0=0xF0;
			i++;
		}
		LED=~LED;
	}
}