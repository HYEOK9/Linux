#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semlib.h"
#include "prodcons.h"

main()
{
	BoundedBufferType	*pBuf;
	int					shmid, i, data;
	int					emptySemid, fullSemid, mutexSemid;

	//shared memory 만드는 과정
	if ((shmid = shmget(SHM_KEY, SHM_SIZE, SHM_MODE)) < 0)  {
		perror("shmget");
		exit(1);
	}
	if ((pBuf = (BoundedBufferType *)shmat(shmid, 0, 0)) == (void *) -1)  {
		perror("shmat");
		exit(1);
	}

	//mutex, full, empty semaphore 초기화
	if ((emptySemid = semInit(EMPTY_SEM_KEY) ) < 0)  {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}
	if ((fullSemid = semInit(FULL_SEM_KEY)) < 0)  {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}
	if ((mutexSemid = semInit(MUTEX_SEM_KEY)) < 0)  {
		fprintf(stderr, "semInit failure\n");
		exit(1);
	}

	srand(0x8888);
	for (i = 0 ; i < NLOOPS ; i++)  {
		//producer는 queue에 데이터를 넣기 전 empty semaphore을 1 감소 시킴
		if (semWait(emptySemid) < 0)  {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}
		//데이터를 넣기 전 mutexSemid도 1감소시킴
		if (semWait(mutexSemid) < 0)  {
			fprintf(stderr, "semWait failure\n");
			exit(1);
		}

		printf("Producer: Producing an item.....\n");
		data = (rand()%100)*10000;
		pBuf->buf[pBuf->in].data = data;
		pBuf->in = (pBuf->in + 1) % MAX_BUF;
		pBuf->counter++;

		//데이터를 넣은 후 mutex semaphore을 1증가시키고 나옴
		if (semPost(mutexSemid) < 0)  {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		//full semaphore도 1 증가 시킴
		if (semPost(fullSemid) < 0)  {
			fprintf(stderr, "semPost failure\n");
			exit(1);
		}
		usleep(data);
	}

	printf("Producer: Produced %d items.....\n", i);

	sleep(2);
	printf("Producer: %d items in buffer.....\n", pBuf->counter);
	
	//종료 전 semaphore destory
	if (semDestroy(mutexSemid) < 0)  {
		fprintf(stderr, "semDestroy failure\n");
	}
	if (semDestroy(emptySemid) < 0)  {
		fprintf(stderr, "semDestroy failure\n");
	}
	if (semDestroy(fullSemid) < 0)  {
		fprintf(stderr, "semDestroy failure\n");
	}
	if (shmctl(shmid, IPC_RMID, 0) < 0)  {
		perror("shmctl");
		exit(1);
	}
}
