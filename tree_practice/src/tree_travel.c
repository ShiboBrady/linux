/*************************************************************************
	> File Name: tree_travel.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 21 Jun 2014 03:32:57 AM PDT
 ************************************************************************/

#include "tree_struct.h"

void tree_recurrence_beOrder(treePNode bt)
{
	stack s;
	treePNode pre, cur;
	s = NULL;
	Push(&s, bt);
	pre = NULL;
	while(!empty(s)){
		cur = Top(s);
		if((cur->lchild == NULL && cur->rchild == NULL) || (pre != NULL && (pre == cur->lchild || pre == cur->rchild))){
			printf("%d ", cur->data);
			Pop(&s);
			pre = cur;
		}
		else{
			if(cur->rchild != NULL){
				Push(&s, cur->rchild);
			}
			if(cur->lchild != NULL){
				Push(&s, cur->lchild);
			}
		}
	}
	printf("\n");
}

void tree_recurrence_preOrder(treePNode bt)
{
	stack s = NULL;
	while(!empty(s) || bt != NULL){
		while(bt != NULL){
			printf("%d ", bt->data);
			Push(&s, bt);
			bt = bt->lchild;
		}
		if(!empty(s)){
			bt = Top(s);
			Pop(&s);
			bt = bt->rchild;
		}
	}
	printf("\n");
}

void tree_recurrence_inOrder(treePNode bt)
{
	stack s = NULL;
	while(!empty(s) || bt != NULL){
		while(bt != NULL){
			Push(&s, bt);
			bt = bt->lchild;
		}	
		if(!empty(s)){
			bt = Top(s);
			printf("%d ", bt->data);
			Pop(&s);
			bt = bt->rchild;
		}
	}
	printf("\n");
}
