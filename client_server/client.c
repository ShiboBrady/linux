/*************************************************************************
	> File Name: client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 01 Jul 2014 03:35:56 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>

FILE *fp_server, *fp_write;
char read_file[64], write_file[64], buf_path[256], buf_content[1024];
int my_pid, fd_read, flag;
pthread_t read_tid, write_tid;

void* my_read(void *arg);
void* my_write(void *arg);

int main()
{

	if(!(fp_server = fopen("server.ff", "w"))){
		perror("Cannot open file");
		exit(-1);
	}

	my_pid = getpid();
	sprintf(read_file, "read_%d.fifo", my_pid);
	sprintf(write_file, "write_%d.fifo", my_pid);
	mkfifo(read_file, 0666);
	mkfifo(write_file, 0666);

	fprintf(fp_server, "%d", my_pid);
	fflush(fp_server);

	fd_read = open(read_file, O_RDONLY);
	fp_write = fopen(write_file, "w");
	
	pthread_create(&read_tid, NULL, my_read, NULL);
	pthread_create(&write_tid, NULL, my_write, NULL);

	pthread_join(read_tid, NULL);
	pthread_join(write_tid, NULL);


	return 0;
}

void* my_read(void *arg)
{
	while(memset(buf_content, 0, 1024), read(fd_read, buf_content, 1024) > 0){
		write(1, buf_content, sizeof(buf_content));
	}
	pthread_exit((void *)2);
}

void* my_write(void *arg)
{
	while(memset(buf_path, 0, 256), fgets(buf_path, 256, stdin) != NULL){
		fprintf(fp_write, "%s", buf_path);
		fflush(fp_write);
	}
	pthread_exit((void *) 1);
}
