/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 10:52:12 PM PDT
 ************************************************************************/

#include<stdio.h>
#define N 20
void showArray(int *a,int n)
{
	int i;
	for(i=0;i<n;++i)
		printf("%d ",a[i]);
	printf("\n");
}

void sort(int *a,int n)
{
	int i,j,k,temp;
	for(i=0;i<n-1;++i){
		k=i;
		for(j=i+1;j<n;++j)
		if(a[k]>a[j])
			k=j;
		if(k!=i){
			temp=a[i];
			a[i]=a[k];
			a[k]=temp;
		}

	}
}
int main()
{
	int a[N],i,j,k;
	printf("Please input %d numbers:\n",N);
	for(i=0;i<N;++i)
		scanf("%d",a+i);
	int n=N;
	printf("Source:\n");
	showArray(a,N);
	sort(a,N);
	for(i=0,j=0;i<N;++i){
		if(a[i]!=a[j]){
			a[++j]=a[i];
		}
	}
	printf("After delete the repeat numbers:\n");
	showArray(a,j+1);
	return 0;
}
