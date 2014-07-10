/*************************************************************************
	> File Name: ls_as_tree.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 24 Jun 2014 07:49:57 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

#define PATH_SIZE 1000

void printdir(char *path, int depth)
{
	DIR *dir;
	struct dirent *reader;
	struct stat my_stat; 
	char new_path[PATH_SIZE];
	dir = opendir(path);
	if(dir == NULL){
		perror("Open dir wrong: ");
		exit(1);
	}
	chdir(path);
	while((reader = readdir(dir)) != NULL){
		if(!(strncmp(reader->d_name, ".", 1) == 0 || strncmp(reader->d_name, "..", 2) == 0)){
			stat(reader->d_name, &my_stat);
			if(my_stat.st_mode & 0040000){
				printf("%*c%s\n",depth, 32, reader->d_name);
				printdir(reader->d_name, depth + 4);
			}
			else{
				printf("%*c%s\n", depth, 32, reader->d_name);
			}
		}
	}
	chdir("..");
	closedir(dir);
}	

int main(int argc, char *argv[])
{
	char *path, pwd[2] = ".";
	if(argc == 1){
		path = pwd;
	}
	else{
		path = argv[1];
	}

	printdir(path, 0);
	return 0;
}
