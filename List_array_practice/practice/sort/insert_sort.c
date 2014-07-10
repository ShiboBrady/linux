/*************************************************************************
	> File Name: insert_sort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 11:54:10 PM PDT
 ************************************************************************/

#include "Sort.h"


void insertSort(int *a,int n)
{
	int i,j,temp;
	for(i=1;i<n;++i)
	{
		j=i-1;
		temp=a[i];
		while(j>=0&&a[j]>temp){
			a[j+1]=a[j];
			--j;
		}
		a[j+1]=temp;
	}
}
