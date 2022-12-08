#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void SigChldHandler(int signo){

	//SIGCHLD 시그널을 받으면 콘솔에 메시지 출력후 프로세스 종료
	if(signo==SIGCHLD){
		printf("Received a SIGCHLD siganl\n");
		exit(1);
	}

	//SIGCHLD외의 시그널을 받은 경우
	else {
		printf("Received unknown signal\n");
		exit(0);
	}
}

void main()
{
	pid_t	pid;

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		printf("I'm a child - PID : %d\n",getpid());
	}
	else  {
		//SIGCHLD에 따른 핸들러 등록
		if(signal(SIGCHLD,SigChldHandler)==SIG_ERR){
			perror("signal");
			exit(1);
		}
	}
	//자식프로세스가 종료될 때까지 그냥 무한루프를 돌림
	while(1) ;
}
