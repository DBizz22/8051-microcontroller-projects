#include<reg51.h>
sbit power=P3^1;
sbit left=P3^2;
sbit right=P3^3;
sbit output=P2^1;
unsigned char turn,wait;

void main()
{
	turn=4;
	wait=0;
	power=1;
	left=right=1;
	output=0;
	EA=1;
	EX0=1;
	EX1=1;
	ET0=1;
	TMOD=0x01;
	IT0=1;
	IT1=1;
	TR0=0;
	while(1)
	{
		if(power)
		{
			output=0;
			TR0=0;
		}
		else
		{
			wait=1;
			TR0=1;
			switch(turn)
			{
				case 0 :	TH0=252;
									TL0=24;
									output=1;
									while(wait);
									TH0=181;
									TL0=200;
									break;
				
				case 1 :	TH0=251;
									TL0=155;
									output=1;
									while(wait);
									TH0=182;
									TL0=69;
									break;
				
				case 2 :	TH0=251;
									TL0=30;
									output=1;
									while(wait);
									TH0=182;
									TL0=194;
									break;
									
				case 3 :	TH0=250;
									TL0=161;
									output=1;
									while(wait);
									TH0=183;
									TL0=63;
									break;
									
				case 4 :	TH0=250;
									TL0=36;
									output=1;
									while(wait);
									TH0=183;
									TL0=188;
									break;
									
				case 5 : 	TH0=249;
									TL0=167;
									output=1;
									while(wait);
									TH0=184;
									TL0=57;
									break;
									
				case 6 : 	TH0=249;
									TL0=42;
									output=1;
									while(wait);
									TH0=184;
									TL0=182;
									break;
									
				case 7 :	TH0=248;
									TL0=173;
									output=1;
									while(wait);
									TH0=185;
									TL0=51;
									break;
									
				case 8 :	TH0=248;
									TL0=48;
									output=1;
									while(wait);
									TH0=185;
									TL0=176;
			}
			wait=1;
			while(wait);
		}
	}
}

void turn_left() interrupt 0
{
	if(turn!=0)
		turn--;
}

void pwm() interrupt 1
{
	output=0;
	wait=0;
}

void turn_right() interrupt 2
{
	turn++;
	if(turn>8)
		turn=8;
}
