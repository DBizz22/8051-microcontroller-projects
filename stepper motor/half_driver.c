#include<reg51.h>

sbit power=P1^0;
sbit dir=P1^1;
sbit spd_up=P3^2;
sbit spd_dwn=P3^3;
sbit A=P2^0;
sbit B1=P2^1;
sbit C=P2^2;
sbit D=P2^3;
unsigned int spd,step;
void delayms(unsigned int);

void main()
{
	power=dir=spd_up=spd_dwn=1;
	A=B1=C=D=0;
	step=1;
	spd=500;
	EA=1;
	EX0=1;
	EX1=1;
	IT0=1;
	IT1=1;
	while(1)
	{
		if(~power)
		{
			if(step==1)
			{
				B1=C=D=0;
				A=1;
			}
			else if(step==2)
			{
				C=D=0;
				A=B1=1;
			}
			else if(step==3)
			{
				A=C=D=0;
				B1=1;
			}
			else if(step==4)
			{
				A=D=0;
				B1=C=1;
			}
			else if(step==5)
			{
				A=B1=D=0;
				C=1;
			}
			else if(step==6)
			{
				A=B1=0;
				C=D=1;
			}
			else if(step==7)
			{
				A=B1=C=0;
				D=1;
			}
			else if(step==8)
			{
				B1=C=0;
				D=A=1;
			}
			delayms(spd);
			
			if(dir)
			{
				step++;
				if(step>8)
					step=1;
			}
			else
			{
				step--;
				if(step<1)
					step=8;
			}
		}
		else
		{
			A=B1=C=D=0;
			while(power);
		}
	}
}

void delayms(unsigned int t)
{
	unsigned int i;
	while(t--)
	{
		for(i=0;i<120;i++);
	}
}

void int0() interrupt 0
{
	if(spd>50)
		spd=spd-50;
}	

void int1() interrupt 2
{
	if(spd<500)
		spd=spd+50;
}