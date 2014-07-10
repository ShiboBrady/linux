/*************************************************************************
	> File Name: my_ls_l.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 19 Jun 2014 09:49:56 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
void authorityProcess(char *str, int auth);
void timeProcess(char *p_time, char *time);

int main(int argc, char *argv[])
{
	DIR *dir;
	struct dirent *reader;
	struct stat fileInfo;
	char str[11];
	char time[1024];
	char userInput[1024];
	char newPath[1024];
	if(argc == 1){
		dir = opendir(".");
		strcpy(userInput, "./");
	}
	else{
		dir = opendir(argv[1]);
		strcpy(userInput, argv[1]);
		strcat(userInput, "/");
//		chdir(argv[1]);
	}
	if(dir == NULL){
		perror("Open file error : ");
		exit(-1);
	}
	printf("mode    nlink  user  group  size      atime    name \n");
	while((reader = readdir(dir)) != NULL){
		memset(newPath,0,1024);
		strcpy(newPath, userInput);
		strcat(newPath, reader->d_name);
		if(strncmp(reader->d_name, ".", 1) != 0 && strncmp(reader->d_name, "..", 2) != 0){
			memset(&fileInfo, 0, sizeof(fileInfo));
			stat(newPath, &fileInfo);
			authorityProcess(str, fileInfo.st_mode);
			timeProcess(time, ctime(&fileInfo.st_atime));
			printf("%s %3d %5s %5s %6d %15s %s\n",str, fileInfo.st_nlink, getpwuid(fileInfo.st_uid)->pw_name, getgrgid(fileInfo.st_gid)->gr_name,fileInfo.st_size, time, reader->d_name);
		}
	}
	closedir(dir);
	return 0;
}

void authorityProcess(char *str, int auth)
{
	strcpy(str, "----------");
	if(auth & 0040000){
		str[0] = 'd';
	}
	if(auth & 0000400){
		str[1] = 'r';
	}
	if(auth & 0000200){
		str[2] = 'w';
	}
	if(auth & 0000100){
		str[3] = 'x';
	}
	if(auth & 0000040){
		str[4] = 'r';
	}
	if(auth & 0000020){
		str[5] = 'w';
	}
	if(auth & 0000010){
		str[6] = 'x';
	}
	if(auth & 0000004){
		str[7] = 'r';
	}
	if(auth & 0000002){
		str[8] = 'w';
	}
	if(auth & 0000001){
		str[9] = 'x';
	}
}

void timeProcess(char *p_time, char *time)
{
	strcpy(p_time, time+4);
	int count=0;
	while(count != 2 && *p_time != 0){
		if(*p_time == ':')
			++count;
		++p_time;
	}
	*(p_time-1) = '\0';
}
