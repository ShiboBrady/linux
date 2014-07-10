/*************************************************************************
	> File Name: init.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:55:28 AM PDT
 ************************************************************************/

#include "Sort.h"

void init(int *a, int n)
{
	int i;
	for(i = 0; i < n; ++i)
		scanf("%d", a + i);
}

