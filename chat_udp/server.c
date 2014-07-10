/*************************************************************************
	> File Name: server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 03 Jul 2014 06:40:28 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

void* recv_func(void *arg);

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("exe, ip, port");
		exit(-1);
	}
	int fd_client, fd_server;
	fd_server = socket(AF_INET, SOCK_DGRAM, 0);
	char buf[1024], chat_msg[1024];
	char chat_ip[31];
	int ips[4];
	if(fd_server == -1){
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in server_addr, client_addr;
	int addrlen = sizeof(client_addr);
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == bind(fd_server, (struct sockaddr*)&server_addr, sizeof(server_addr))){
		perror("bind");
		close(fd_server);
		exit(-1);
	}

	while(printf("ip:"), fflush(stdout), bzero(chat_ip, 32), fgets(chat_ip, 32, stdin)){
		if(chat_ip[0] == '\n'){
			continue;
		}
		else{
			if(4 != sscanf(chat_ip, "%d.%d.%d.%d", ips, ips + 1, ips +2, ips + 3)){
				printf("wrong format!\n");
				continue;
			}
			else if(ips[0] > 255){
				printf("wrong ip!\n");
				continue;
			}
			else{
				chat_ip[strlen(chat_ip) - 1] = 0;
				bzero(&client_addr, sizeof(client_addr));
				client_addr.sin_family = AF_INET;
				client_addr.sin_port = htons(atoi(argv[2]));
				client_addr.sin_addr.s_addr = inet_addr(chat_ip);
				pthread_t tid;
				pthread_create(&tid, NULL, recv_func, (void*)fd_server);
				while(bzero(chat_msg, 1024), fgets(chat_msg, 1024, stdin) != NULL){
					chat_msg[strlen(chat_msg) - 1] = 0;
					sendto(fd_server, chat_msg, strlen(chat_msg), 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
				}
				sendto(fd_server, "bye", 3, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
								
			}
		}
	}

	return 0;
}

void* recv_func(void* arg){
	pthread_detach(pthread_self());
	int fd_server = (int)arg;
	struct sockaddr_in from_addr;
	char chat_msg[1024];
	int addrlen = sizeof(from_addr);
	while(1){
		bzero(&chat_msg, 1024);
		recvfrom(fd_server, chat_msg, 1024, 0, (struct sockaddr*)&from_addr, &addrlen);
		if(strncmp(chat_msg, "bye", 3) == 0){
			break;
		}
		else{
			printf("from %s:%s\n", inet_ntoa(from_addr.sin_addr), chat_msg);
		}
	}	
}
