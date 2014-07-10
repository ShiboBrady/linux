/*************************************************************************
	> File Name: bubbleSort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 17 Jun 2014 11:46:49 PM PDT
 ************************************************************************/

#include "Sort.h"

void bubbleSort(int *a, int n)
{
	int i, low, high;
	low = 0;
	high = n - 1;
	while(low < high){
		for(i = low; i < high; ++i){
			if(a[i] > a[i + 1])
				swap(a + i, a + i + 1);			
		}
		--high;
		for(i = high; i > low; --i){
			if(a[i] < a[i - 1])
				swap(a + i,a + i - 1);
		}
		++low;
	}
}
