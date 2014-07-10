/*************************************************************************
	> File Name: server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 03 Jul 2014 05:27:57 AM PDT
 ************************************************************************/

#include "processpool.h"

int main(int argc, char *argv[])
{
	if(argc != 4){
		printf("expect argument of exe, ip, port, child number.\n");
		exit(-1);
	}

	int fd_server, fd_client, index, childNum = atoi(argv[3]);
	fd_set fd_info, fd_info_bkp;
	struct sockaddr_in client_addr;
	int addrlen = sizeof(client_addr);
	char result[5], str_fd_client[5];
	FILE *fp_write;

	FD_ZERO(&fd_info);
	FD_ZERO(&fd_info_bkp);
	
	p_pcs_state pchilds = (p_pcs_state)calloc(childNum, sizeof(pcs_state));
	init_processpool(pchilds, childNum);
	fd_server = preprocess(argv[1], argv[2]);

	FD_SET(fd_server, &fd_info_bkp);

	for(index = 0; index < childNum; ++index){
		FD_SET(pchilds[index].fd_read, &fd_info_bkp);	
	}
	
	while(1){

		fd_info = fd_info_bkp;
		select(1024, &fd_info, NULL, NULL, NULL);

		if(FD_ISSET(fd_server, &fd_info)){
			fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);

			printf("a client connect: %s: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			
			for(index = 0; index < childNum; ++index){
				if(pchilds[index].state == FREE){
					pchilds[index].state = BUSY;
					fp_write = fdopen(pchilds[index].fd_write, "w");
					printf("fd_client:%d\n", fd_client);
					fprintf(fp_write, "%d", fd_client);
					fflush(fp_write);
					
					break;
				}
			}

		}
		for(index = 0; index < childNum; ++index){
			if(FD_ISSET(pchilds[index].fd_read, &fd_info)){
				read(pchilds[index].fd_read, result, 5);
				printf("%d process excute over.\n", index);
				pchilds[index].state = FREE;
			}
		}
	}
	return 0;
}
