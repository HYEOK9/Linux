#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <signal.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/ipc.h>
#include "semlib.c"
#include "shm.h"

int shmid;
int *n;
int result=0;
int sem1,sem2;

int sigIntHandler(){
	
	if(semDestroy(sem1)<0){
		perror("semDestory");
		exit(1);
	}

	if(semDestroy(sem2)<0){
		perror("semDestroy");
		exit(1);
	}

	if(shmctl(shmid,IPC_RMID,0)<0){
		perror("shmctl");
		exit(1);
	}

	exit(1);
}

int main(){

	signal(SIGINT,sigIntHandler);

	if((shmid=shmget(SHM_KEY, SHM_SIZE, SHM_MODE))<0){
		perror("shmget");
		exit(1);
	}

	if((sem1=semInit(SEM1_KEY))<0){
		printf("semInit");
		exit(1);
	}

	if((sem2=semInit(SEM2_KEY))<0){
		printf("semInit");
		exit(1);
	}

	if(semInitValue(sem1,0)<0){
		printf("semInitValue");
		exit(1);
	}

	if(semInitValue(sem2,0)<0){
		printf("semInitValue");
		exit(1);
	}

	while(1){
		if(semWait(sem1)<0){
			perror("semWait");
			exit(1);
		}

		if((n=(int*)shmat(shmid,0,0))==(void*)-1){
			perror("shmat");
			exit(1);
		}

		for(int i=1; i<=(int)*n; i++) result+=i;
		*n=result;

		printf("Calc = %d\n",*n);

		if(semPost(sem2)<0){
			perror("semPost");
			exit(1);
		}
	}

}

