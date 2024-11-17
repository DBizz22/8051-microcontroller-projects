#include<reg51.h>
#include<intrins.h>
#define uint unsigned int

sbit s=P1^0;
uint nums[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};

void delayms(uint t)
{
	uint i;
	while(t--)
		for(i=120;i>0;i--);
}

void main()
{
	uint i=0;
	s=1;
	while(1)
	{
		if(s==0)
		{
			P0=nums[i];
			delayms(1000);
			i=(i+1)%10;
		}
		else
			P0=0x00;
	}
}