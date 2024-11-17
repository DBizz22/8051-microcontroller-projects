#include<reg51.h>

void sconfig();
void tdata(char);
void message(unsigned char*);
void delayms(int);

void main()
{
	unsigned char raw[]={"Hello Stranger!. I am Divine."};
	sconfig();
	while(1)
	{
		message(raw);
		tdata(0x0D);
		delayms(1000);
	}
}

void sconfig()
{
	SCON=0x50;
	TMOD=0x20;
	TH1=0xFD;
	TR1=1;
}

void tdata(char d)
{
		SBUF=d;
		while(TI==0);
		TI=0;
}	

void delayms(int count)
{
	int i;
	while(count)
	{
		for(i=0;i<922;i++);
		count--;
	}
}

void message(unsigned char* str)
{
	while(*str)
	{
		tdata(*str);
		str++;
	}
}