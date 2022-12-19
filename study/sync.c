#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t PtoldSemId,CtoldSemId;

void* Parent(){

	printf("Parent: Tell to child\n");

	if(sem_post(&PtoldSemId)<0){
		perror("sem_post");
		exit(1);
	}

	printf("Parent: Wait for child to tell\n");

	if(sem_wait(&CtoldSemId)<0){
		perror("sem_wait");
		exit(1);
	}

	pthread_exit(NULL);
}
 
void* Child(){

	printf("Child: Wait for parent to tell\n");

	if(sem_wait(&PtoldSemId)<0){
		perror("sem_wait");
		exit(1);
	}

	printf("Child: Tell to parent\n");

	if(sem_post(&CtoldSemId)<0){
		perror("sem_post");
		pthread_exit(NULL);
	}

	pthread_exit(NULL);

}

int main(){

	pthread_t Pthread,Cthread;

	if (sem_init(&PtoldSemId,0,0)<0){
		perror("sem_init");
		exit(1);		
	}

	if (sem_init(&CtoldSemId,0,0)<0){
		perror("sem_init");
		exit(1);
	}

	if(pthread_create(&Pthread,NULL,Parent,NULL)<0){
		perror("pthread_create");
		exit(1);
	}

	if(pthread_create(&Cthread,NULL,Child,NULL)<0){
		perror("pthread_create");
		exit(1);
	}

	if(pthread_join(Pthread,NULL)<0){
		printf("pthread_join");
		exit(1);
	}

	if(pthread_join(Cthread,NULL)<0){
		printf("pthread_join");
		exit(1);
	}

	if(sem_destroy(&PtoldSemId)<0){
		perror("sem_destroy");
		exit(1);
	}

	if(sem_destroy(&CtoldSemId)<0){
		perror("sem_destroy");
		exit(1);
	}
}
