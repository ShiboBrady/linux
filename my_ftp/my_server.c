/*************************************************************************
	> File Name: my_server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 07:30:16 PM PDT
 ************************************************************************/

#include "ftp.h"

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT\n");
		exit(-1);
	}
	int fd_server, fd_client, addrlen;
	pid_t pid;
	MSG msg, snd_msg;
	char buf_cmd[1024];
	SA server_addr, client_addr;
	addrlen = sizeof(SA);
	fd_server = preprocess(argv[1], argv[2]);
	while(fd_client = accept(fd_server, (struct sockaddr*)&client_addr, &addrlen)){
		printf("client: %s:%d is connect.\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		pid = fork();
		if(pid == 0){
			char my_param[1024];
			char f;
			while(1){
				memset(&msg, 0, sizeof(MSG));
				recv(fd_client, &msg, MSG_HEAD, 0);
				recv(fd_client, msg.content, msg.len, 0);
				if(msg.len == 0){
					break;
				}
				//delPlace(msg.content);/*delete place in client.*/
				f = msg.content[0];
				if(f == 'l' || f == 'c' || f == 'r' || f == 'g'){
					begin(fd_client, msg.content);
				}
				else if(msg.content[0] == 'p'){
					if(-1 != findsub(msg.content, "puts")){
						bzero(my_param, 1024);
						strcpy(my_param, msg.content + 5);
						my_upload(fd_client, my_param);
					}
				}
				else{
					msg.len = 0;
					send(fd_client, &msg, MSG_HEAD, 0);
				}
			}
		}
			
	}
	return 0;
}

