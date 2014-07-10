/*************************************************************************
	> File Name: my_client.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 07 Jul 2014 06:31:33 PM PDT
 ************************************************************************/

#include "download.h"

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT\n");
		exit(-1);
	}

	int fd_server, fd_write, addrlen, total;
	char filename[100];
	SA server_addr;
	MSG msg, rcv_msg;

	if(-1 == (fd_server = socket(AF_INET, SOCK_STREAM, 0))){
		perror("socket");
		exit(-1);
	}

	addrlen = sizeof(SA);
	bzero(&server_addr, addrlen);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == connect(fd_server, (struct sockaddr*)&server_addr, addrlen)){
		perror("connect");
		close(fd_server);
		exit(-1);
	}

	printf("input: ");
	fgets(msg.content, MSG_LEN, stdin);
	msg.content[strlen(msg.content) - 1] = 0;
	msg.len = strlen(msg.content);
	sprintf(filename, "down_%s", msg.content);

	fd_write = open(filename, O_WRONLY | O_CREAT, 0777);

	if(fd_write < 0){
		perror("write open");
		exit(-1);
	}
	else{
		total = 0;
		send(fd_server, &msg, MSG_HEAD + msg.len, 0);
		while(1){
			bzero(&msg, sizeof(SA));
			recv(fd_server, &msg, MSG_HEAD, 0);
			total += msg.len;
			system("clear");
			printf("download %.2f Kb\n", (double)total / 1024);
			if(msg.len > 0){
				recv(fd_server, &msg.content, msg.len, 0);
				write(fd_write, msg.content, msg.len);
			}
			else{
				close(fd_write);
				printf("download over.\n");
				break;
			}
		}
	}
	return 0;
}

