/*************************************************************************
	> File Name: my_cat.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 24 Jun 2014 08:17:52 PM PDT
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i;
	char param[128] = "cat";
	if(argc == 1){
		system(param);
	}
	else{
		for(i = 1; i < argc; ++i){
			strcat(param, " ");
			strcat(param, argv[i]);
		}
		system(param);
	}
	return 0;
}
