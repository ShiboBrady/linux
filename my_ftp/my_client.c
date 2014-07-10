/*************************************************************************
	> File Name: my_client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sun 06 Jul 2014 06:02:57 PM PDT
 ************************************************************************/

#include "ftp.h"

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT.\n");
		exit(EXIT_FAILURE);
	}
	int fd_server, fd_read, fd_write, read_n, total;
	struct sockaddr_in server_addr;
	char buf[512], filename[100];
	int my_recv = 8196, my_snd = 8196;
	MSG msg, rcvMsg, sendMsg;

	if(-1 == (fd_server = socket(AF_INET, SOCK_STREAM, 0))){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	setsockopt(fd_server, SOL_SOCKET, SO_RCVBUF, &my_recv, sizeof(int));
	setsockopt(fd_server, SOL_SOCKET, SO_SNDBUF, &my_recv, sizeof(int));

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == (connect(fd_server, (struct sockaddr*)&server_addr, sizeof(server_addr)))){
		perror("connect");
		exit(EXIT_FAILURE);
	}

	while(1){
		bzero(buf, 512);
		fgets(buf, 512, stdin);
		buf[strlen(buf) - 1] = 0;
		delPlace(buf);
		msg.len = strlen(buf);
		strcpy(msg.content, buf);
		send(fd_server, &msg, MSG_HEAD + msg.len, 0);
		if(buf[0] == 'p'){
			total = 0;
			if(-1 != findsub(buf, "puts")){
				fd_read = open(buf + 5, O_RDONLY);
				if(fd_read < 0){
					perror("upload open file");
					continue;
				}
				while(bzero(&sendMsg, MSG_SIZE), (read_n = read(fd_read, sendMsg.content, MSG_LEN)) > 0){
					sendMsg.len = strlen(sendMsg.content);
					send(fd_server, &sendMsg, MSG_HEAD + sendMsg.len, 0);
					total += read_n;
					system("clear");
					printf("upload %.2f Kb\n", (double)total / 1024);
				}
				sendMsg.len = 0;
				send(fd_server, &sendMsg, MSG_HEAD, 0);
				close(fd_read);
				printf("upload success.\n");
			}
		}
		else if(buf[0] == 'g'){
			total = 0;
			bzero(filename, 100);
			if(-1 != findsub(buf, "gets")){
				sprintf(filename, "down_%s", buf + 5);
				fd_write = open(filename, O_WRONLY | O_CREAT, 0666);
				if(fd_write < 0){
					perror("download create file\n");
					continue;
				}
				while(1){
					bzero(&rcvMsg, MSG_SIZE);
					recv(fd_server, &rcvMsg, MSG_HEAD, 0);
					total += rcvMsg.len;
					if(rcvMsg.len > 0){
						recv(fd_server, &rcvMsg.content, rcvMsg.len, 0);
						write(fd_write, rcvMsg.content, rcvMsg.len);
						system("clear");
						printf("downloading...%.2f Kb \n", (double)total/1024);
					}
					else{
						break;
					}
				}
				close(fd_write);
				printf("down success.\n");
			}
		}
		else{
			while(1){
				memset(&rcvMsg, 0, sizeof(MSG));
				recv(fd_server, &rcvMsg, MSG_HEAD, 0);
				if(rcvMsg.len > 0){
					recv(fd_server, &rcvMsg.content, rcvMsg.len, 0);
					write(1, rcvMsg.content, rcvMsg.len);
					printf("\n");
				}
				else{
					break;
				}
			}
		}
	}

	return 0;
}

