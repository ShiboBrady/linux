/*************************************************************************
	> File Name: w_popen_study.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 07:35:48 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	char buf[1024];
	fp = popen("./reverse", "w");
	if(fp == NULL){
		perror("popen: ");
		exit(1);
	}
	while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
		if(buf[0] != '\n'){
			fputs(buf, fp);
			fflush(fp);
		}
	}
	pclose(fp);
	return 0;
}
