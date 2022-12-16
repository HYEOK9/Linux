#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int dataRead=0,dataWrited=0;
pthread_cond_t isRead,isWrite;
pthread_mutex_t mutex;

char pData[32]="Data is not writed";

void* Sender(){

	//lock 걸며 critical section 진입
	if(pthread_mutex_lock(&mutex)<0){
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}

	//data write
	strcpy(pData,"Data is writed");
	printf("this is a request from thread-%lu.\n",pthread_self());
	printf("Sent a request....\n");
	dataWrited=1;

	//data write signal
	if(pthread_cond_signal(&isWrite)<0){
		perror("pthread_cond_siganl");
		pthread_exit(NULL);
	}

	//data가 read되지 않았으면 wait
	while(!dataRead){
		if(pthread_cond_wait(&isRead,&mutex)<0){
			perror("pthread_cond_signal");
			pthread_exit(NULL);
		}
	}

	//mutex unlock
	if(pthread_mutex_unlock(&mutex)<0){
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}

	pthread_exit(NULL);
}

void* Receiver(){

	//lock걸며 critical section 진입
	if(pthread_mutex_lock(&mutex)<0){
		perror("pthread_mutex_lock");
		pthread_exit(NULL);
	}

	//data가 write될 때 까지 wait
	while(!dataWrited){
		if(pthread_cond_wait(&isWrite,&mutex)<0){
			perror("pthread_mutex_lock");
			pthread_exit(NULL);
		}
	}

	//data read
	printf("Received request: %s.\n",pData);
	printf("this is reply from thread-%lu\n",pthread_self());
	dataRead=1;

	//data read signal
	if(pthread_cond_signal(&isRead)<0){
		perror("pthread_cond_signal");
		pthread_exit(NULL);
	}

	//mutex unlock
	if(pthread_mutex_unlock(&mutex)<0){
		perror("pthread_mutex_unlock");
		pthread_exit(NULL);
	}

	pthread_exit(NULL);
}

int main(){

	pthread_t tid[2];

	//condition variable, mutex init
	if(pthread_cond_init(&isWrite,NULL)<0){
		perror("pthread_cond_init");
		exit(1);
	}

	if(pthread_cond_init(&isRead,NULL)<0){
		perror("pthread_cond_init");
		exit(1);
	}

	if(pthread_mutex_init(&mutex,NULL)<0){
		perror("pthread_mutex_init");
		exit(1);
	}

	//thread create
	if(pthread_create(&tid[0],NULL,Sender,NULL)<0){
		perror("pthread_create");
		exit(1);
	}

	if(pthread_create(&tid[1],NULL,Receiver,NULL)<0){
		perror("pthread_create");
		exit(1);
	}

	//thread join
	for (int i=0; i<2; i++){
		if(pthread_join(tid[i],NULL)<0){
			perror("pthread_join");
			exit(1);
		}
	}

	//condition variable, mutex destory
	if(pthread_cond_destroy(&isWrite)<0){
		perror("pthread_cond_destroy");
		exit(1);
	}

	if(pthread_cond_destroy(&isRead)<0){
		perror("pthread_cond_destroy");
		exit(1);
	}

	if(pthread_mutex_destroy(&mutex)<0){
		perror("pthread_cond_destroy");
		exit(1);
	}
}
