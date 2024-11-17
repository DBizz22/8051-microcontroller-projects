#include<reg51.h>

sbit out=P3^0;

void main()
{
	int i;
	out=0;
	TMOD=0x01;
	TL0=0xF0;
	TH0=0xD8;
	TR0=1;
	while(1)
	{
		i=0;
		while(i<30)
		{
			while(TF0!=1);
			TF0=0;
			TL0=0xF0;
			TH0=0xD8;
			i++;
		}
		out=~out;
		i=0;
		while(i<70)
		{
			while(TF0!=1);
			TF0=0;
			TL0=0xF0;
			TH0=0xD8;
			i++;
		}
		out=~out;
	}
}