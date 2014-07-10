/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 08:35:13 PM PDT
 ************************************************************************/

#include "list_struct.h"
#define N 10
void fun(pNode *list1,pNode *list2)
{
	pNode p1,p2,q1,q2;
	p1=p2=*list1;
	while(p1){
		if((p1->data)%2==0){
			if(p1==p2){
				if(q1==NULL){

			
					*list2=*list1;
					q1=*list2;
				}
				else{
					
					
					q1->next=*list1;
					q1=q1->next;					
				}
				*list1=(*list1)->next;
				p1=p2=*list1;	
				q1->next=NULL;
			}else{	
				if(q1==NULL){
					*list2=p1;
					q1=*list2;
				}else{
					q1->next=p1;
					q1=q1->next;
				}
				p2->next=p1->next;
				p1=p1->next;
				q1->next=NULL;
			}
		}else{
			p2=p1;
			p1=p1->next;
		}
	}
	p2->next=NULL;
}

int main()
{
	pNode list1,list2;
	initList(&list1);
	initList(&list2);
	printf("Please input %d numbers to create list:\n",N);
	int i,elem;
	for(i=0;i<N;++i)
	{
		scanf("%d",&elem);
		insertList(&list1,elem);
	}

	showList("Before split",list1);
	fun(&list1,&list2);
	showList("After split,List1",list1);
	showList("After split,List2",list2);
	return 0;
}

