/*************************************************************************
	> File Name: read_first.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 30 Jun 2014 06:11:41 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <time.h>

void* read(void *arg);
void* write(void *arg);

int cnt = 0, readNum = 0;
pthread_mutex_t cnt_mutex, readNum_mutex;

int main()
{
	int num;
	pthread_t tid;
	srand(time(NULL));
	pthread_mutex_init(&cnt_mutex, NULL);
	pthread_mutex_init(&readNum_mutex, NULL);
	while(1){
		num = rand();
		if(num % 2 == 1){
			pthread_create(&tid, NULL, read, NULL);
		}
		else{
			pthread_create(&tid, NULL, write, NULL);
		}
		sleep(1);
	}
	return 0;
}

void* read(void *arg)
{
	pthread_mutex_lock(&readNum_mutex);
	if(readNum == 0){
		pthread_mutex_lock(&cnt_mutex);
	}
	pthread_mutex_unlock(&readNum_mutex);

	pthread_mutex_lock(&readNum_mutex);
	readNum++;
	printf("A reader in.\n");
	pthread_mutex_unlock(&readNum_mutex);

//	sleep(2);
	printf("reader: cnt = %d\n", cnt);

	pthread_mutex_lock(&readNum_mutex);
	readNum--;
	printf("A reader is leave, there %d reader left.\n", readNum);
	pthread_mutex_unlock(&readNum_mutex);
	
	pthread_mutex_lock(&readNum_mutex);
	if(readNum == 0){
		pthread_mutex_unlock(&cnt_mutex);
	}
	pthread_mutex_unlock(&readNum_mutex);

	pthread_detach(pthread_self());
}

void* write(void *arg)
{
	
	pthread_mutex_lock(&cnt_mutex);
	cnt++;
//	sleep(1);
	printf("Writer is in, and cnt = %d\n", cnt);
	pthread_mutex_unlock(&cnt_mutex);
	pthread_detach(pthread_self());
}
