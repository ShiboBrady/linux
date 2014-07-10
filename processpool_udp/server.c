/*************************************************************************
	> File Name: server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 01:39:28 AM PDT
 ************************************************************************/

#include "pool.h"

int main(int argc, char *argv[])
{
	if(argc != 4){
		printf("EXE IP PORT CHILD_NUM");
		exit(-1);
	}

	int fd_server, fd_max, child_num = atoi(argv[3]), i, addrlen = sizeof(SA);
	char buf[1024], rtn_value[3];
	FILE *fp_write;
	SA server_addr, client_addr; 
	fd_set fd_info, fd_info_bkp;
	struct timeval tm;

	if(-1 == (fd_server = socket(AF_INET, SOCK_DGRAM, 0))){
		perror("socket");
		exit(-1);
	}
	
	bzero(&server_addr, sizeof(SA));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == (bind(fd_server, (struct sockaddr*)&server_addr, sizeof(SA)))){
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	
	FD_ZERO(&fd_info);
	FD_ZERO(&fd_info_bkp);
	FD_SET(fd_server, &fd_info_bkp);
	
	pchildInfo childs = (pchildInfo)calloc(child_num, sizeof(childInfo));
	childProcessInit(childs, child_num);
	//fd_max = fd_max > fd_server ? fd_max : fd_server;

	for(i = 0; i < child_num; ++i){
		FD_SET(childs[i].fd_read, &fd_info_bkp);
	}

	while(1){
		tm.tv_usec = 1000;
		tm.tv_sec = 0;
		fd_info = fd_info_bkp;

		select(1024, &fd_info, NULL, NULL, &tm);

		if(FD_ISSET(fd_server, &fd_info)){
			printf("fd_set\n");
			for(i = 0; i < child_num; ++i){
				if(childs[i].state == FREE){
					childs[i].state = BUSY;
					memset(buf, 0, 1024);
					recvfrom(fd_server, buf, 1024, 0, (struct sockaddr*)&client_addr, &addrlen);
					printf("client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
					fp_write = fdopen(childs[i].fd_write, "w");
					fprintf(fp_write, "%d %d %s", client_addr.sin_addr.s_addr, client_addr.sin_port, buf);
					fflush(fp_write);
					break;
				}
			}
		}
		for(i = 0; i < child_num; ++i){
			if(FD_ISSET(childs[i].fd_read, &fd_info)){
				read(childs[i].fd_read, rtn_value, 2);
				childs[i].state = FREE;
			}
		}
	}


	return 0;
}

