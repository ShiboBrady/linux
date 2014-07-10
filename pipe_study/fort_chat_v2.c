/*************************************************************************
	> File Name: fort_chat_v2.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 26 Jun 2014 01:28:45 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fd1[2], fd2[2];
	char buf[1024];
	FILE *fp_child, *fp_father;
	pipe(fd1);
	pipe(fd2);
	if(fork() > 0){
		fclose(fd1[1]);
		fclose(fd2[0]);

		while(memset(buf, 0, 1024), read(fd1[0], buf, 1024)){
			write(1, buf, sizeof(buf));
		}

		fclose(fd1[0]);

		fp_father = fdopen(fd2[1], "w");
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin)){
			fprintf(fp_father, "From father: %s", buf);
			fflush(fp_father);
		}
		fclose(fd2[1]);

		wait(NULL);
		printf("exit.");
	}
	else{
		
	}
	return 0;
}
