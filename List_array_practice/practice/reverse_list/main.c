/**************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 06:56:09 PM PDT
 ************************************************************************/

#include "list_struct.h"
#define N 10
int main()
{
	pNode h;
	initList(&h);
	printf("Please enter %d numbers to create list:\n",N);
	int i, elem;
	for(i=0;i<N;++i)
	{
		scanf("%d",&elem);
		insertList(&h, elem);
	}
	showList("Befor reverse",h);
	reverse_list(&h);
	showList("After reverse",h);
	return 0;
}
