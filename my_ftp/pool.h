/*************************************************************************
	> File Name: pool.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 12:40:07 AM PDT
 ************************************************************************/

#ifndef POOL_H
#define POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUSY 1
#define FREE 0

typedef struct sockaddr_in SA;

typedef struct childInfo
{
	pid_t pid;
	int fd_read;
	int fd_write;
	int state;
	int call_times;
}childInfo, *pchildInfo;

int childProcessInit(pchildInfo childs, int child_num);
void child_main(int w, int r);
#endif
