/*************************************************************************
	> File Name: make_child.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 02:28:22 AM PDT
 ************************************************************************/

#include "pool.h"

int childProcessInit(pchildInfo childs, int child_num)
{
	int i, fd_max = 0x80000000;
	int fds1[2], fds2[2];
	for(i = 0; i < child_num; ++i){
		pid_t pid;
		pipe(fds1);
		pipe(fds2);
		pid = fork();
		if(pid == 0){
			close(fds1[0]);
			close(fds2[1]);
			dup2(fds1[1], 1);
			dup2(fds2[0], 0);
			close(fds1[1]);
			close(fds2[0]);
			//child_main(fds1[1], fds2[0]);
			child_main(1, 0);
		}
		else{
			close(fds1[1]);
			close(fds2[0]);
			childs[i].fd_read = fds1[0];
			childs[i].fd_write = fds2[1];
			childs[i].pid = pid;
			childs[i].state = FREE;
			childs[i].call_times = 0;
			//fd_max = fd_max > fds1[0] ? fd_max : fds1[0];
			//fd_max = 
		}
	}
}

void child_main(int w, int r)
{
	int port, ip, fd_server, addrlen;
	SA client_addr;
	char buf[1024], buf_msg[1024];
	while(memset(buf, 0, 1024), read(r, buf, 1024) > 0){
			sscanf(buf, "%d %d %s", &ip, &port, buf_msg);
			fd_server = socket(AF_INET, SOCK_DGRAM, 0);
			memset(&client_addr, 0, sizeof(SA));
			client_addr.sin_family = AF_INET;
			client_addr.sin_port = port;
			client_addr.sin_addr.s_addr = ip;
			addrlen = sizeof(SA);
			sendto(fd_server, buf_msg, sizeof(buf_msg), 0, (struct sockaddr*)&client_addr, addrlen);
			write(w, "1", 1);
	}
}

