/*************************************************************************
	> File Name: client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 05:04:54 AM PDT
 ************************************************************************/

#include "pool.h"

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT\n");
		exit(-1);
	}

	int fd_server, addrlen = sizeof(SA);
	char buf[1024];
	SA server_addr;
	if(-1 == (fd_server = socket(AF_INET, SOCK_DGRAM, 0))){
		perror("socket");
		exit(-1);
	}

	memset(&server_addr, 0, sizeof(SA));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	while(1){
	memset(buf, 0, 1024);
	fgets(buf, 1024, stdin);
	sendto(fd_server, buf, strlen(buf), 0, (struct sockaddr*)&server_addr, addrlen);
	memset(buf, 0, 1024);
	recvfrom(fd_server, buf, 1024, 0, NULL, NULL);
	printf("%s\n", buf);
	}
	return 0;
}

