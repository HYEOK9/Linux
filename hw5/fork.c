#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int		Var = 6;
char	Buf[] = "a write to stdout\n";

int main()
{
	int		var;
	pid_t	pid;

	var = 88;
	write(STDOUT_FILENO, Buf, sizeof(Buf)-1);
	printf("Before fork\n");

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	//child process면 var++,Var++
	else if (pid == 0)  {
		/* child */
		Var++;
		var++;
	}
	//parent process면 2초간 sleep
	else  {
		/* parent */
		sleep(2);
	}

	//child, parent process의 pid, Var, var출력
	printf("pid = %d, Var = %d, var = %d\n", getpid(), Var, var);
}
