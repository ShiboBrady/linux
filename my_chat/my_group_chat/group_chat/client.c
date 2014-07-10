/*************************************************************************
	> File Name: client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Fri 27 Jun 2014 01:57:48 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	if(argc == 1){
		printf("There is no connection infomation.\n");
		exit(-1);
	}
	FILE *fp_server, *fp_write;
	int fd_read, client_pid, client_read, client_write, pid;
	char client_read_fifo[128], client_write_fifo[128];
	char buf[1024];
	if(!(fp_server = fopen(argv[1], "w"))){
		perror("connect fail : ");
		exit(-1);
	}

	client_pid = getpid();
	sprintf(client_read_fifo, "read_%d.fifo", client_pid);
	sprintf(client_write_fifo, "write_%d.fifo", client_pid);
	mkfifo(client_read_fifo, 0666);
	mkfifo(client_write_fifo, 0666);
	
	fprintf(fp_server, "%d", client_pid);
	fflush(fp_server);

	fd_read = open(client_read_fifo, O_RDONLY);
	fp_write = fopen(client_write_fifo, "w");

	printf("Client %d begin to talk ! \n", client_pid);
	//fclose(fp_server);
	
	pid = fork();

	if(pid > 0){
		close(fd_read);
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_write, "From client %d : %s\n", client_pid, buf);
			fflush(fp_write);
		}
		fprintf(fp_write, "%s", "q");
		fflush(fp_write);
		fclose(fp_write);
		close(fd_read);
		kill(pid, 9);
		wait(NULL);
		unlink(client_read_fifo);
		unlink(client_write_fifo);
		exit(1);
	}
	else{
		fclose(fp_write);
		while(memset(buf, 0, 1024), read(fd_read, buf, 1024)){
			write(1, buf, sizeof(buf));
		}
		close(fd_read);
		exit(1);
	}
	
	return 0;
}
