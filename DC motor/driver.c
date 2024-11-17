#include<reg51.h>
#define TIME (65536-5000)

sbit power=P1^0;
sbit dir=P1^1;
sbit incr=P3^2;
sbit decr=P3^3;
sbit mot1i=P2^0;
sbit mot1o=P2^1;
sbit pwm1=P2^2;
sbit pwm2=P2^3;
sbit mot2i=P2^4;
sbit mot2o=P2^5;
unsigned int div;

void main()
{
	unsigned int i;
	power=dir=incr=decr=1;
	mot1i=mot1o=pwm1=pwm2=mot2i=mot2o=0;
	EA=1;
	EX0=1;
	EX1=1;
	IT0=1;
	IT1=1;
	TMOD=0x01;
	TH0=TIME/256;
	TL0=TIME%256;
	div=1;
	TR0=1;
	while(1)
	{
		if(~power)
		{
			if(dir)
			{
				mot1i=mot2i=1;
				mot1o=mot2o=0;
			}
			else
			{
				mot1i=mot2i=0;
				mot1o=mot2o=1;
			}
			
			for(i=0;i<=3;i++)
			{
				if(div>i)
				{
					pwm1=pwm2=1;
					while(TF0==0);
					TF0=0;
				}
				else
				{
					pwm1=pwm2=0;
					while(TF0==0);
					TF0=0;
				}
				TH0=TIME/256;
				TL0=TIME%256;
			}
		}
		else
		{
				mot1i=mot1o=pwm1=pwm2=mot2i=mot2o=TR0=0;
				div=1;
				while(power==1);
				TH0=TIME/256;
				TL0=TIME%256;
				TR0=1;
		}
	}
}

void int0() interrupt 0
{
	if(div<4)
		div++;
}

void int1() interrupt 2
{
	if(div>1)
		div--;
}