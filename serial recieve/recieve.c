#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
#define OUT P2

sbit RS=P2^0;
sbit RW=P2^1;
sbit E=P2^2;
void delayms(uint);
void s_config();
void cmd4(uchar);
void tdata4(uchar);
void string(uchar*);
void cmd(uchar);
void tdata(uchar);
void rdata();
uchar dat;
uint count;

void main()
{
	uint line;
	cmd(0x28);
	cmd(0x01);
	cmd(0x0C);
	cmd(0x80);
	string("RECIEVED MESSAGE");
	cmd(0xC0);
	s_config();
	dat=0;
	count=0;
	line=1;
	while(1)
	{
		rdata();
		if(dat==0x0D||count==16)
		{
			(line==0)?cmd(0xc0):cmd(0x80);
			line=++line%2;
			count=0;
			if(dat!=0x0D)
				tdata(dat);
		}
		else if(dat=='1')
		{
			cmd(0x01);
			cmd(0x80);
			line=0;
			count=0;
		}
		else
			tdata(dat);
		delayms(1);
	}
}

void delayms(uint t)
{
	uint i;
	while(t)
	{
		for(i=0;i<922;i++);
		t--;
	}
}

void s_config()
{
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
}

void cmd(uchar ch)
{
	cmd4(ch&0xf0);
	cmd4((ch<<4)&0xf0);
}

void rdata()
{
	while(RI==0);
	dat=SBUF;
	RI=0;
}

void tdata(uchar ch)
{
	tdata4(ch&0xF0);
	tdata4((ch<<4)&0xF0);
	count++;
}

void string(uchar* str)
{
	while(*str)
	{
		tdata(*str++);
	}
}

void cmd4(uchar ch)
{
	OUT=ch;
	RS=0;
	RW=0;
	E=1;
	delayms(1);
	E=0;
}

void tdata4(uchar ch)
{
	OUT=ch;
	RS=1;
	RW=0;
	E=1;
	delayms(1);
	E=0;
}