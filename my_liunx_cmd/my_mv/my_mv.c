/*************************************************************************
	> File Name: my_mv.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sun 22 Jun 2014 09:41:08 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int fd_read, fd_write, read_n;
	char buf[1024];
	if(argc == 1){
		printf("missing file operand.\n");
		exit(1);
	}
	if(argc == 2){
		printf("missing destination directory operand after %s.\n", argv[1]);
		exit(1);
	}
	if(argc == 3){
		if((fd_read = open(argv[1], O_RDONLY)) == -1){
			printf("Open file %s error.\n ",argv[1]);
			exit(1);
		}	
		if((fd_write = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, 0666)) == -1){
			printf("The file %s is alread exit.\n", argv[2]);
			exit(1);
		}
	}
	else{
		printf("Too much arguments.\n");
		exit(1);
	}
	while((read_n = read(fd_read, buf, 1024)) != 0){
		write(fd_write, buf, read_n);
	}
	close(fd_read);
	close(fd_write);
	if(unlink(argv[1]) == -1){
		unlink(argv[2]);
		perror("mv file fail : ");
		exit(1);
	}
	return 0;
}
