#include<reg51.h>
#define uchar unsigned char

sbit on=P1^0;
sbit pause=P3^2;
uchar num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar dash=0x40;
void delayus(unsigned int);
void display(unsigned int,unsigned int,unsigned int);
int min,sec,msec;

void main()
{
	EA=1;
	ET0=1;
	EX0=1;
	IE0=1;
	IT0=1;
	TMOD=0x01;
	TL0=0xF0;
	TH0=0xD8;
	P0=0;
	on=1;
	pause=1;
	min=sec=msec=0;
	display(min,sec,msec);
	TR0=1;
	while(1)
	{
		if(~on)
			display(min,sec,msec);
		else
		{
			P0=0;
			P2=0;
			TR0=0;
			while(on);
			TL0=0xF0;
			TH0=0xD8;
			min=sec=msec=0;
			TR0=1;
		}
	}
}

void delayus(unsigned int t)
{
	int i;
	while(t--)
	{
		for(i=120;i>0;i--);
	}
}

void display(unsigned int min,unsigned int sec,unsigned int msec)
{
		P2=0;
		P0=num[msec%10];
		delayus(1);
		P2=1;
		P0=num[msec/10];
		delayus(1);
		P2=2;
		P0=dash;
		delayus(1);
		P2=3;
		P0=num[sec%10];
		delayus(1);
		P2=4;
		P0=num[sec/10];
		delayus(1);
		P2=5;
		P0=dash;
		delayus(1);
		P2=6;
		P0=num[min%10];
		delayus(1);
		P2=7;
		P0=num[min/10];
		delayus(1);
}

void int0() interrupt 0
{
	while(pause==0&&on==0)
		display(min,sec,msec);
}

void Time() interrupt 1
{
		msec++;
		if(msec==100)
		{
			sec++;
			msec=0;
		}
		if(sec==60)
		{
			min++;
			sec=0;
		}
		if(min==60)
					min=0;
	TL0=0xF0;
	TH0=0xD8;
}

