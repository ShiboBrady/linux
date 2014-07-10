/*************************************************************************
	> File Name: chooseSort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:24:07 AM PDT
 ************************************************************************/

#include "Sort.h"

void chooseSort(int *a, int n)
{
	int i, j ,k, temp;
	for(i = 0;i < n - 1; ++i){
		k = i;
		for(j = i + 1; j < n; ++j)
			if(a[k] > a[j])
				k = j;
		if(k != i)
			swap(a + i, a + k);
	}
}


