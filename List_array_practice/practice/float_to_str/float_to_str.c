/*************************************************************************
	> File Name: float_to_str.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 01:13:22 AM PDT
 ************************************************************************/

#include "float_to_str.h"


void float_to_str(char *ch,float fl)
{
	char *str=ch;
	if(fl<0)
	{
		*(str++) = '-';
		fl = 0 - fl;
	}

	int integer_part=(int)fl;
	float float_part = fl - integer_part;
	int num[50],i=0;
	char *ch1,*ch2;
	
	printf("%d\n",integer_part);
	printf("%f\n",float_part);
	do
		num[i++]=integer_part%10;
	while(integer_part/=10);
	
	printf("i=%d\n",i);
	for(i=i-1;i>=0;--i){
		*(str++)=num[i]+48;
	
	}
	*str=0;
	*(str++)='.';
	
	int a,b=15;
	do
	{
		float_part*=10;
		a=(int)float_part;
		*(str++)=a+48;
		float_part-=a;
		printf("%d\n",a);
	}while(b--);
	//while(float_part>0);
	*str=0;
	puts(ch);
}
