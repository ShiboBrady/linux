/*************************************************************************
	> File Name: my_ls.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 09:49:56 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *dirent;
	if(argc == 1)
	{
		argv[1] = ".";
	}
	else{
		dir = opendir(argv[1]);
		while((dirent = readdir(dir)) != NULL){
			printf("Type:%c\tSize:%d\t\tName:%s\n",dirent->d_type,dirent->d_reclen,dirent->d_name);
		}
	}
	closedir(dir);
	return 0;
}
