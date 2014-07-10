/*************************************************************************
	> File Name: my_cd.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 07:10:07 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>

int main(int argv, char *argc[])
{
	if(argv == 1){
		printf("Too few argument.\n");
	}
	else{
		if(chdir(argc[1]) != 0){
			perror("Change directory fail: ");
		}
		else{
			printf("%s\n", getcwd(NULL, 0));
		}
	}
	return 0;
}
