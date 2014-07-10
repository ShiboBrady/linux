/*************************************************************************
	> File Name: client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Fri 27 Jun 2014 06:11:17 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{	
	if(argc == 1){

	}
	FILE *fp_server, *fp_write;
	char read_fifo[64], write_fifo[64], buf_msg[1024], *key_input;
	int my_pid, child_pid;
	int fd_read;
	fd_set fd_info, fd_info_backup;
	

	if(!(fp_server = fopen(argv[1], "w"))){
		perror("Can't open connect file: ");
		exit(-1);
	}

	my_pid = getpid();

	sprintf(read_fifo, "read_%d.fifo", my_pid);
	sprintf(write_fifo, "write_%d.fifo", my_pid);
	mkfifo(read_fifo, 0666);
	mkfifo(write_fifo, 0666);

	fprintf(fp_server, "%d", my_pid);
	fflush(fp_server);
	
	fp_write = fopen(write_fifo, "w");
	fd_read = open(read_fifo, O_RDONLY);

	printf("Success to connect server.\n");

	FD_ZERO(&fd_info);
	FD_ZERO(&fd_info_backup);
	
	FD_SET(0, &fd_info_backup);
	FD_SET(fd_read, &fd_info_backup);
	
	while(1){
		FD_ZERO(&fd_info);
		fd_info = fd_info_backup;

		select(fd_read + 1, &fd_info, NULL, NULL, NULL);

		if(FD_ISSET(0, &fd_info)){
			memset(buf_msg, 0, 1024);
			if(fgets(buf_msg, 1024, stdin) == NULL){
				break;
			}
			if(buf_msg[0] == 10){
				continue;
			}
			fprintf(fp_write, "From Client %d: %s\n", my_pid, buf_msg);
			fflush(fp_write);
		}
		if(FD_ISSET(fd_read, &fd_info)){
			memset(buf_msg, 0, 1024);
			if(read(fd_read, buf_msg, 1024) == -1){
				break;
			}
			write(1, buf_msg, strlen(buf_msg));
		}
	}
	
	fprintf(fp_server, "%c%d", 'q', my_pid);
	fflush(fp_server);
	fclose(fp_write);
    close(fd_read);
	unlink(read_fifo);
	unlink(write_fifo);
	return 0;
}
