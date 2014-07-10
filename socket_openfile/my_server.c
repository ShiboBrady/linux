/*************************************************************************
	> File Name: my_server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 02 Jul 2014 01:25:36 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define IP "192.168.1.74"
#define PORT 8888
int main()
{
	int fd_server, fd_client, send_n, recv_n, flag = 1;
	char recv_buf[128] = "", send_buf[1024];
	struct stat my_stat;
	FILE *fp_read;
	struct sockaddr_in server_addr, client_addr;
	memset(&server_addr, 0, sizeof(struct sockaddr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(IP);
	fd_server = socket(AF_INET, SOCK_STREAM, 0);
	if(fd_server == -1){
		perror("socket");
		exit(-1);
	}
	if(bind(fd_server, (const struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	if(listen(fd_server, 5) == -1){
		perror("listen");
		close(fd_server);
		exit(-1);
	}
	while(1){
	memset(&client_addr, 0, sizeof(struct sockaddr));
	int addrlen = sizeof(struct sockaddr);
	fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen);
	if(fd_client == -1){
		perror("accept");
		close(fd_server);
		exit(-1);
		printf("%s %d success connect\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	}
	while((recv_n = recv(fd_client, recv_buf, 128, 0)) > 0){//0表示立刻发

	stat(recv_buf, &my_stat);
	memset(send_buf, 0, 1024);
	if(my_stat.st_mode & 0040000){
		sprintf(send_buf, "%s", "Is a directory.");
	}
	else if(!(fp_read = fopen(recv_buf, "r"))){
		sprintf(send_buf, "%s", "File isn't exit.'");
	}
	else{
		flag = 0;
		printf("recv from IP: %s\nMsg: %s\n", inet_ntoa(client_addr.sin_addr), recv_buf);
		while(memset(send_buf, 0, 1024), fgets(send_buf, 1024, fp_read) != NULL){
			//send_buf[strlen(send_buf) - 1] = 0;
			send_n = send(fd_client, send_buf, strlen(send_buf), 0);
			if(send_n == -1){
				perror("send");
				close(fd_client);
				close(fd_server);
				exit(-1);
			}			
		}
		printf("read over.\n");
	}
	if(flag){
		printf("recv from IP: %s\nMsg: %s\n", inet_ntoa(client_addr.sin_addr), send_buf);
		send_n = send(fd_client, send_buf, strlen(send_buf), 0);
		if(send_n == -1){
			perror("send");
			close(fd_client);
			close(fd_server);
			exit(-1);
		}
	}
	printf("!@#$\n");
	}
	}
	return 0;
}
