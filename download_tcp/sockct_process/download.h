/*************************************************************************
	> File Name: my_socket.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 07 Jul 2014 08:57:18 AM PDT
 ************************************************************************/

#ifndef MY_SOCKET_H
#define MY_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MSG_HEAD 4
#define MSG_LEN 8188
#define MSG_SIZE 8192

typedef struct sockaddr_in SA;

typedef struct MSG
{
	int len;
	char content[MSG_LEN];
}MSG;

int preprocess(char *ip, char *port);
void request_preprocess(int fd_client);

#endif
