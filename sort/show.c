/*************************************************************************
	> File Name: show.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:56:59 AM PDT
 ************************************************************************/

#include "Sort.h"

void show(int *a, int n)
{
	int i;
	for(i = 0; i < n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}


