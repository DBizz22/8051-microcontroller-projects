#include<reg51.h>
#define OUTPUT P2

sbit ok=P2^7;
char digit[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7C,0x39,0x5E,0x79,0x71};
void delayms(unsigned int);

void main()
{
	unsigned int i=0;
	unsigned char rec;
	ok=1;
	SCON=0x50;
	TMOD=0x20;
	TH1=0xF4;
	TL1=0xF4;
	TR1=1;
	while(1)
	{
		ok=1;
		SBUF=digit[i];
		while(TI==0);
		TI=0;
		while(RI==0);
		RI=0;
		rec=SBUF;
		if(digit[i]==rec)
		{
			ok=0;
			OUTPUT=rec;
			delayms(500);
			i++;
		}
		
		if(i==16)
			i=0;
	}
}

void delayms(unsigned int t)
{
	unsigned int i;
	while(t--)
		for(i=0;i<125;i++);
}