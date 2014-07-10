/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 12:53:49 AM PDT
 ************************************************************************/

#include "Sort.h"

int main()
{
	int i, a[N];

	init(a, N);
	printf("Source:\n");
	show(a, N);

	init(a, N);
	printf("Quick Sort:\n");
	quickSort(a, N);
	show(a, N);

	init(a, N);
	printf("Choose Sort:\n");
	chooseSort(a, N);
	show(a, N);

	init(a, N);
	printf("Insert Sort: \n");
	insertSort(a, N);
	show(a, N);

	init(a, N);
	printf("Bubble Sort: \n");
	bubbleSort(a, N);
	show(a, N);
	
	return 0;
}

