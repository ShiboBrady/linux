/*************************************************************************
	> File Name: processpool.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 03 Jul 2014 05:17:59 AM PDT
 ************************************************************************/
#ifndef PROCESSPOOL_H
#define PROCESSPOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define BUSY 1
#define FREE 0
typedef struct processState
{
	pid_t pid;
	int state;
	int fd_read;
	int fd_write;
	int pro_n;
}pcs_state, *p_pcs_state;

void init_process(p_pcs_state childs, int num);

void child_main();

int preprocess(char *ip, char *port);
void request_handle(int fd_client);
#endif
