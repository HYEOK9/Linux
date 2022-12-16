#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.c"
#include "shm.h"


main()
{
	int		shmid;
	char		*ptr,*pData;
	//semaphore id 선언
	int		mutexSemId,isWriteSemId;

	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}

	if ((ptr = shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	//semaphore init
	if ((mutexSemId=semInit(IPC_SEM_KEY))<0){
		perror("semInit");
		exit(1);
	}

	if ((isWriteSemId=semInit(ISIN_SEM_KEY))<0){
		perror("semInit");
		exit(1);		
	}

	//data 쓰기
	pData=ptr+sizeof(int);

	//isWrite semaphore post
	if(semPost(isWriteSemId)<0){
		perror("semPost");
		exit(1);
	}

	sprintf(pData, "This is a request from %d.", getpid());
	printf("Sent a request.....");

	//sipc1을 wait
	if (semWait(mutexSemId)<0){
		perror("semWait");
		exit(1);
	}

	printf("Received reply: %s\n", pData);
}
