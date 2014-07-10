/*************************************************************************
	> File Name: cl1.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 26 Jun 2014 07:49:08 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

void sighandler(int num)
{
	wait(NULL);
	printf("cl1 exit\n");
	exit(1);
}
int main()
{
	FILE *fp_12;
	int fd_21;
	int pid;
	char buf[1024];

	fp_12 = fopen("1_2.fifo", "w");
	fd_21 = open("2_1.fifo", O_RDONLY);
	
	pid = fork();
	printf("cl1 pid: %d\n", pid);
	if(pid > 0){
		fclose(fp_12);
		while(memset(buf, 0, 1024), read(fd_21, buf, 1024) != 0){
			write(1, buf, sizeof(buf));
		}
		close(fd_21);
		kill(pid, 9);
		printf("kill cl1 pid\n");
		wait(NULL);
		printf("cl1 exit...\n");
		exit(1);
	}
	else{
		close(fd_21);

		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_12, "Form father: %s \n", buf);
			fflush(fp_12);
		}
		fclose(fp_12);
	}
	return 0;
}
