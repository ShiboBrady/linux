/*************************************************************************
	> File Name: quick_sort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 11:26:08 PM PDT
 ************************************************************************/

#include "Sort.h"


void partable(int *a,int n)
{
	int low=0;
	int high=n-1;
	int temp=a[low];
	while(low<high){
		while(low<high &&　a[high]>temp)
			--high;
		if(low<high)
			a[low]=a[high];
		while(low<high && a[low]<temp)
			++low;
		if(low<high)
			a[high]=a[low];
	}
	a[high]=temp;
	return high;
}

void quickSort(int *a,int n)
{
	int position;
	int i,j;
	if(n>0){
		position=partable(a,0,n);
		quickSort(a,position);
		quickSort(a+position+1,n-position-1);
	}
}
