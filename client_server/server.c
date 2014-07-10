/*************************************************************************
	> File Name: server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Tue 01 Jul 2014 05:13:11 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void* my_read(void *arg);
int main()
{
	FILE *fp_write;
	int fd_read, fd_server;
	char buf_conn[64];
	pthread_t tid;
	if((fd_server = open("server.ff", O_RDONLY)) == -1){
		perror("Cannot open connection.");
		exit(-1);
	}

	while(1){
		if(read(fd_server, buf_conn, 64) > 0){
			pthread_create(&tid, NULL, my_read, (void*)buf_conn);
		}
	}
	return 0;
}

void* my_read(void *arg)
{
	char *conn = (char*)arg;
	char content[1024], path[256];
	char read_file[64], write_file[64];
	int client_pid;
	FILE *fp_write, *fp_read;
	int fd_read;
	struct stat my_stat;

	client_pid = atoi(conn);
	sprintf(read_file, "write_%d.fifo", client_pid);
	sprintf(write_file, "read_%d.fifo", client_pid);
	
	fp_write = fopen(write_file, "w");
	perror("write");
	fd_read = open(read_file, O_RDONLY);
	perror("read");

	while(memset(path, 0, 256), read(fd_read, path, 256) > 0){
		printf("%s\n", path);
		path[strlen(path) - 1] = 0;	
		printf("size:%d\n", strlen(path));
		stat(path, &my_stat);
		if(my_stat.st_mode & 0040000){
			fprintf(fp_write, "%s", "Is a directory\n");
			fflush(fp_write);
		}
		else if(!(fp_read = fopen(path, "r"))){
			fprintf(fp_write, "%s", "File is not exit\n");
			fflush(fp_write);
		}else{
			while(memset(content, 0, 1024), fgets(content, 1024, fp_read) != NULL){
				fprintf(fp_write, "%s", content);
				fflush(fp_write);
			}
		}
//		memset(content, 0, 1024);
//		fp_read = fopen("client.c", "r");
//		while(memset(content, 0, 1024), fgets(content, 1024, fp_read) != NULL){
//		fprintf(fp_write, "%s", content);
//		fflush(fp_write);
//		}
		
	}
	pthread_exit((void*)1);
}
