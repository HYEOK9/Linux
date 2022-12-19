#include <stdlib.h>
#include <stdio.h>
#include "semlib.c"
#include "shm.h"

int shmid;
int sem1,sem2;
int *n;

int Calc(int number){

	if((shmid=shmget(SHM_KEY,SHM_SIZE,SHM_MODE))<0){
		perror("shmget");
		exit(1);
	}

	if((n=(int *)shmat(shmid,0,0))==(void*)-1){
		perror("shmat");
		exit(1);
	}

	*n=number;

	if((sem1=semInit(SEM1_KEY))<0){
		perror("semInit");
		exit(1);
	}

	if(semPost(sem1)<0){
		perror("semWait");
	}

	if((sem2=semInit(SEM2_KEY))<0){
		perror("semInit");
		exit(1);
	}

	if(semWait(sem2)<0){
		perror("semWait");
		exit(1);
	}

	printf("Calc = %d\n",*n);
	return n;
}

int main(int argc, char* argv[]){

	int inputNumber=atoi(argv[1]);
	Calc(inputNumber);
	exit(1);
}
