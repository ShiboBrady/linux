/*************************************************************************
	> File Name: cl2.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Thu 26 Jun 2014 08:35:18 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main()
{
	int fd1, fd2,n_ready, max, read_rtn, rf1 = 0, rf2 = 0;
	fd_set fd_read, fd_ready;

	FILE *fp_21, *fp_23;
	int fd_12, fd_32;
	
	char buf[1024];

	FD_ZERO(&fd_read);
	FD_ZERO(&fd_ready);

	fp_21 = fopen("2_1.fifo", "w");
	fd_12 = open("1_2.fifo", O_RDONLY);
	fp_23 = fopen("2_3.fifo", "w");
	fd_32 = open("3_2.fifo", O_RDONLY);
	max = fd_12 > fd_32 ? fd_12 : fd_32;

	FD_SET(fd_12, &fd_read);
	FD_SET(fd_32, &fd_read);

	if(fork() > 0){
		close(fd_12);
		close(fd_32);
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_21, "From cl2 : %s\n", buf);
			fprintf(fp_23, "From cl2 : %s\n", buf);
			fflush(fp_21);
			fflush(fp_23);
		}
		fclose(fp_21);
		fclose(fp_23);
		wait(NULL);
		printf("cl1 exit");
	}
	else{
		fclose(fp_21);
		fclose(fp_23);
		while(1){
			FD_ZERO(&fd_ready);
			fd_ready = fd_read;
			n_ready = select(max + 1, &fd_ready, NULL, NULL, NULL);
			if(FD_ISSET(fd_12, &fd_ready)){
				memset(buf, 0, 1024);
				read_rtn = read(fd_12, buf, 1024);
				if(read_rtn == 0){
					rf1 = 1;
					break;
				}
			}
			if(FD_ISSET(fd_32, &fd_ready)){
				memset(buf, 0, 1024);
				read_rtn = read(fd_32, buf, 1024);
				if(read_rtn == 0){
					rf2 = 1;
					break;
				}
			}
			write(1, buf, sizeof(buf));
		}
		if(rf1){
			close(fd_12);
		}
		else{
			close(fd_32);
		}
	}
}
