/*************************************************************************
	> File Name: my_client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 02 Jul 2014 04:30:11 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include  <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#define IP "192.168.1.100"
#define PORT 8888

int fd_server;
char buf[1024], buf_path[100], buf_content[1024];
struct sockaddr_in server_addr;

void* my_send(void *arg);
void* my_receive(void *arg);
int main()
{
	pthread_t tid1, tid2;
	fd_server = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_server == -1){
		perror("socket");
		exit(-1);
	}

	memset(&server_addr, 0, sizeof(struct sockaddr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(IP);
	if(connect(fd_server, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) == -1){
		perror("connect");
		close(fd_server);
		exit(-1);
	}
	pthread_create(&tid1, NULL, my_send, NULL);
	pthread_create(&tid2, NULL, my_receive, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}

void* my_send(void *arg)
{
	int flag = 0;
	while(1){
		do{
			memset(buf_path, 0, 100);
			if(fgets(buf_path, 100, stdin) == NULL){
				flag = 1;
				break;
			}
			buf_path[strlen(buf_path) - 1] = 0;
     	}while(strlen(buf_path) == 0);
		printf("read over.\n");
		if(flag){
			break;
		}
		if(send(fd_server, buf_path, 100, 0) == -1){
			perror("send");
			close(fd_server);
			exit(-1);
		}
	}
	exit(1);
}

void* my_receive(void *arg)
{
	while(1){
		memset(buf_content, 0, 1024);
		if(recv(fd_server, buf_content, sizeof(buf_content), 0) == -1){
			perror("recv");
			close(fd_server);
			exit(-1);
		}
		//write(1, buf_content, sizeof(buf_content));		
		puts(buf_content);
	}
	printf("*****\n");
}
