#include<reg51.h>
#include<stdio.h>
#include<stdlib.h>
#include "lcd4bit.h"
#include "s_calc_key.h"

char opr1,opr2;
	
void main()
{
	int num,op1,op2,ans;
	char ch;
	char input[8],disp[8];
	int n,op_no; 
	num=op1=op2=ans=op_no=0;
	n=0;
	lcd_init();
	while(1)
	{
		PAD=0xF0;
		ch=key();
		num++;
		if(ch=='*'||ch=='/'||ch=='+'||ch=='-'||ch=='=')
		{
			op_no++;
			if(op_no==1)
			{
				op1=atoi(input);
				opr1=ch;
			}
			else if(op_no>=2)
			{
				op2=atoi(input);
				opr2=ch;
			}
			n=0;
		}
		else
		{
			input[n]=ch;
			input[n+1]='\0';
			n++;
		}
		
		if(ch=='='||op_no>=2)
		{
			switch(opr1)
			{
				case '*'	:	ans=op1*op2;
										break;
				case '/'	: ans=op1/op2;
										break;
				case '+'	: ans=op1+op2;
										break;
				case '-'	: ans=op1-op2;
										break;
			}
			
			if(ch=='=')
			{
				lcdcmd(0xC0);
				lcdstr("Ans = ");
				sprintf(disp,"%d",ans);
				lcdstr(disp);
			}
			else
			{
				op1=ans;
				opr1=opr2;
				op_no=1;
			}
			n=0;
		}
		if(ch=='S'||num>16)
		{
			if(num>16)
			{
				lcdcmd(0xC0);
				lcdstr("Input Error");
				delayms(1000);
			}
			num=op1=op2=ans=op_no=0;
			lcdcmd(0x01);
			lcdcmd(0x80);
		}
	}
	
}



