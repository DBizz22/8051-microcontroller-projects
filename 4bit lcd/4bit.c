#include<reg51.h>
#define uchar unsigned char
	
sbit rs=P2^0;
sbit rw=P2^1;
sbit E=P2^2;
void delayms(unsigned int);
void lcdcmd(uchar);
void cmd1(uchar);
void lcddat(uchar);
void dat1(uchar);
void lcdstr(char*);

void main()
{
	char word1[]={"Hello world!!."};
	char word2[]={" I am BIZZ."};
	E=1;
	lcdcmd(0x28);
	lcdcmd(0x01);
	lcdcmd(0x0c);
	lcdcmd(0x8f);
	lcdstr(word1);
	lcdstr(word2);
	while(1)
	{
		lcdcmd(0x18);
	}
}

void delayms(unsigned int t)
{
	int i;
	while(t--)
		for(i=120;i>0;i--);
}

void lcdcmd(uchar c)
{
	uchar nib=(c&0xf0);
	cmd1(nib);
	nib=(c<<4)&0xf0;
	cmd1(nib);
}

void cmd1(uchar c)
{
	P2=c;
	rs=0;
	rw=0;
	E=1;
	delayms(100);
	E=0;
}

void lcddat(uchar c)
{
	uchar nib=(c&0xf0);
	dat1(nib);
	nib=(c<<4)&0xf0;
	dat1(nib);
}

void dat1(uchar c)
{
	P2=c;
	rs=1;
	rw=0;
	E=1;
	delayms(100);
	E=0;
}

void lcdstr(char* str)
{
	while(*str)
	{
		lcddat(*str);
		str++;
	}
}