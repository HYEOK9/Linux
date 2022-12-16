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
	int		*pInt;
	//semaphore id 선언
	int		mutexSemId,isWriteSemId;
	int		semVal;

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

	//semaphore값 초기화
	if (semInitValue(mutexSemId,0)<0){
		perror("semInitValue");
		exit(1);
	}
	
	if (semInitValue(isWriteSemId,0)<0){
		perror("semInitvalue");
		exit(1);
	}
	
	//sipc2가 아직 쓰지 않았다면 wait
	if(semWait(isWriteSemId)<0){
		perror("semWait");
		exit(1);
	}

	//data 출력
	pData = ptr + sizeof(int);
	printf("Received request: %s.....", pData);
	sprintf(pData, "This is a reply from %d.", getpid());

	//mutex semphore post
	if (semPost(mutexSemId)<0){
		perror("semPost");
		exit(1);
	}

	printf("Replied.\n");

	sleep(1);

	//shared memory 삭제
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
