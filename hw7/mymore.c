#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main() 
{
	int fd[2];
	pid_t child;

	//pipe 생성
	if(pipe(fd)<0)  {
		perror("pipe");
		exit(1);
	}
 
	child = fork();
	if(child == (pid_t)(-1))  {
        	perror("fork");
		exit(1);
	}
	//child process
	else if(child == (pid_t)0) {
        	close(1);
		//fd1을 쓸것이므로 fd[0]은 closeㅇ
		close(fd[0]);
        	
		//1과 fd[1]을 duplicate
        	if(dup(fd[1])==-1)  {
        		perror("dup");
			exit(1);
		}

		//execlp로 ls -l 수행, 이 출력이 pipe에 input으로 넘어감
        	if((execlp("ls", "ls", "-l", NULL)) == -1)  {
        		perror("execlp");
			exit(1);
		}
	}
	//parent process
	else {
		//standard input 닫음
        	close(0);
		close(fd[1]);
        	
		//dup(fd[0])와 같음, dup2는 직접 지정
        	if(dup2(fd[0],0)==-1)  {
        		perror("dup");
			exit(1);
		}
		//more process에 std input으로 ls -l의 출력이 전달됨
        	if((execlp("more", "more", NULL)) == -1)  {
        		perror("execlp");
			exit(1);
		}
	}
 
	return 0;
}
