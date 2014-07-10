/*************************************************************************
	> File Name: list_operation.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 06:37:08 PM PDT
 ************************************************************************/

#include "list_struct.h"

void initList(pNode *h)
{
	*h = NULL;
}

void insertList(pNode *h, int i)
{
	pNode p, q, r;
	r = (pNode)calloc(1, sizeof(Node));
	r->data=i;
	r->next=NULL;
	p = q = *h;
	if(*h == NULL){
		*h = r;
	}else{
			while(p->next&&p->data<i){
				q=p;		
				p=p->next;
			}
			if(p->data>=i){
				if(p==q){

					r->next=*h;				
					*h=r;
				}else{
					
					q->next=r;					
					r->next=p;
				}
			}else{
				p->next=r;
			}
	}
}

void showList(char *str,pNode p)
{
	printf("%s: ",str);
	while(p){
		printf("%d ",p->data);
		p=p->next;
	}
	printf("\n");
}
