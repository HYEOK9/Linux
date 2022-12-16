#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

int pData=0;
sem_t isInSemId,mutexSemId;

void* Receiver(){

	//isInSemId를 wait
	if(sem_wait(&isInSemId)<0){
		perror("sem_wait");
		exit(1);
	}

	//shared data semaphore wait
	if(sem_wait(&mutexSemId)<0){
		perror("sem_wait");
		exit(1);
	}

	//shared data 출력
	printf("Received request: %d.\n",pData);
	printf("pData is %d, this is reply from thread-%lu.\n",pData,pthread_self());

	//shared data semaphore을 post
	if(sem_post(&mutexSemId)<0){
		perror("sem_post");
		exit(1);
	}

	printf("Replied.\n");

	pthread_exit(NULL);
}

void* Sender(){

	//shared data semaphore wait
	if(sem_wait(&mutexSemId)<0){
		perror("sem_wait");
		exit(1);
	}
	
	printf("this is a request from thread-%lu.\n",pthread_self());
	printf("Sent a request....\n");
	pData=1;

	//shared data semaphore post
	if(sem_post(&mutexSemId)<0){
		perror("sem_post");
		exit(1);
	}	

	//Receiver thread가 접근 가능하도록 post
	if(sem_post(&isInSemId)<0){
		perror("sem_wait");
		exit(1);
	}

	pthread_exit(NULL);
}

int main(){

	pthread_t tid[2];

	//semaphore 초기화
	if(sem_init(&isInSemId,0,0)<0){
		perror("sem_init");
		exit(1);
	}

	if(sem_init(&mutexSemId,0,1)<0){
		perror("sem_init");
		exit(1);
	}

	//receiver thread, sender thread 생성
	if(pthread_create(&tid[0],NULL,Receiver,NULL)<0){
		perror("pthread_create");
		exit(1);
	}

	if(pthread_create(&tid[1],NULL,Sender,NULL)<0){
		perror("pthread_create");
	}

	//thread join
	for(int i =0; i<2; i++){
		if(pthread_join(tid[0],NULL)<0){
			perror("pthread_join");
			exit(1);
		}
	}


	//semaphore destory
	if (sem_destroy(&isInSemId) < 0){
		perror("sem_destroy");
		exit(1);
	}

	if (sem_destroy(&mutexSemId) < 0){
		perror("sem_destroy");
		exit(1);
	}
}
