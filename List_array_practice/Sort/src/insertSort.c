/*************************************************************************
	> File Name: insertSort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:13:27 AM PDT
 ************************************************************************/
#include "Sort.h"

void insertSort(int *a,int n)
{
	int i, j, k, temp;
	for(i = 1;i <= n; ++i){
		j = i - 1;
		temp = a[i];
		while(j >= 0 && a[j] > temp){
			a[j+1]=a[j];
			--j;
		}
		a[j+1] = temp;
	}
}
