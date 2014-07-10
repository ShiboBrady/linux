/*************************************************************************
	> File Name: create_tree.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 21 Jun 2014 04:25:39 AM PDT
 ************************************************************************/

#include "tree_struct.h"

int insertNode(treePNode *bt, int a)
{
	if(*bt == NULL){
		*bt = (treePNode)calloc(1, sizeof(treeNode));
		(*bt)->data = a;
		(*bt)->lchild = (*bt)->rchild = NULL;
		return 1;
	}
	else{
		if((*bt)->data == a){
			return 0;
		}
		else if((*bt)->data > a){
			return insertNode(&(*bt)->lchild, a);
		}
		else{
			return insertNode(&(*bt)->rchild, a);
		}
	}
}

void createTree(treePNode *bt, int *a, int n)
{
	int i;
	//treePNode bt = *root;
	for(i = 0; i < n; ++i){
		insertNode(bt, a[i]);
	}
}
