/*************************************************************************
	> File Name: fork_chat_v1.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Wed 25 Jun 2014 11:55:14 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char buf[1024];
	int fds[2], fds2[2];
	FILE *fp_child,*fp_father;
	pipe(fds);
	pipe(fds2);
	printf("fds[0]:%d, fds[1]:%d\n", fds[0], fds[1]);
	printf("fds2[0]:%d, fds2[1]:%d\n", fds2[0], fds2[1]);
	if(fork()>0){
		close(fds[1]);
		close(fds2[0]);
		while(memset(buf, 0, 1024), read(fds[0], buf, 1024) > 0){
			write(1, buf, strlen(buf));
		}
		//close(fds[0]);

		fp_father = fdopen(fds2[1], "w");
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_father, "from father: %s", buf);
			fflush(fp_father);
		}
		close(fds2[1]);
		wait(NULL);
		printf("exit.\n");
	}
	else{
		close(fds[0]);
		close(fds2[1]);
		fp_child = fdopen(fds[1], "w");
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_child, "from child: %s", buf);
			fflush(fp_child);
		}
		close(fds[1]);


		while(memset(buf, 0, 1024), read(fds2[0], buf, 1024) > 0){
			write(1, buf, strlen(buf));
		}
		close(fds2[0]);
	}
	return 0;
}
