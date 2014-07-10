/*************************************************************************
	> File Name: producer_consumer.c
	> Author: ZhangShibo
	> Mail:453430198@qq.com 
	> Created Time: Mon 30 Jun 2014 08:36:50 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <pthread.h>
#include <time.h>
#define N 5

int product[N];
int product_cnt = 0, left_cnt = 0;
pthread_t product_tid, consumer1_tid, consumer2_tid; 
pthread_cond_t consumer_cond, producer_cond;
pthread_mutex_t product_mutex, product_cnt_mutex, left_cnt_mutex;

void* produce(void *arg);
void* consume(void *arg);

int main(int argc, char *argv[])
{
	int producter_num = atoi(argv[1]);
	int consumer_num = atoi(argv[2]);
	srand(time(NULL));
	pthread_mutex_init(&product_mutex, NULL);
	pthread_mutex_init(&product_cnt_mutex, NULL);
	pthread_cond_init(&consumer_cond, NULL);
	pthread_cond_init(&producer_cond, NULL);
	
	while(producter_num){
		pthread_create(&product_tid, NULL, produce, NULL);
		producter_num--;
	}
	while(consumer_num){
		pthread_create(&consumer1_tid, NULL, consume, NULL);
		consumer_num--;
	}

	//pthread_create(&product_tid, NULL, produce, NULL);
	//pthread_create(&consumer1_tid, NULL, consume, NULL);
	//pthread_create(&consumer2_tid, NULL, consume, NULL);

	pthread_join(product_tid, NULL);
	pthread_join(consumer1_tid, NULL);
	pthread_join(consumer2_tid, NULL);

	pthread_mutex_destroy(&product_mutex);
	pthread_mutex_destroy(&product_cnt_mutex);
	pthread_cond_destroy(&producer_cond);
	pthread_cond_destroy(&consumer_cond);
	return 0;	
}

void* produce(void *arg)
{
	while(1){
		//pthread_mutex_lock(&product_mutex);
		pthread_mutex_lock(&product_cnt_mutex);
		while(product_cnt == N){
			pthread_cond_wait(&consumer_cond, &product_cnt_mutex);
		}
		pthread_mutex_unlock(&product_cnt_mutex);
		
		//pthread_mutex_lock(&product_mutex);
		pthread_mutex_lock(&product_cnt_mutex);
		printf("Producter come in, product number is %d.\n", product_cnt);
		product_cnt++;
		if(product_cnt == 1){
			pthread_cond_broadcast(&producer_cond);
		}
		printf("Producter come out, product number is %d.\n", product_cnt);
		//pthread_mutex_unlock(&product_mutex);
		pthread_mutex_unlock(&product_cnt_mutex);
		sleep(rand() % 5 + 1);
	}
}

void* consume(void *arg)
{
	while(1){	
		//pthread_mutex_lock(&product_mutex);
		pthread_mutex_lock(&product_cnt_mutex);
		while(product_cnt == 0){
			pthread_cond_wait(&producer_cond, &product_cnt_mutex);
		}
		pthread_mutex_unlock(&product_cnt_mutex);
		
		//pthread_mutex_lock(&product_mutex);
		pthread_mutex_lock(&product_cnt_mutex);
		printf("Consumer come in, product number is %d.\n", product_cnt);
		sleep(rand() % 5 + 1);
		product_cnt--;
		if(product_cnt == N-1){
			pthread_cond_broadcast(&consumer_cond);
		}
		
		printf("Consumer come out, product number is %d.\n", product_cnt);
		//pthread_mutex_unlock(&product_mutex);
		pthread_mutex_unlock(&product_cnt_mutex);
		sleep(rand() % 5 + 1);
	}
	sleep(1);
}
