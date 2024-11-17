#include<reg51.h>
#define DISPLAY P0

sbit button=P3^2;
char nums[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int i=0;

void main()
{
	EA=1;
	EX0=1;
	IT0=1;
	P2=0;
	button=1;
	DISPLAY=nums[i];
	while(1);
}

void int0() interrupt 0
{
	i++;
	if(i==10)
		i=0;
	DISPLAY=nums[i];
}