#include<reg51.h>
#include "ds18b20.h"
#define DISPLAY P0
#define TIME_H 76
#define TIME_L 0

sbit SET=P3^1;
sbit INC=P3^2;
sbit DEC=P3^3;
sbit BUZZ=P3^4;
sbit LED=P2^0;
sbit A=P3^5;
sbit B1=P3^6;
sbit C=P3^7;
unsigned char sett;
unsigned char num[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x39,0x71};
unsigned int mode;
int limitc1,limitc2,limitf1,limitf2;
void initial();
void display1();
void display2();
void display3();
void delayms();

void main()
{
	initial();
	while(1)
	{
		if(sett==0)
			display1();
		else if(sett==1)
			display2();
		else if(sett==2)
			display3();
		
		if(SET==0)
		{
			while(SET==0);
			sett++;
			if(sett==3)
				sett=0;
		}
	}
}

void initial()
{
	LED=0;
	sett=0;
	limitc1=5;
	limitc2=20;
	limitf1=(limitc1*9)/5+32;
	limitf2=(limitc2*9)/5+32;
	INC=DEC=SET=1;
	A=0;
	B1=0;
	C=0;
	DISPLAY=0;
	temp_f=temp_c=0;
	BUZZ=0;
	mode=0;
	EA=1;
	EX0=1;
	EX1=1;
	ET0=1;
	IT0=1;
	IT1=1;
	TMOD=0x01;
	TH0=TIME_H;
	TL0=TIME_L;
	TR0=1;
}

void incre() interrupt 0
{
	if(sett==0)
	{
			mode++;
			if(mode==2)
				mode=0;
	}
	else if(sett==1)
	{
			limitc1++;
			if(limitc1>=limitc2)
				limitc1=limitc2-1;
			limitf1=(limitc1*9)/5+32;
	}
	else if(sett==2)
	{
			limitc2++;
			if(limitc2>=125)
				limitc2=125;
			limitf2=(limitc2*9)/5+32;
	}
}

void timer0() interrupt 1
{
	Read_Temperature();
	
	if(mode)
	{
		if(temp_f<=limitf1||temp_f>=limitf2)
		{
			BUZZ=1;
			LED=~LED;
		}
		else
		{
			BUZZ=0;
			LED=0;
		}
	}
	else
	{
		if(temp_c<=limitc1||temp_c>=limitc2)
		{
			BUZZ=1;
			LED=~LED;
		}
		else
		{
			BUZZ=0;
			LED=0;
		}
	}

	TH0=TIME_H;
	TL0=TIME_L;
}

void decre() interrupt 2
{
	if(sett==0)
	{
			mode++;
			if(mode==2)
				mode=0;
	}
	else if(sett==1)
	{
			limitc1--;
			if(limitc1<=-55)
				limitc1=-55;
			limitf1=(limitc1*9)/5+32;
	}
	else if(sett==2)
	{
		limitc2--;
		if(limitc2<=limitc1)
			limitc2=limitc1+1;
		limitf2=(limitc2*9)/5+32;
	}
}


void display1()
{
	float temp;
	if(mode)
		temp=temp_f;
	else
		temp=temp_c;
	
			
		DISPLAY=0;
		B1=C=1;
		A=0;
		if( ((int)temp)>=0 )
			DISPLAY=0;
		else
		{
			DISPLAY=0x40;		
			delayms();
			temp=temp*-1;
		}
			
		A=B1=C=0;
		if(mode)
			DISPLAY=num[11];
		else
			DISPLAY=num[10];
		delayms();
		
		DISPLAY=0;
		A=1;
		B1=C=0;
		DISPLAY=0x63;
		delayms();
		
		DISPLAY=0;
		A=C=0;
		B1=1;
		DISPLAY=num[(int)(temp*100)%10];
		delayms();
		
		DISPLAY=0;
		A=B1=1;
		C=0;
		DISPLAY=num[(int)(temp*10)%10];
		delayms();
		
		DISPLAY=0;
		C=1;
		A=B1=0;
		DISPLAY=(num[(int)temp%10])|0x80;
		delayms();
		
		DISPLAY=0;
		if(temp>9)
		{
			A=C=1;
			B1=0;
			DISPLAY=num[(int)(temp*0.1)%10];
			delayms();
		}
		
		if(temp>99)
		{
			DISPLAY=0;
			C=B1=1;
			A=0;
			DISPLAY=num[((int)temp)/100];
			delayms();
		}
}

void display2()
{
		int temp;
		A=B1=C=0;
		if(mode)
		{
				DISPLAY=num[11];
				temp=limitf1;
		}
		else
		{
			DISPLAY=num[10];
			temp=limitc1;
		}
		delayms();
	
		DISPLAY=0;
		C=A=1;
		B1=0;
		if(temp<0)
		{
			DISPLAY=0x40;
			delayms();
			temp=temp*-1;
		}

		
		DISPLAY=0;
		A=1;
		B1=C=0;
	  DISPLAY=0x63;
		delayms();
		
		DISPLAY=0;
		B1=1;
		A=C=0;
		DISPLAY=num[temp%10];
		delayms();
		
		DISPLAY=0;
		A=B1=1;
		C=0;
		DISPLAY=num[(int)(temp*0.1)%10];
		delayms();
		
		DISPLAY=0;
		C=1;
		A=B1=0;
		DISPLAY=num[temp/100];
		delayms();
		
		
		DISPLAY=0;
		C=B1=1;
		A=0;
		DISPLAY=0;
		delayms();
		
		DISPLAY=0;
		A=B1=C=1;
		DISPLAY=0x38;
		delayms();
}

void display3()
{
		int temp;
	
		A=B1=C=0;
		if(mode)
		{
				DISPLAY=num[11];
				temp=limitf2;
		}
		else
		{
				DISPLAY=num[10];
				temp=limitc2;
		}
		delayms();
	
		DISPLAY=0;
		C=A=1;
		B1=0;
		if(temp<0)
		{
			DISPLAY=0x40;
			delayms();
			temp=temp*-1;
		}	

		
		A=1;
		B1=C=0;
		DISPLAY=0x63;
		delayms();
		
		DISPLAY=0;
		B1=1;
		A=C=0;
		DISPLAY=num[temp%10];
		delayms();
		
		DISPLAY=0;
		A=B1=1;
		C=0;
		DISPLAY=num[(int)(temp*0.1)%10];
		delayms();
		
		DISPLAY=0;
		C=1;
		A=B1=0;
		DISPLAY=num[temp/100];
		delayms();
		
		
		DISPLAY=0;
		C=B1=1;
		A=0;
		DISPLAY=0;
		delayms();
		
		DISPLAY=0;
		A=B1=C=1;
		DISPLAY=0x76;
		delayms();
}


void delayms()
{
	int i;
	for(i=0;i<240;i++);
}