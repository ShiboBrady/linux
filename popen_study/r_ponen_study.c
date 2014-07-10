/*************************************************************************
	> File Name: popen_study.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 06:35:06 PM PDT
 ************************************************************************/

#include<stdio.h>

int main()
{
	FILE *fp;
	int read_n;
	char buf[1024];
	fp = popen("ls -l", "r");
	read_n = fread(buf, 1, 1024, fp);
	printf("%s\n", buf);
	return 0;
}
