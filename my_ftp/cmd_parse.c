/*************************************************************************
	> File Name: cmd_parse.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Sat 05 Jul 2014 07:53:20 PM PDT
 ************************************************************************/

#include "ftp.h"


void begin(int fd_client, char *str)
{
	//printf("begin, cmd = %s\n", str);
	char ls[] = "ls";
	char ls_l[] = "ls -l";
	char cd[] = "cd";
	char gets[] = "gets";
	char puts[] = "puts";
	char remove[] = "remove";
	char my_param[1024];

	MSG msg = {0, ""};

	char *p = str;
	char c = *p;
	switch(*p)
	{
		case 'l':
			if(-1 != findsub(str, ls)){
				if(-1 != findsub(str, ls_l)){
					my_ls_l(fd_client);
				}
				else{
					my_ls(fd_client);
				}
			}
			else{
				msg.len = 0;
				send(fd_client, &msg, MSG_HEAD, 0);

			}
			break;
		case 'c':
			if(-1 != findsub(str, cd)){
				bzero(my_param, 1024);
				strcpy(my_param, p + 3);
				my_cd(fd_client, my_param);
			}
			else{
				msg.len = 0;
				send(fd_client, &msg, MSG_HEAD, 0);
			}
			break;
		case 'g':
			if(-1 != findsub(str, gets)){
				bzero(my_param, 1024);
				strcpy(my_param, p + 5);
				my_download(fd_client, my_param);
			}
			else{
				msg.len = 0;
				send(fd_client, &msg, MSG_HEAD, 0);
			}
			break;
		case 'p':
			if(-1 != findsub(str, puts)){
				bzero(my_param, 1024);
				strcpy(my_param, p + 5);
				my_upload(fd_client, my_param);
			}
			else{
				msg.len = 0;
				send(fd_client, &msg, MSG_HEAD, 0);
			}
			break;
		case 'r':
			if(-1 != findsub(str, remove)){
				bzero(my_param, 1024);
				strcpy(my_param, p + 7);
				my_remove(fd_client, my_param);
			}
			else{
				msg.len = 0;
				send(fd_client, &msg, MSG_HEAD, 0);
			}
			break;
		default :
			break;
	}

}

/*字符串匹配*/
int findsub(char *str, char *sub)
{
	int i, j, longlen = strlen(str), shortlen = strlen(sub);
	for(i = 0; i < longlen - shortlen + 1; ++i){
		for(j = 0; j < shortlen; ++j){
			if(str[i + j] != sub[j]){
				break;
			}
		}
		if(j == shortlen){
			return i;
		}
	}
	return -1;
}


/*去空格*/
void delPlace(char *str)
{
	char *p, *q;
	p = str;
	int count = 0;
	while(*p == 32){/*如果字符串开头是空格*/
		++p;
		++count;
	}
	while(*p != 0){/*从不是空格的地方往前移动*/
		*(p-count) = *p;
		++p;
	}
	*(p - count) = 0;/*移动最后的\0*/
	p = q = str;
	while(*p){
		count = 0;
		if(*p == 32 && *(p + 1) == 32){/*如果当前字符和下一个字符都是空格，则需要去空格*/
			++p;
			q = p;/*纪录当前位置*/
			while(*p == 32){
				++p;
				++count;
			}
			while(*p != 0){
				*(p - count) = *p;
				++p;
			}
			*(p - count) = 0;
			p = q;/*让p重新回到刚才的地方*/
		}
		else{
			++p;
		}
	}
	if(*(p - 1) == 32){/*如果字符串是以空格结尾的，则往前找最后一个非空格的字符*/
		--p;
	}
	*p = 0;/*在字符串最后面加上\0*/
}

/*列出文件*/
void my_ls(int fd_client)
{
	DIR *dir;
	char send_str[MSG_LEN];
	struct dirent *reader;
	struct stat fileInfo;
	if(!(dir = opendir("."))){
		perror("opendir");
		return;
	}
	while((reader = readdir(dir)) != NULL){
		if(strncmp(reader->d_name, ".", 1) != 0 && strncmp(reader->d_name, "..", 2) != 0){
			memset(&fileInfo, 0, sizeof(fileInfo));
			bzero(send_str, MSG_LEN);
			stat(reader->d_name, &fileInfo);
			sprintf(send_str, "%s %d", reader->d_name, fileInfo.st_size);
			send_msg(fd_client, send_str);
		}
	}
	bzero(send_str, MSG_LEN);
	send_msg(fd_client, send_str);
	closedir(dir);
}

