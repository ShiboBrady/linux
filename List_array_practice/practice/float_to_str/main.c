/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 01:48:29 AM PDT
 ************************************************************************/

#include "float_to_str.h"

int main()
{
	float f;
	char float_str[30];
	memset(float_str,0,30);
	printf("Please input a float.\n");
	scanf("%f",&f);
	float_to_str(float_str, f);
	printf("The string is:\n");
	puts(float_str);
	return 0;
}
