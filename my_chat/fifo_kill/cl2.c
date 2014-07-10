/*************************************************************************
	> File Name: cl2.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 26 Jun 2014 07:49:13 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void sighandler(int num)
{
	exit(0);
}

int main()
{
	FILE *fp_21;
	int fd_12;
	int pid;
	char buf[1024];

	fd_12 = open("1_2.fifo", O_RDONLY);
	fp_21 = fopen("2_1.fifo", "w");

	pid = fork();
	printf("cl2 pid: %d\n", pid);
	if(pid > 0){
		fclose(fp_21);
		while(memset(buf, 0, 1024), read(fd_12, buf, 1024) != 0){
			write(1, buf, sizeof(buf));
		}
		close(fd_12);
		kill(pid, 9);
		printf("kill cl2 pid\n");
		wait(NULL);
		printf("cl2 exit...\n");
		exit(1);
	}
	else{
		close(fd_12);
		
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_21, "From child : %s \n", buf);
			fflush(fp_21);
		}
		fclose(fp_21);
		exit(1);
	}
	return 0;
}

