#include <stdio.h>
#include "synclib.h"

#define	NLOOPS	5


main()
{
	int		i;
	pid_t	pid;

	//pipe 생성
	TELL_WAIT();
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	//parent process
	else if (pid > 0)  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			TELL_CHILD();
			printf("Parent: Tell to child\n");
			printf("Parent: Wait for child to tell\n");
			WAIT_CHILD();
		}
	}
	//child process
	else  {
		for (i = 0 ; i < NLOOPS ; i++)  {
			printf("Child: Wait for parent to tell\n");
			//우선 parent를 기다림
			WAIT_PARENT();
			//무언가 한 뒤, parent에게 보냄
			TELL_PARENT();
			printf("Child: Tell to parent\n");
		}
	}
}
