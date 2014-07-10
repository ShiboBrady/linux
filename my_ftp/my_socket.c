/*************************************************************************
	> File Name: my_socket.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 07:15:01 PM PDT
 ************************************************************************/

#include "ftp.h"

int preprocess(char *ip, char *port)
{
	int fd_server, addrlen, reuse = 1;
	int my_recv = 8196, my_snd = 8196;
	SA server_addr, client_addr;
	
	if(-1 == (fd_server = socket(AF_INET, SOCK_STREAM, 0))){
		perror("socket");
		exit(-1);
	}

	setsockopt(fd_server, SOL_SOCKET, SO_RCVBUF, &my_recv, sizeof(int));
	setsockopt(fd_server, SOL_SOCKET, SO_SNDBUF, &my_snd, sizeof(int));

	if(0 != setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))){
		perror("setsockopt");
		close(fd_server);
		exit(-1);
	}

	memset(&server_addr, 0, sizeof(SA));
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


void send_msg(int fd_client, char *str)
{
	MSG snd_msg;
	snd_msg.len = strlen(str);
	strcpy(snd_msg.content, str);
	send(fd_client, &snd_msg, snd_msg.len + MSG_HEAD, 0);
}
