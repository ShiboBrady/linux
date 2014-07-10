/*************************************************************************
	> File Name: quickSort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 17 Jun 2014 11:06:00 PM PDT
 ************************************************************************/

#include "Sort.h"


int partable(int *a, int n)
{
	int low, high, temp;
	low = 0;
	high = n - 1;
	temp = a[low];
	while(low < high){
		while(low < high && a[high] >= temp)
			--high;
		if(low < high)
			a[low] = a[high];
		while(low < high && a[low] < temp)
			++low;
		if(low < high)
			a[high] = a[low];
	}
	a[high] = temp;
	return high;
}
void quickSort(int *a,int n)
{
	int position;
	if(n > 0){
		position = partable(a, n);
		quickSort(a, position);
		quickSort(a + position + 1, n - position -1);
	}
}
