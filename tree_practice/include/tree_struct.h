/*************************************************************************
	> File Name: tree_struct.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 21 Jun 2014 04:03:44 AM PDT
 ************************************************************************/

#ifndef TREE_STRUCT_H
#define TREE_STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
int data;
struct treeNode *lchild;
struct treeNode *rchild;
}treeNode, *treePNode;

typedef struct stack{
treePNode nodeInfo;
struct stack *next;
}*stack;

void tree_recurrence_beOrder(treePNode bt);
void tree_recurrence_preOrder(treePNode bt);
void tree_recurrence_inOrder(treePNode bt);

void Push(stack *s, treePNode node);
void Pop(stack *s);
treePNode Top(stack s);
int empty(stack s);

void createTree(treePNode *bt, int *a, int n);
#endif
