#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void
PrintMsg(char *msg)
{
	printf("%s", msg);

	pthread_exit(NULL);
}

int main()
{
	pthread_t	tid1, tid2;
	char		*msg1 = "Hello, ";
	char		*msg2 = "World!\n";

	//thread id는 tid1이고, msg1을 인자로 PrintMsg를 실행하는 쓰레드 생성
	/* Thread ID: tid1, Thread function: PrintMsg, Thread argument: msg1 */
	if (pthread_create(&tid1,NULL,(void*) PrintMsg,(void*) msg1)<0)  {
		perror("pthread_create");
		exit(1);
	}

	//thread id는 tid2고, msg2를 인자로 PrintMsg를 실행하는 쓰레드 생성
	if (pthread_create(&tid2, NULL, (void *)PrintMsg, (void *)msg2) < 0)  {
		perror("pthread_create");
		exit(1);
	}

	//thread들의 id 출력
	printf("Threads created: tid=%ld, %ld\n", tid1, tid2);
	
	/* Wait for tid1 to exit */
	if (pthread_join(tid1,NULL)<0)  {
		perror("pthread_join");
		exit(1);
	}
	if (pthread_join(tid2, NULL) < 0)  {
		perror("pthread_join");
		exit(1);
	}

	//thead들이 끝나길 기다린 후 메시지 출력
	printf("Threads terminated: tid=%ld, %ld\n", tid1, tid2);
}
