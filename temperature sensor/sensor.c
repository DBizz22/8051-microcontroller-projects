#include<reg51.h>
#include "lcd4bit.h"
#define DATA P1

sbit RDD=P3^0;
sbit WRD=P3^1;
sbit INTR=P3^2;
void set();
void setTEMP(unsigned char);

void main()
{
	unsigned char temp;
	DATA=0xFF;
	WRD=0;
	RDD=INTR=1;
	lcd_init();
	lcdstr("ROOM TEMPERATURE");
	while(1)
	{
		set();
		temp=DATA;
		setTEMP(temp);
		RDD=1;
	}
}

void set()
{
		WRD=1;
		while(INTR==1);
		WRD=0;
		RDD=0;
}

void setTEMP(unsigned char ch)
{
	unsigned char A,B;
	lcdcmd(0xC6);
	A=(0x30)+(ch/10);
	B=(0x30)+(ch%10);
	lcddat(A);
	lcddat(B);
	lcddat(0xDF);
	lcddat('C');
	delayms(10);
}