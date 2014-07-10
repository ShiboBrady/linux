/*************************************************************************
	> File Name: main.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 18 Jun 2014 10:12:18 PM PDT
 ************************************************************************/

#include "list_struct.h"
#define N 10

void merge(pNode *list1,pNode list2)
{
	reverse_list(&list2);
	pNode pa1,pa2,pb1,pb2;
	pa1=pa2=*list1;
	pb1=pb2=list2;
	while(pa1 && pb1){
		while(pa1->next&&pa1->data<pb1->data){
			pa2=pa1;
			pa1=pa1->next;
		}
		if(pa1->data>=pb1->data){
			if(pa1==pa2){
				*list1=pb1;
			}else{
				pa2->next=pb1;
			}
			pb1=pb1->next;
			pb2->next=pa1;
			pa1=pa1->next;
			pa2=pb2;
			pb2=pb1;
		}else{
			pa2=pa1;
			pa1=pa1->next;
		}
	}
	if(pa1==NULL&&pb1){
		pa2->next=pb1;
	}
}

int main()
{
	pNode list1,list2;
	initList(&list1);
	initList(&list2);
	int i,elem;
	printf("Please input N numbers to create list1:\n",N);
	for(i=0;i<N;++i){
		scanf("%d",&elem);
		insertList(&list1,elem);
	}
	printf("Please input N numbers to create list2:\n");
	for(i=0;i<N;++i){
		scanf("%d",&elem);
		insertList(&list2,elem);
	}
	reverse_list(&list2);
	showList("Before merge,list1",list1);
	showList("Before merge,list2",list2);
	merge(&list1,list2);
	showList("After merge,List1",list1);
	return 0;
}
