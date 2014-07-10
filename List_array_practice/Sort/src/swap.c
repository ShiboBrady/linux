/*************************************************************************
	> File Name: swap.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:48:43 AM PDT
 ************************************************************************/

#include<stdio.h>

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
