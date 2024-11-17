#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char	

sbit button=P1^7;
sbit rs=P3^0;
sbit rw=P3^1;
sbit E=P3^2;
uint done;
char digits[]={"0123456789"};
void delayms(uint);
void lcdcmd(uchar);
void lcddat(uchar);
void lcdstr(uchar*);
void display(uint,uint,uint);

void main()
{
	uint t;
	uint hr,min,sec;
	char text1[]={"MY CLOCK"};
	char text2[]={"00HR:00MIN:00SEC"};
	hr=min=sec=0;
	P2=0x00;
	TMOD=0x01;   //timer config
	TL0 = 0xF0;				//Initial timer value							
	TH0 = 0xD8;				//Initial timer value								
	EA=1;
	ET0=1;
	rs=rw=E=button=0;
	lcdcmd(0x01);
	lcdcmd(0x0c);
	lcdcmd(0x38);
	lcdcmd(0x84);
	lcdstr(text1);
	lcdcmd(0xc0);
	lcdstr(text2);
	done=1;
	TF0 = 0;				//Clear TF1 flag
	TR0=1;  //start timer
	while(1)
	{
		if(~button)
		{
			TR0=1;
			display(hr,min,sec);
			for(t=100;t>0;t--)
			{
				while(done);
				done=1;
			}
			sec++;
			if(sec==60)
			{
				min=min+1;
				sec=0;
			}
			if(min==60)
			{
				hr=hr+1;
				min=0;
			}
			if(hr==24)
				hr=0;
		}
		else
		{
			TR0=0;
		}
	}
	return;
}

void delayus(uint i)
{
	uint j;
	while(i--)
	{
		for(j=120;j>0;j--);
	}
}


void lcdcmd(uchar cmd)
{
	P2=cmd;
	rs=0;
	rw=0;
	E=1;
	delayus(1);
	E=0;
}

void lcddat(uchar dat)
{
	P2=dat;
	rs=1;
	rw=0;
	E=1;
	delayus(1);
	E=0;
}

void lcdstr(uchar* str)
{
	while(*str)
	{
		lcddat(*str);
		str++;
	}
}

void display(uint hr,uint min,uint sec)
{
	
	lcdcmd(0xc0);
	lcddat(digits[hr/10]);
	lcddat(digits[hr%10]);
	lcdcmd(0xc5);
	lcddat(digits[min/10]);
	lcddat(digits[min%10]);
	lcdcmd(0xcb);
	lcddat(digits[sec/10]);
	lcddat(digits[sec%10]);
}

void int0() interrupt 1
{
	TL0 = 0xF0;		//reload timer
	TH0 = 0xD8;
	done=0;
	return;
}
