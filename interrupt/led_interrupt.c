#include<reg51.h>
#include<intrins.h>
#define LED_DISPLAY P2
#define uint unsigned int 
#define uchar unsigned char

sbit button1=P3^2;
sbit button2=P3^3;
uint keyvalue;

void delayms(uint);
void int_config();

void main()
{
	keyvalue=0;
	button1=button2=1;
	LED_DISPLAY=0xfe;
	int_config();
	while(1)
	{
		if(keyvalue)
			LED_DISPLAY=_cror_(LED_DISPLAY,1);
		else
			LED_DISPLAY=_crol_(LED_DISPLAY,1);
		delayms(500);
	}
}

void delayms(uint t)
{
	uint i;
	while(t--)
		for(i=120;i>0;i--);
}

void int_config()
{
	IT0=1;
	IT1=1;
	EA=1;
	EX0=1;
	EX1=1;
}

void Int0() interrupt 0
{
	delayms(30);
	if(~button1)
		keyvalue=1;
}

void Int1() interrupt 2
{
	delayms(30);
	if(~button2)
		keyvalue=0;
}