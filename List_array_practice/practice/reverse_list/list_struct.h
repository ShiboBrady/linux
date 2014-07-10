/*************************************************************************
	> File Name: list_struct.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 06:34:46 PM PDT
 ************************************************************************/

#ifndef	LIST_STRUCT_H
#define LIST_STRUCT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
	int data;
	struct ListNode *next;
}Node,*pNode;

void initList(pNode *p);
void insertList(pNode *p, int i);
void showList(char *str, pNode p);
void reverse_list(pNode *p);
#endif
