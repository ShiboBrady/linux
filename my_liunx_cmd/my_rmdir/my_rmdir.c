/*************************************************************************
	> File Name: my_rmdir.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 07:22:27 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>

int main(int argv, char *argc[])
{
	if(argv == 1){
		printf("Too few argument.\n");
	}
	else{
		if((rmdir(argc[1])) != 0){
			perror("Doesn't remove dirctory: ");
		}
	}
	return 0;
}
