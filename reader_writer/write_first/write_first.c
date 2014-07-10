/*************************************************************************
	> File Name: write_first.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 30 Jun 2014 09:40:30 AM PDT
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <time.h>

void* read(void *arg);
void* write(void *arg);
int cnt = 0, readNum = 0;
pthread_mutex_t w_mutex, r_mutex, cnt_mutex;

int main()
{
	int num;
	pthread_t tid1, tid2;
	pthread_mutex_init(&w_mutex, NULL);
	pthread_mutex_init(&r_mutex, NULL);
	pthread_mutex_init(&cnt_mutex, NULL);
	srand(time(NULL));
	while(1){
		num = rand();
		if(num % 2 ==0){
			pthread_create(&tid1, NULL, read, NULL);
		}
		else{
			pthread_create(&tid2, NULL, write, NULL);
		}
		sleep(1);
	}
	return 0;
}

void* read(void *arg)
{
	pthread_mutex_lock(&w_mutex);
	pthread_mutex_unlock(&w_mutex);

	pthread_mutex_lock(&r_mutex);
	if(readNum == 0){
		pthread_mutex_lock(&cnt_mutex);
	}
	pthread_mutex_unlock(&r_mutex);
	
	printf("A reader come in.\n");
	pthread_mutex_lock(&r_mutex);
	readNum++;
	sleep(1);
	pthread_mutex_unlock(&r_mutex);

	printf("A reader leave.\n");
	pthread_mutex_lock(&r_mutex);
	readNum--;
	printf("%d reader left.\n", readNum);
	pthread_mutex_unlock(&r_mutex);

	pthread_mutex_lock(&r_mutex);
	if(readNum == 0){
		pthread_mutex_unlock(&cnt_mutex);
	}
	pthread_mutex_unlock(&r_mutex);
}

void* write(void *arg)
{
	pthread_mutex_lock(&w_mutex);
	pthread_mutex_lock(&cnt_mutex);
	cnt++;
	printf("Writer in, cnt = %d\n", cnt);
	sleep(2);
	pthread_mutex_unlock(&cnt_mutex);
	pthread_mutex_unlock(&w_mutex);
}
