/*************************************************************************
	> File Name: my_system.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 24 Jun 2014 08:04:31 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("system pid : %d \n", getpid());
	printf("system begin!\n");
	system("./hello world");
	printf("system end!\n");
	return 0;
}
