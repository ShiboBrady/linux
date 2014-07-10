/*************************************************************************
	> File Name: cl1.c
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

	FILE *fp_12, *fp_13;
	int fd_21, fd_31;
	
	char buf[1024];

	FD_ZERO(&fd_read);
	FD_ZERO(&fd_ready);

	fd_21 = open("2_1.fifo", O_RDONLY);
	fp_12 = fopen("1_2.fifo", "w");
	fp_13 = fopen("1_3.fifo", "w");
	fd_31 = open("3_1.fifo", O_RDONLY);
	max = fd_21 > fd_31 ? fd_21 : fd_31;

	FD_SET(fd_21, &fd_read);
	FD_SET(fd_31, &fd_read);

	if(fork() > 0){
		close(fd_21);
		close(fd_31);
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_12, "From cl1 : %s\n", buf);
			fprintf(fp_13, "From cl2 : %s\n", buf);
			fflush(fp_12);
			fflush(fp_13);
		}
		fclose(fp_12);
		fclose(fp_13);
		wait(NULL);
		printf("cl1 exit");
	}
	else{
		fclose(fp_12);
		fclose(fp_13);
		while(1){
			FD_ZERO(&fd_ready);
			fd_ready = fd_read;
			n_ready = select(max + 1, &fd_ready, NULL, NULL, NULL);
			if(FD_ISSET(fd_21, &fd_ready)){
				memset(buf, 0, 1024);
				read_rtn = read(fd_21, buf, 1024);
				if(read_rtn == 0){
					rf1 = 1;
					break;
				}
			}
			if(FD_ISSET(fd_31, &fd_ready)){
				memset(buf, 0, 1024);
				read_rtn = read(fd_31, buf, 1024);
				if(read_rtn == 0){
					rf2 = 1;
					break;
				}
			}
			write(1, buf, sizeof(buf));
		}
		if(rf1){
			close(fd_21);
		}
		else{
			close(fd_31);
		}
	}
}
