#include<reg51.h>
#define DISPLAY P2

sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
void delayms(int);
void lcdcmd(char);
void lcddat(char);
void lcdstr(char*);
void cmd(char);
void dat(char);

void lcd_init();


void delayms(int t)
{
	int i;
	while(t--)
	{
		for(i=0;i<120;i++);
	}
}

void lcdcmd(char c)
{
	cmd(c&0xF0);
	cmd((c<<4)&0xF0);
}

void cmd(char c)
{
	DISPLAY=c;
	RS=0;
	RW=0;
	E=1;
	delayms(1);
	E=0;
}

void lcddat(char d)
{
	dat(d&0xF0);
	dat((d<<4)&0xF0);
}

void dat(char d)
{
	DISPLAY=d;
	RS=1;
	RW=0;
	E=1;
	delayms(1);
	E=0;
}

void lcd_init()
{
	lcdcmd(0x28);
	lcdcmd(0x01);
	lcdcmd(0x0C);
	lcdcmd(0x80);
}

void lcdstr(char* str)
{
	int y;
	y=0;
	while(str[y])
	{
		lcddat(str[y]);
		y++;
	}
}


