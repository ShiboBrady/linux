/*************************************************************************
	> File Name: makechild.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 03 Jul 2014 05:24:24 AM PDT
 ************************************************************************/

#include "processpool.h"

void init_processpool(p_pcs_state childs, int num)
{
	int index;
	for(index = 0; index < num; ++index){
		pid_t pid;
		int fds1[2], fds2[2];
		pipe(fds1);
		pipe(fds2);
		printf("fds1[0] = %d, fds2[1] = %d, %d, %d\n", fds1[0], fds1[1], fds2[0], fds2[1]);
		pid = fork();
		if(pid == 0){
			close(fds1[0]);
			close(fds2[1]);
			child_main(fds2[0]);
		}
		else{
			childs[index].pid = pid;
			childs[index].state = FREE;
			childs[index].fd_read = fds1[0];
			childs[index].fd_write = fds2[1];
			childs[index].pro_n = 0;
			close(fds1[1]);
			close(fds2[0]);
		}
	}
}

void child_main(int fd)
{
	int fd_client;
	char temp[5];
	while(memset(temp, 0, 5), read(fd, temp, 5) > 0){
		fd_client = atoi(temp);
		request_handle(fd_client);
		printf("%d\n", 1);
	}
}
