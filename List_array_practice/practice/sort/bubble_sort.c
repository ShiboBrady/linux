/*************************************************************************
	> File Name: bubble_sort.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 11:57:03 PM PDT
 ************************************************************************/

#include "Sort.c"

void bubbleSort(int *a,int n)
{
	int i,up,down,temp;
	while(up<down){
		for(i=up;i<down;++i){
			if(a[i]>a[i+1]){
				temp=a[i];
				a[i]=a[i+1];
				a[i+1]=temp;
			}
		}
		--down;
		for(i=down;i>up;--i){
			if(a[i]<a[i-1]){
				temp=a[i];
				a[i]=a[i-1];
				a[i-1]=temp;
			}
		}
		++up;
	}
}
