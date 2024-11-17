#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char 
#define speed1 1000
#define speed2 500
#define speed3 100
	
sbit led_s1=P2^0;
sbit led_s2=P2^1;
sbit config=P2^2;
sbit freq=P2^3;
unsigned int s_freq=0;
unsigned int s_config=1;
uint temp_l1,temp_l2;

int delayms(uint);
int delay();
void config1();
void config2();
void config3();


void main()
{
	P1=0x00;
	P2=0x0f;
	while(1)
	{
		if(~led_s1|~led_s2)
		{
			temp_l1=led_s1;
			temp_l2=led_s2;
			if(~config)
			{
				s_config++;
				if(s_config>3)
					s_config=1;
				while(~config);
			}
			switch(s_config)
			{
				case 1:	config1();
								break;
				case 2:	config2();
								break;
				case 3:	config3();
			}
		}
		else
			P1=0x00;
	}
}

int delayms(uint t)
{
	uint i;
	while(t--)
	{
		for(i=120;i>0;i--);
		if(led_s1==!temp_l1|led_s2==!temp_l2|config==0)
				return 1;
	}
	return 0;
}

int delay()
{
	uint s=0;
		if(~freq)
		{
			s_freq++;
			if(s_freq>2)
				s_freq=0;
			while(~freq);
		}
		if(s_freq==0)
			s=speed1;
		else if(s_freq==1)
			s=speed2;
		else
			s=speed3;
		if(delayms(s))
			return 1;
		return 0;
}

void config1()
{
	if(~led_s1&~led_s2)
	{
		P1=0x01;if(delay())return;P1=0x03;if(delay())return;
		P1=0x07;if(delay())return;P1=0x0f;if(delay())return;
		P1=0x1f;if(delay())return;P1=0x3f;if(delay())return;
		P1=0x7f;if(delay())return;P1=0xff;if(delay())return; 
	}
	else if(~led_s1)
	{
		P1=0x01;if(delay())return;P1=0x03;if(delay())return;
		P1=0x07;if(delay())return;P1=0x0f;if(delay())return;
	}
	else if(~led_s2)
	{
		P1=0x10;if(delay())return;P1=0x30;if(delay())return;
		P1=0x70;if(delay())return;P1=0xf0;if(delay())return;
	}
	P1=0x00;
	delay();
}

void config2()
{
	if(~led_s1&~led_s2)
	{
		P1=0x01;if(delay())return;P1=0x11;if(delay())return;
		P1=0x13;if(delay())return;P1=0x33;if(delay())return;
		P1=0x37;if(delay())return;P1=0x77;if(delay())return;
		P1=0x7f;if(delay())return;P1=0xff;if(delay())return;
	}
	else if(~led_s1)
	{
		P1=0x01;if(delay())return;P1=0x09;if(delay())return;
		P1=0x0b;if(delay())return;P1=0x0f;if(delay())return;
	}
	else if(~led_s2)
	{
		P1=0x10;if(delay())return;P1=0x90;if(delay())return;
		P1=0xb0;if(delay())return;P1=0xf0;if(delay())return;
	}
	P1=0x00;
	delay();
}

void config3()
{
	if(~led_s1&~led_s2)
	{
		P1=0x01;if(delay())return;P1=0x02;if(delay())return;
		P1=0x04;if(delay())return;P1=0x08;if(delay())return;
		P1=0x10;if(delay())return;P1=0x20;if(delay())return;
		P1=0x40;if(delay())return;P1=0x80;if(delay())return;
	}
	else if(~led_s1)
	{
		P1=0x01;if(delay())return;P1=0x02;if(delay())return;
		P1=0x04;if(delay())return;P1=0x08;if(delay())return;
	}
	else if(~led_s2)
	{
		P1=0x10;if(delay())return;P1=0x20;if(delay())return;
		P1=0x40;if(delay())return;P1=0x80;if(delay())return;
	}
	P1=0x00;
	delay();
}
