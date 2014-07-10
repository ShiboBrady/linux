/*************************************************************************
	> File Name: my_pwd.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 06:57:10 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(int argv, char *argc[])
{
	printf("The current directory is: %s\n", getcwd(NULL, 0));
	return 0;
}
