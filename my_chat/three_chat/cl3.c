/*************************************************************************
	> File Name: cl3.c
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

	FILE *fp_31, *fp_32;
	int fd_13, fd_23;
	
	char buf[1024];

	FD_ZERO(&fd_read);
	FD_ZERO(&fd_ready);

	fd_13 = open("1_3.fifo", O_RDONLY);
	fp_31 = fopen("3_1.fifo", "w");
	fd_23 = open("2_3.fifo", O_RDONLY);
	fp_32 = fopen("3_2.fifo", "w");
	max = fd_13 > fd_23 ? fd_13 : fd_23;

	FD_SET(fd_13, &fd_read);
	FD_SET(fd_23, &fd_read);

	if(fork() > 0){
		close(fd_13);
		close(fd_23);
		while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL){
			fprintf(fp_31, "From cl3 : %s\n", buf);
			fprintf(fp_32, "From cl3 : %s\n", buf);
			fflush(fp_31);
			fflush(fp_32);
		}
		fclose(fp_31);
		fclose(fp_32);
		wait(NULL);
		printf("cl1 exit");
	}
	else{
		fclose(fp_31);
		fclose(fp_32);
		while(1){
			FD_ZERO(&fd_ready);
			fd_ready = fd_read;
			n_ready = select(max + 1, &fd_ready, NULL, NULL, NULL);
			if(FD_ISSET(fd_13, &fd_ready)){
				memset(buf, 0, 1024);
				read_rtn = read(fd_13, buf, 1024);
				if(read_rtn == 0){
					rf1 = 1;
					break;
				}
			}
			if(FD_ISSET(fd_23, &fd_ready)){
				memset(buf, 0, 1024);
				read_rtn = read(fd_23, buf, 1024);
				if(read_rtn == 0){
					rf2 = 1;
					break;
				}
			}
			write(1, buf, sizeof(buf));
		}
		if(rf1){
			close(fd_13);
		}
		else{
			close(fd_23);
		}
	}
}