void my_ls_l(int fd_client)
{
	char send_str[MSG_LEN], str[11], time[200];
	DIR *dir;
	struct dirent *reader;
	struct stat fileInfo;
	if(!(dir = opendir("."))){
		perror("opendir");
		return;
	}
	while((reader = readdir(dir)) != NULL){
		if(strncmp(reader->d_name, ".", 1) != 0 && strncmp(reader->d_name, "..", 2) != 0){
			bzero(&fileInfo, sizeof(fileInfo));
			stat(reader->d_name, &fileInfo);
			authorityProcess(str, fileInfo.st_mode);
			timeProcess(time, ctime(&fileInfo.st_atime));
			sprintf(send_str, "%s %3d %5s %5s %6d %15s %s\n", str, fileInfo.st_nlink, getpwuid(fileInfo.st_uid)->pw_name, getgrgid(fileInfo.st_gid)->gr_name, fileInfo.st_size, time, reader->d_name);
			send_msg(fd_client, send_str);
		}
	}
	bzero(send_str, MSG_LEN);
	send_msg(fd_client, send_str);
	closedir(dir);
}

void my_cd(int fd_client, char *str)
{
	char send_str[MSG_LEN];
	chdir(str);
	sprintf(send_str, "%s", getcwd(NULL, 0));
	send_msg(fd_client, send_str);
	bzero(send_str, MSG_LEN);
	send_msg(fd_client, send_str);
}

void my_remove(int fd_client, char *str)
{
	char send_str[MSG_LEN];
	struct stat file_name;
	stat(str, &file_name);
	if(file_name.st_mode & 0040000){
		if(0 != rmdir(str)){
			sprintf(send_str, "%s", "delete fail.");
		}
		else{
			sprintf(send_str, "%s", "delete success.");
		}
	}
	else{
		if(0 != unlink(str)){
			sprintf(send_str, "%s", "delete fail.");
		}
		else{
			sprintf(send_str, "%s", "delete success.");
		}
	}
	send_msg(fd_client, send_str);
	bzero(send_str, MSG_LEN);
	send_msg(fd_client, send_str);
}

void my_download(int fd_client, char *str)
{
	int read_n, fd_read, total;
	char send_str[MSG_LEN + 1];
	MSG snd_msg;
	printf("filename : %s\n", str);
	fd_read = open(str, O_RDONLY);
	if(fd_read < 0){
		perror("Not has this file:");
		sprintf(send_str, "%s", "Not has this file.");
		send_msg(fd_client, send_str);
	}
	else{
		total = 0;
		while(bzero(&snd_msg, sizeof(MSG)), (read_n = read(fd_read, snd_msg.content, MSG_LEN)) > 0){
			snd_msg.len = read_n;
			send(fd_client, &snd_msg, read_n + MSG_HEAD, 0);
			total += read_n;
			system("clear");
			printf("send %.2f Kb\n", (double)total / 1024);
		}
	}
	bzero(send_str, MSG_LEN);
	send_msg(fd_client, send_str);
	close(fd_read);
	printf("send over.\n");
}

void my_upload(int fd_client, char *str)
{
	int fd_write, total, i;
	MSG msg;
	char filename[50];
	bzero(filename, 50);
	sprintf(filename, "upload_%s", str);
	i = fd_write = open(filename, O_WRONLY | O_CREAT, 0666);
	printf("fd_write = %d", fd_write);
	if(fd_write < 0){
		perror("create file fail");
	}
	else{
		total = 0;
		while(1){
			bzero(&msg, MSG_SIZE);
			recv(fd_client, &msg, MSG_HEAD, 0);
			total += msg.len;
			if(msg.len > 0){
				recv(fd_client, &msg.content, msg.len, 0);
				write(i, msg.content, msg.len);
				system("clear");
				printf("upload %.2f Kb\n", (double)total / 1024);
			}
			else{
				break;
			}
		}
		close(fd_write);
		printf("upload over.\n");
	}
}

void authorityProcess(char *str, int auth)
{
	strcpy(str, "----------");
	if(auth & 0040000){
		str[0] = 'd';
	}
	if(auth & 0000400){
		str[1] = 'r';
	}
	if(auth & 0000200){
		str[2] = 'w';
	}
	if(auth & 0000100){
		str[3] = 'x';
	}
	if(auth & 0000040){
		str[4] = 'r';
	}
	if(auth & 0000020){
		str[5] = 'w';
	}
	if(auth & 0000010){
		str[6] = 'x';
	}
	if(auth & 0000004){
		str[7] = 'r';
	}
	if(auth & 0000002){
		str[8] = 'w';
	}
	if(auth & 0000001){
		str[9] = 'x';
	}
}

void timeProcess(char *p_time, char *time)
{
	strcpy(p_time, time+4);
	int count=0;
	while(count != 2 && *p_time != 0){
		if(*p_time == ':')
			++count;
		++p_time;
	}
	*(p_time-1) = '\0';
}
