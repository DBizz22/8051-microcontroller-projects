#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
#define DELAY 100

void delayms(uint);
void lcdcmd(uchar);
void lcddat(uchar);
void lcdstr(uchar*);

sbit power=P0^0;
sbit bright=P0^1;
sbit rs=P3^0;
sbit rw=P3^1;
sbit E=P3^2;
sbit on=P1^0;
sbit play=P1^1;
	
void main()
{
	int i=0;
	char test1[]={"HELLO WORLD! BIZZ IS ON."};
	//char words[]={"HELLO WORLD!. MY NAME IS MR DIVINE. "};
	power=bright=1;
	on=play=1;
	rs=rw=E=0;
	P2=0;
	
	lcdcmd(0x01);
	lcdcmd(0x0c);
	lcdcmd(0x8f);
	while(1)
	{
		for(i=0;i<26;i++)
		{
			lcddat(test1[i]);
			lcdcmd(0x18);
			delayms(100);
		}
		//lcdcmd(0x1c);
		//delayms(100);
	}
}

void lcdcmd(uchar i)
{
	P2=i;
	rs=0;
	rw=0;
	E=1;
	delayms(1);
	E=0;
}

void lcddat(uchar i)
{
	P2=i;
	rs=1;
	rw=0;
	E=1;
	delayms(DELAY);
	E=0;
}

void delayms(uint i)
{
	uint j;
	while(i--)
	{
		for(j=120;j>0;j--);
	}
}

void lcdstr(uchar* ch)
{
	while(*ch)
		lcddat(*ch++);
}
