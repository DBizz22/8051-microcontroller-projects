#include<reg51.h>
#define OUTPUT P2

sbit ok=P3^2;
unsigned char rec;
unsigned int wait=1;

void main()
{
	ok=1;
	SCON=0x50;
	EA=1;
	EX0=1;
	IT0=1;
	TMOD=0x20;
	TH1=0xF4;
	TL1=0xF4;
	TR1=1;
	while(1)
	{
		wait=1;
		while(RI==0);
		RI=0;
		rec=SBUF;
		SBUF=rec;
		while(TI==0);
		TI=0;
		while(wait);
	}
}

void int0() interrupt 0
{
		OUTPUT=rec;
		while(ok==0);
		wait=0;
}