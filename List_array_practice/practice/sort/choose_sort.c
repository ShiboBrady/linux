/*************************************************************************
	> File Name: choose_sort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 12:00:56 AM PDT
 ************************************************************************/

#include "Sort.h"

void chooseSort(int *a,int n)
{
	int i,j,k,temp;
	for(i=0;i<n-1;++i){
		k=i;
		for(j=i+1;j<n;++j){
			if(a[k]>a[j])
				k=j;
		}
		if(k!=i){
			temp=a[i];
			a[i]=a[k];
			a[k]=temp;
		}
	}
}
