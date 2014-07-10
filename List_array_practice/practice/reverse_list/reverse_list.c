/*************************************************************************
	> File Name: reverse_list.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 06:32:22 PM PDT
 ************************************************************************/

#include "list_struct.h"

void reverse_list(pNode *h)
{
	pNode p, q, r;
	if(*h == NULL||(*h)->next==NULL)
		return;
	q=NULL;
	r=*h;
	p=(*h)->next;
	while(p){
		r->next=q;
		q=r;
		r=p;
		p=p->next;
	}
	r->next=q;
	*h=r;
}

