/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 08:15:18 PM PDT
 ************************************************************************/

#include "list_struct.h"
#define N 10

void fun(pNode *list1,pNode *list2)
{
	pNode p1,p2,q;
	p1=p2=*list1;
	q=*list2;
	while(q){
			p1=p2=*list1;
			while(p1->next && p1->data!=q->data){
				p2=p1;
				p1=p1->next;
			}
			if(p1->data==q->data){


				if(p1==p2){
					*list1=(*list1)->next;
				}else{
					p2->next=p1->next;
				}
			}
			q=q->next;
	}
}
int main()
{

	pNode list1,list2;
	initList(&list1);
	initList(&list2);
	printf("Please input %d numbers in list:\n",N);
	int i, elem;
	for(i=0;i<N;++i)
	{
		scanf("%d",&elem);
		insertList(&list1,elem);
	}
	showList("List1",list1);
	printf("Please input %d numbers in list2:\n");
	for(i=0;i<N;++i){
		scanf("%d",&elem);
		insertList(&list2,elem);
	}
	showList("List2",list2);
	fun(&list1,&list2);
	showList("After delete",list1);
	return 0;
}
