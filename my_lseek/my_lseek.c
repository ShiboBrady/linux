/*************************************************************************
	> File Name: my_lseek.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 23 Jun 2014 12:31:43 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

typedef struct stu
{
	int sno;
	char name[20];
}stuInfo;

int main()
{
	int fd_wr_rd, read_n;
	int buf[1024], i;
	char fileName[] = "stuInfo.txt";
	stuInfo stu[5] = {{1, "张三"}, {2, "李四"}, {3, "赵五"}, {4, "Tom"}, {5,"萍萍"}};
	stuInfo stu_temp;
	if((fd_wr_rd = open(fileName, O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1){
		perror("Open file fail:");
		exit(1);
	}
	for(i = 0; i < 5; ++i){
		write(fd_wr_rd, stu + i, sizeof(stuInfo));
	}
	lseek(fd_wr_rd, 0, SEEK_SET);

	printf("Before change:\n");
	while((read_n = read(fd_wr_rd, &stu_temp, sizeof(stuInfo))) != 0){
		printf("sno:%d, name:%s \n", stu_temp.sno, stu_temp.name);
	}
	
	lseek(fd_wr_rd, -2*sizeof(stuInfo), SEEK_CUR);
	read(fd_wr_rd, &stu_temp, sizeof(stuInfo));
	strcpy(stu_temp.name, "汤姆");
	lseek(fd_wr_rd, -sizeof(stuInfo), SEEK_CUR);
	write(fd_wr_rd, &stu_temp, sizeof(stuInfo));
	
	printf("After change:\n");
	lseek(fd_wr_rd, 0, SEEK_SET);
	
	while((read_n = read(fd_wr_rd, &stu_temp, sizeof(stuInfo))) != 0){
		printf("sno:%d, name:%s \n", stu_temp.sno, stu_temp.name);
	}
	return 0;
}
