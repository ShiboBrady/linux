/*************************************************************************
	> File Name: server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Fri 27 Jun 2014 06:49:24 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define NUM 500

typedef struct conn_info
{
	int client_pid;
	int fd_read;
	FILE *fp_write;
}conn_info;

int main(int argc, char *argv[])
{
	if(argc == 1){
		printf("Lack of connect message\n");
		exit(-1);
	}
	FILE *fp_write;
	int fd_server, fd_read, client_pid, i, j;
	char read_fifo[64], write_fifo[64], buf_conn[10], buf_msg[1024];
	fd_set fd_info, fd_info_backup;
	conn_info conn[NUM];
	
	if((fd_server = open(argv[1], O_RDONLY)) == -1){
		perror("Connect file wrong: ");
		exit(-1);
	}

	memset(conn, -1, sizeof(conn));
	
	FD_ZERO(&fd_info);
	FD_ZERO(&fd_info_backup);
	FD_SET(fd_server, &fd_info_backup);

	while(1){
		FD_ZERO(&fd_info);
		fd_info = fd_info_backup;

		select(1024, &fd_info, NULL, NULL, NULL);

		if(FD_ISSET(fd_server, &fd_info)){
			memset(buf_conn, 0, 10);
			if(read(fd_server, buf_conn, 10) == 0){
				continue;
			}

			if(strncmp(buf_conn, "q", 1) == 0){
				client_pid = atoi(buf_conn + 1);
				for(i = 0; i < NUM; ++i){
					if(conn[i].client_pid == client_pid){
						break;
					}
				}
				close(conn[i].fd_read);
				fclose(conn[i].fp_write);
				FD_CLR(conn[i].fd_read, &fd_info_backup);
				printf("Client %d is offline.\n", conn[i].client_pid);
				memset(conn + i, -1, sizeof(conn_info));
			}
			else{
				client_pid = atoi(buf_conn);
				for(i = 0; i < NUM; ++i){
					if(conn[i].fd_read == -1)
						break;
				}
				
				if(i < NUM){
					sprintf(read_fifo, "write_%d.fifo", client_pid);
					sprintf(write_fifo, "read_%d.fifo", client_pid);
					fd_read = open(read_fifo, O_RDONLY);
					perror("read:");
					fp_write = fopen(write_fifo, "w");
					perror("write:");
					
					if(fd_read != -1 && fp_write != NULL){
						conn[i].fd_read = fd_read;
						conn[i].fp_write = fp_write;
						conn[i].client_pid = client_pid;
						FD_SET(fd_read, &fd_info_backup);
						printf("Client %d is online.\n", client_pid);
					}
					else{
						printf("Connection file not exit!\n");
						kill(client_pid, 9);
						unlink(read_fifo);
						unlink(write_fifo);
					}
				}
			else{
				printf("Already to the upper limit!\n");
				kill(client_pid, 9);
				unlink(read_fifo);
				unlink(write_fifo);				
			}
			}
		}
		for(i = 0; i < NUM; ++i){
			if(FD_ISSET(conn[i].fd_read, &fd_info)){
				if(read(conn[i].fd_read, buf_msg, 1024) > 0){
				//	if(strncmp(buf_msg, "q", 1) == 0){
				//		close(conn[i].fd_read);
				//		fclose(conn[i].fp_write);
				//		FD_CLR(conn[i].fd_read, &fd_info_backup);
				//		printf("Client %d is offline.\n", conn[i].client_pid);
				//		memset(conn + i, -1, sizeof(conn_info));
				//	}
				//	else{
						for(j = 0; j < NUM; ++j){
							if(conn[j].fd_read != -1){
								fprintf(conn[j].fp_write, "%s", buf_msg);
								fflush(conn[j].fp_write);
							}
						}
				//	}
				}
			}
		}		
	}
	return 0;
}
