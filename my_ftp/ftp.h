/*************************************************************************
	> File Name: ftp.h
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 07:07:06 PM PDT
 ************************************************************************/

#ifndef FTP_H
#define FTP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MSG_HEAD 4
#define MSG_SIZE 8196
#define MSG_LEN 8188

typedef struct sockaddr_in SA;

typedef struct MSG
{
	int len;
	char content[MSG_LEN];
}MSG;

int preprocess(char *ip, char *port);
void send_msg(int fd_client, char *str);
void delPlace(char *str);
void begin(int fd_client, char *str);
int findsub(char *str, char *sub);
void my_ls(int fd_client);
void my_ls_l(int fd_client);
void my_cd(int fd_client, char *str);
void my_remove(int fd_client, char *str);
void my_download(int fd_client, char *str);
void my_upload(int fd_client, char *str);
void authorityProcess(char *str, int auth);
void timeProcess(char *p_time, char *time);
#endif
