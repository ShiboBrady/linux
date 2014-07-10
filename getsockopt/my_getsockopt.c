/*************************************************************************
	> File Name: my_getsockopt.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 02 Jul 2014 06:23:51 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
	int sock_fd;
	int recv_size, snd_size;
	int my_recv = 8192, my_snd = 8192;
	int len_secv = sizeof(int);
	int reuse = 1;
	int len_snd = sizeof(int);
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Before modify.\n");
	getsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &recv_size, &len_secv);
	getsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &snd_size, &len_snd);
	printf("recv_size: %d\n", recv_size);
	printf("snd_size: %d\n", snd_size);

	setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &my_recv, sizeof(int));
	setsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &my_snd, sizeof(int));

	printf("After modify.\n");
	getsockopt(sock_fd, SOL_SOCKET, SO_RCVBUF, &recv_size, &len_secv);
	getsockopt(sock_fd, SOL_SOCKET, SO_SNDBUF, &snd_size, &len_snd);
	printf("recv_size: %d\n", recv_size);
	printf("snd_size: %d\n", snd_size);

	setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
	return 0;
}
