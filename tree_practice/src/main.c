/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 21 Jun 2014 04:24:13 AM PDT
 ************************************************************************/

#include "tree_struct.h"
#define N 10
void test(treePNode bt)
{
	if(bt != NULL){
		test(bt->lchild);
		test(bt->rchild);
		printf("%d ", bt->data);
	}
	printf("\n");
}
int main()
{
	treePNode bt = NULL;
	int i, a[N];
	printf("Please input %d tree nodes:\n");
	for(i = 0; i < N; ++i){
		scanf("%d", a+i);
	}
	createTree(&bt, a, N);
	printf("The beOrder is: \n");
	tree_recurrence_beOrder(bt);
	tree_recurrence_preOrder(bt);
	tree_recurrence_inOrder(bt);
	return 0;
}
