/****************vs*********************************************************
	> File Name: tree_struct.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 21 Jun 2014 04:06:07 AM PDT
 ************************************************************************/

#include "tree_struct.h"

void Push(stack *s, treePNode node)
{
	stack new_node = (stack)calloc(1, sizeof(struct stack));
	new_node->nodeInfo = node;
	new_node->next = *s;
	*s = new_node;
}

void Pop(stack *s)
{
	stack p = *s;
	*s = p->next;
	free(p);
}

treePNode Top(stack s)
{
	return s->nodeInfo;
}

int empty(stack s)
{
	if(s == NULL){
		return 1;
	}
	else{
		return 0;
	}
}
