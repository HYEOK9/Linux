#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t	pid;
	char	*argv[] = { "/home/lsp52/hw3/mycp", "/home/lsp52/hw3/input.txt", "/home/lsp52/hw3/output2.txt", NULL };

	// execl
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		// child process에서 hw3의 mycp 실행 후 output1.txt생성
		if (execl("/home/lsp52/hw3/mycp","mycp","/home/lsp52/hw3/input.txt","/home/lsp52/hw3/output1.txt",NULL))  {
			perror("execl");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}

	// execv
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		//또 다른 child process에서 execv로 mycp실행 후 output2.txt생성
		if (execv("/home/lsp52/hw3/mycp",argv))  {
			perror("execv");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}

	// execlp
	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	//
	else if (pid == 0)  {
		// execute 'env' from PATH
		if (execlp("env","env",NULL))  {
			perror("execlp");
			exit(1);
		}
	}
	if (waitpid(pid, NULL, 0) < 0)  {
		perror("waitpid");
		exit(1);
	}
}
