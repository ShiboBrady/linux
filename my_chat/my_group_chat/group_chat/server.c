/*************************************************************************
	> File Name: server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Fri 27 Jun 2014 04:11:01 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#define NUM 500
typedef struct client_info
{
	FILE *fp_server_write;
	int pid;
	int server_read;
	int server_write;
}client_info;

int main(int argc, char *argv[])
{
	if(argc == 1){
		printf("There is no avalible connection.\n");
		exit(-1);
	}

	int fd_server, fd_server_read,fd_server_write, client_pid, i, j;
	client_info conn[NUM];
	fd_set fd_info, fd_ready;
	char buf_conn[128], buf_msg[1024], server_read_fifo[128], server_write_fifo[128];

	memset(conn, -1, sizeof(conn));

	if((fd_server = open(argv[1], O_RDONLY)) == -1){
		perror("Can not open fifo file : ");
		exit(-1);
	}
	
	FD_ZERO(&fd_info);
	FD_ZERO(&fd_ready);
	FD_SET(fd_server, &fd_info);
	
	while(1){
		FD_ZERO(&fd_ready);
		fd_ready = fd_info;

		select(1024, &fd_ready, NULL, NULL, NULL);
		
		if(FD_ISSET(fd_server, &fd_ready)){
			if(read(fd_server,buf_conn ,128) == 0){
				continue;
			}
			client_pid = atoi(buf_conn);
			sprintf(server_write_fifo, "read_%d.fifo", client_pid);
			sprintf(server_read_fifo, "write_%d.fifo", client_pid);
			fd_server_write = open(server_write_fifo, O_WRONLY);
			perror("write:");
			fd_server_read = open(server_read_fifo, O_RDONLY);
			perror("read:");

			
			for(i = 0;i < NUM; ++i){
				if(conn[i].server_read == -1){
					break;
				}
			}
			if(i < NUM){
				conn[i].pid = client_pid;
				conn[i].server_read = fd_server_read;
				conn[i].server_write = fd_server_write;
				conn[i].fp_server_write = fdopen(fd_server_write, "w");
				FD_SET(fd_server_read, &fd_info);
				printf("Client %d is online .\n", client_pid);
			}
			else{				
				kill(client_pid, 9);
				close(fd_server_read);
				close(fd_server_write);
				unlink(server_read_fifo);
				unlink(server_write_fifo);
			}
			
		}
		for(i = 0; i < NUM; ++i){
			if(FD_ISSET(conn[i].server_read, &fd_ready)){
				memset(buf_msg, 0, 1024);
				read(conn[i].server_read, buf_msg, 1024);
				if(strncmp(buf_msg, "q", 1) == 0){
					close(conn[i].server_read);
					close(conn[i].server_write);
					FD_CLR(conn[i].server_read, &fd_info);
					printf("Client %d exit.\n", conn[i].pid);
					memset(conn + i, -1, sizeof(client_info));
				}
				else{
					for(j = 0; j < NUM; ++j){
						if(conn[j].server_read != -1){
							fprintf(conn[j].fp_server_write, " %s", buf_msg);
							fflush(conn[j].fp_server_write);
						}
					}
				}
			}
		}
	}
	return 0;
}
