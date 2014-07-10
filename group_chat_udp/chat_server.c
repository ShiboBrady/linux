/*************************************************************************
	> File Name: chat_server.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Fri 04 Jul 2014 02:06:52 AM PDT
 ************************************************************************/

#include "chat.h"

void msg_on(pUSR *, SA *, int);
void msg_off(pUSR*, SA *, int);
void msg_usr(int, MSG*, SA *);
void msg_grp(int ,pUSR, MSG*, SA *);
void msg_fls(pUSR pLise, SA *, int);

int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("EXE IP PORT\n");
		exit(-1);
	}
	int fd_server, online_num;
	fd_set fd_info, fd_info_bkp;
	pUSR pList = NULL;

	SA server_addr;
	if(-1 == (fd_server  = socket(AF_INET, SOCK_DGRAM, 0))){
		perror("socket");
		exit(-1);
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(-1 == (bind(fd_server, (struct sockaddr*)&server_addr, sizeof(SA)))){
		perror("bind");
		close(fd_server);
		exit(-1);
	}

	FD_ZERO(&fd_info);
	FD_ZERO(&fd_info_bkp);

	FD_SET(fd_server, &fd_info_bkp);

	struct timeval tm;

	while(1){
		fd_info = fd_info_bkp;
		tm.tv_usec = 1000;
		tm.tv_sec = 0;
		select(fd_server + 1, &fd_info, NULL, NULL, &tm);
		if(FD_ISSET(fd_server, &fd_info)){
			MSG chat_msg;
			SA from_addr;
			int addrlen = sizeof(SA);
			bzero(&chat_msg, sizeof(MSG));
			recvfrom(fd_server, &chat_msg, sizeof(MSG), 0, (struct sockaddr*)&from_addr, &addrlen);
			//printf("%s\n", inet_ntoa(from_addr.sin_addr));
			switch(chat_msg.type){
				case 1:
					msg_usr(fd_server, &chat_msg, &from_addr);
					break;
				case 2:
					msg_grp(fd_server, pList, &chat_msg, &from_addr);
					break;
				case 3:
					msg_on(&pList, &from_addr, fd_server);
					break;
				case 4:
					msg_off(&pList, &from_addr, fd_server);
					break;
				case 5:
					msg_fls(pList, &from_addr, fd_server);
					break;
			}
		}
	}
	
	return 0;
}

/*上线处理，链表头插入*/
void msg_on(pUSR *phead, SA *addr, int fd_server)
{
	int num = 0, i = 0;
	pUSR p;
	printf("ip:%s port:%d on\n", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
	pUSR new_usr = (pUSR)calloc(1, sizeof(USR));
	new_usr -> addr = *addr;
	new_usr -> next = *phead;
	*phead = new_usr;
	p = *phead;
	while(p){
		msg_fls(*phead, &(p->addr), fd_server);
		p = p->next;
	}
}

/*下线处理，删除链表节点*/
void msg_off(pUSR *head, SA *addr, int fd_server){
	pUSR p, q;
	p = q = *head;
	if(*head == NULL){
		printf("There is no user online.\n");
		return;
	}
	while(p->next != NULL && ((p->addr).sin_port != addr->sin_port || (p->addr).sin_addr.s_addr != addr->sin_addr.s_addr)) {
		q = p;
		p = p->next;
	}
	printf("%s:%d.\n", inet_ntoa((q->addr).sin_addr), ntohs((q->addr).sin_port));
	printf("%s:%d.\n", inet_ntoa((p->addr).sin_addr), ntohs((p->addr).sin_port));
	if((p->addr).sin_port == addr->sin_port && (p->addr).sin_addr.s_addr == addr->sin_addr.s_addr) {
		if(p == q){
			*head = p->next;
		}
		else{
			q->next = p->next;
		}
		printf("%s:%d user is offline.\n", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
		free(p);
	}
	else{
		printf("Not has this user");
	}
	p = *head;
	while(p){
		msg_fls(*head, &(p->addr), fd_server);
		p = p->next;
	}
}
/*两人聊天*/
void msg_usr(int fd_server, MSG *msg, SA *addr){
	SA to_addr = msg->addr;
	msg->addr = *addr;
	sendto(fd_server, msg, sizeof(MSG), 0, (struct sockaddr*)&(to_addr), sizeof(SA));

}
/*群聊*/
void msg_grp(int fd_server, pUSR head, MSG *msg, SA *addr)
{
	while(head){
		msg->addr = *addr;
		
		sendto(fd_server, msg, sizeof(MSG), 0, (struct sockaddr*)&(head->addr), sizeof(SA));
		head = head->next;	
	}
}

void msg_fls(pUSR pList, SA *addr, int fd_server)
{
	pUSR p = pList;
	MSG msg;
	int num = 0, i = 0;
	while(p){
		++num;
		p = p->next;
	}
	msg.type = MSG_FLS;
	msg.len = num;
	sendto(fd_server, &msg, sizeof(MSG), 0, (struct sockaddr*)addr, sizeof(SA));
	p = pList;
	while(i != num){
		msg.type = MSG_FLS;
		msg.addr = p->addr;
		sendto(fd_server, &msg, sizeof(MSG), 0, (struct sockaddr*)addr, sizeof(SA));
		p = p->next;
		++i;
	}	
}
