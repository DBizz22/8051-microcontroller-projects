#include<reg51.h>
#define PAD P1

sbit r1=P1^0;
sbit r2=P1^1;
sbit r3=P1^2;
sbit r4=P1^3;
sbit c1=P1^4;
sbit c2=P1^5;
sbit c3=P1^6;
sbit c4=P1^7;
char key(void);

char key()
{
	while(c1&&c2&&c3&&c4);
	if(1)
	{
		PAD=0xFE;
		if(c1==0)  
		{
			while(c1==0);
			lcddat('7');
			return '7';
		}
		else if(c2==0)
		{
			while(c2==0);
				lcddat('8');
				return '8';
		}
		else if(c3==0)
		{
			while(c3==0);
				lcddat('9');
				return '9';
		}
		else if(c4==0)
		{
			while(c4==0);
				lcddat('/');
				return '/';
		}
		
		PAD=0xFD;
		if(c1==0)
		{
			while(c1==0);
			lcddat('4');
			return '4';
		}
		else if(c2==0)
		{
			while(c2==0);
				lcddat('5');
				return '5';
		}
		else if(c3==0)
		{
			while(c3==0);
				lcddat('6');
				return '6';
		}
		else if(c4==0)
		{
			while(c4==0);
				lcddat('*');
			return '*';
		}
		
		PAD=0xFB;
		if(c1==0)
		{
			while(c1==0);
			lcddat('1');
			return '1';
		}
		else if(c2==0)
		{
			while(c2==0);
				lcddat('2');
			return '2';
		}
		else if(c3==0)
		{
			while(c3==0);
				lcddat('3');
			return '3';
		}
		else if(c4==0)
		{
			while(c4==0);
				lcddat('-');
			return '-';
		}
		
		PAD=0xF7;
		if(c1==0)
		{
			while(c1==0);
			return 'S';
		}
		else if(c2==0)
		{
			while(c2==0);
				lcddat('0');
				return '0';
		}
		else if(c3==0)
		{
			while(c3==0);
				return '=';
		}
		else if(c4==0)
		{
			while(c4==0);
				lcddat('+');
			return '+';
		}
		
	}
}