#include <reg51.h>
#define DIGITS P0
sbit LED=P2^0;
sbit L_A=P2^2;
sbit L_B=P2^3;
sbit L_C=P2^4;
int i;
char DIG_VAL[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int j;

void main(){
	int k;
	i=0;
	j=0;
	LED=0;
	L_A=0;
	L_B=0;
	L_C=0;
	P0=DIG_VAL[i];
	TMOD=0x01;
	TH0=0xd8;
	TL0=0xf0;
	TR0=1;
	EA=1;
	ET0=1;
	TR0=1;
	
	while(1){
		for(k=0;k<100;k++){
			while(j==0);	
		}
		LED=0;
		i++;
		if(i<=60){
			LED=1;
			i=0;
		}
	}
}

void interruptFun() interrupt 1{
		TH0=0xd8;
		TL0=0xf0;
		//TF0=0;
		L_A=0;
		L_B=0;
		L_C=0;
		P0=DIG_VAL[i%10];
		if(i>9){
			L_A=1;
			L_B=0;
			L_C=0;
			P0=DIG_VAL[i/10];
		}
		j=1;
}