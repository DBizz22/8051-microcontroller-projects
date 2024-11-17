#include<reg51.h>

sbit out=P3^0;

void main()
{
	TMOD=0x02;
	TL0=0x9C;
	out=0;
	TR0=1;
	while(1)
	{
		while(TF0!=1);
		out=~out;
		TF0=0;
		TL0=0x9C;
	}
}