/*************************************************************************
	> File Name: my_mkdir.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 07:16:34 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argv, char *argc[])
{
	if(argv == 0){
		printf("Too few argument.\n");
	}
	else{
		if((mkdir(argc[1], 0777)) != 0){
			perror("Make directory fail:");
		}
	}
	return 0;
}
