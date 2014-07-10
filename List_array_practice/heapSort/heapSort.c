/*************************************************************************
	> File Name: heapSort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 06:18:37 PM PDT
 ************************************************************************/

#include "Heap_Sort.h"

void heapInsert(int *a, int l, int n)
{
	int i = l, j = i * 2, temp = a[l];
	while(j <= n){
		if(j < n && a[j] < a[j + 1])
			++j;
		if(temp < a[j]){
			a[j] = a[i];
			i = j;
			j *= 2;
		}else{
			break;
		}
	}
	a[i] = temp;
}

void heapSort(int *a, int n)
{
	int i, temp;
	for(i = n / 2; i >= 1; ++i){
		heapInsert(a, i, n);
	}
	for(i = n; i > 1; --i){
		a[0] = a[i];
		a[i] = a[1];
		a[1] = a[0];
		heapInsert(a, 1, i - 1);
	}
}
