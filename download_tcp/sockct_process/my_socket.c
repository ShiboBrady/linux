/*************************************************************************
	> File Name: my_socket.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 07 Jul 2014 09:05:54 AM PDT
 ************************************************************************/

#include "download.h"

int preprocess(char *ip, char *port)
{
	int fd_server, addrlen, reuse = 1;
	SA server_addr, client_addr;

	if(-1 == (fd_server = socket(AF_INET, SOCK_STREAM, 0))){
		perror("socket");
		exit(-1);
	}

	if(0 != setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))){
		perror("setsockopt");
		close(fd_server);
		exit(-1);
	}

	bzero(&server_addr, sizeof(SA));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(port));
	server_addr.sin_addr.s_addr = inet_addr(ip);

	if(-1 == bind(fd_server, (struct sockaddr*)&server_addr, sizeof(server_addr))){
		perror("bind");
		close(fd_server);
		exit(-1);
	}

	if(-1 == listen(fd_server, 5)){
		perror("listen");
		close(fd_server);
		exit(-1);
	}
	return fd_server;

}

void request_process(int fd_client)
{
	MSG msg;
	int fd_read, total = 0, read_n;
	bzero(&msg, sizeof(MSG));
	recv(fd_client, &msg, MSG_HEAD, 0);
	printf("msg.len = %d\n", msg.len);
	recv(fd_client, &msg.content, msg.len, 0);
	printf("downfile:%s\n", msg.content);
	fd_read = open(msg.content, O_RDONLY);
	if(fd_read < 0){
		perror("read file error");
	}
	else{
		total = 0;
		while(bzero(&msg, MSG_SIZE), (read_n = read(fd_read, msg.content, MSG_LEN)) > 0){
			msg.len = read_n;
			send(fd_client, &msg, MSG_HEAD + read_n, 0);
			total += read_n;
			system("clear");
			printf("send %.2f Kb\n", (double)total / 1024);
		}
		msg.len = 0;
		send(fd_client, &msg, MSG_HEAD, 0);
		close(fd_read);
		printf("send over.\n");
	}
}
