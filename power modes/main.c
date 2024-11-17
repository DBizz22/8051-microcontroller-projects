#include<reg51.h> 
sbit light=P2^0;
sbit button=P3^0;
sbit idl=P1^0;
sbit pwrd=P1^1;

void main()
{
	PCON=0;
	idl=pwrd=button=1;
	light=0;
	while(1)
	{
		if(button)
			light=0;
		else
			light=1;
		
		if(idl)
			PCON=PCON|0x00;
		else
			PCON=0x01;
		
		if(pwrd)
			PCON=PCON|0x00;
		else
			PCON=0x02;
	}
}