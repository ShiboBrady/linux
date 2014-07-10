/*************************************************************************
	> File Name: my_server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 07 Jul 2014 05:02:46 PM PDT
 ************************************************************************/

#include "download.h"



int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT\n");
		exit(-1);
	}

	int fd_server, fd_client, addrlen, fd_read, total, read_n;
	pid_t pid;
	SA client_addr;
	MSG msg;
	fd_server = preprocess(argv[1], argv[2]);	
	addrlen = sizeof(SA);

	while(fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen)){
		printf("client %s:%d is online.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		pid = fork();
		if(pid == 0){
			request_process(fd_client);
		}
	}
	return 0;
}

