/*************************************************************************
	> file Name: chat_client.c
	> author: ZhangShibo
	> mail:453430198@qq.com 
	> created Time: Fri 04 Jul 2014 04:39:27 AM PDT
 ************************************************************************/

#include "chat.h"

pclientlist cur_online = NULL;	
int online_num;


void* recv_func(void *arg);
void group_chat(int fd_client, SA *server_addr);
void friend_chat(int fd_client, SA *server_addr, pclientlist head, int num);
void print_list(pclientlist head);

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT.\n");
		exit(-1);
	}

	int fd_client, choose, i = 0;
	pthread_t tid;
	fd_client = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd_client == -1){
		perror("socket");
		exit(-1);
	}

	SA server_addr;
	bzero(&server_addr, sizeof(SA));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	MSG msg_on, msg_chat, msg_off, msg_fls;
	bzero(&msg_on, sizeof(MSG));
	msg_on.type = MSG_ON;
	msg_off.type = MSG_OFF;

	/*先发送一个上线信息*/
	sendto(fd_client, &msg_on, sizeof(MSG), 0, (struct sockaddr*)&server_addr, sizeof(SA));


	/*创建一个接受信息的线程*/
	pthread_create(&tid, NULL, recv_func, (void*)fd_client);

	/*用户菜单选项*/
	do{
		system("clear");
		printf("1.my friends\n");
		printf("2.my quence\n");
		printf("3.exit\n");
		scanf("%d", &choose);
		switch(choose){
			case 1:
				friend_chat(fd_client, &server_addr, cur_online, online_num);
				break;
			case 2:
				group_chat(fd_client, &server_addr);
				break;
			case 3:
				break;
		}
	}while(choose != 3);

	/*退出聊天*/
	sendto(fd_client, &msg_off, sizeof(MSG), 0, (struct sockaddr*)&server_addr, sizeof(SA));
	return 0;
}

void* recv_func(void *arg)
{
	int fd_client = (int)arg;
	MSG recv_msg;
	while(1){
		bzero(&recv_msg, sizeof(MSG));
		recvfrom(fd_client, &recv_msg, sizeof(MSG), 0, NULL, NULL);
		if(recv_msg.type != MSG_FLS){
			printf("from %s:%d\n\t%s \n", inet_ntoa(recv_msg.addr.sin_addr), ntohs(recv_msg.addr.sin_port), recv_msg.msg);
		}
	/*接收从服务器端发来的当前在线好友列表*/
		else{
			if(cur_online != NULL){
				pclientlist p, q;
				p = q = cur_online;
				cur_online = NULL;
				while(p){
					q = p->next;
					free(p);
					p = q;
				}
			}
			int i = 0;
			online_num = recv_msg.len;
			if(online_num == 0){				
				pclientlist p, q;
				p = q = cur_online;
				cur_online = NULL;
				while(p){
					q = p->next;
					free(p);
					p = q;
				}
				continue;
			}
			while(i != online_num){
				pclientlist p;
				pclientlist friend = (pclientlist)calloc(1, sizeof(clientlist));
				recvfrom(fd_client, &recv_msg, sizeof(MSG), 0, NULL, NULL);
				friend->addr = recv_msg.addr;
				friend->num = i + 1;
				friend->next = NULL;
				if(i == 0){
					cur_online = friend;
					p = cur_online;
				}
				else{
					p->next = friend;
					p = p->next;
				}
				++i;
			}
		}
	}
}

void group_chat(int fd_client, SA *server_addr)
{
	system("clear");
	MSG msg_chat;
	while(bzero(&msg_chat, sizeof(MSG)), fgets(msg_chat.msg, MSG_SIZE, stdin) != NULL){
		msg_chat.type = MSG_GRP;
		msg_chat.len = strlen(msg_chat.msg);
		msg_chat.msg[strlen(msg_chat.msg) - 1] = 0;
		sendto(fd_client, &msg_chat, sizeof(MSG), 0, (struct sockaddr*)server_addr, sizeof(SA));
	}
}

void friend_chat(int fd_client, SA *server_addr, pclientlist head, int num)
{
	system("clear");
	MSG msg_chat;
	int choose, flag = 0;
	SA cur_friend;
	printf("There %d current online friend.\n", num);
	printf("Input a number of your friend which you want to chat.\n");
	print_list(head);
	scanf("%d", &choose);
	
	while(head){
		if(head->num == choose){
			flag = 1;
			cur_friend = head->addr;
			break;
		}
		head = head->next;
	}
	if(!flag){
		printf("He/She is not online!\n");
		return;
	}
	printf("Now ,you are chating with ip:%s\n", inet_ntoa(cur_friend.sin_addr));	
while(bzero(&msg_chat, sizeof(MSG)), fgets(msg_chat.msg, MSG_SIZE, stdin) != NULL){
		msg_chat.type = MSG_USR;
		msg_chat.addr = cur_friend;
		msg_chat.len = strlen(msg_chat.msg);
		msg_chat.msg[strlen(msg_chat.msg) - 1] = 0;
		sendto(fd_client, &msg_chat, sizeof(MSG), 0, (struct sockaddr*)server_addr, sizeof(SA));
	}
}

void print_list(pclientlist head)
{
	while(head){
		printf("%d:%s:%d\n", head->num, inet_ntoa(head->addr.sin_addr), ntohs(head->addr.sin_port));
		head = head->next;
	}
}
