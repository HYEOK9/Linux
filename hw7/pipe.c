#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define	MAX_BUF	128

main()
{
	int		n, fd[2],fd2[2];
	pid_t	pid;
	char	buf[MAX_BUF];

	//fd 두개 만듦
	if (pipe(fd)<0)  {
		perror("pipe");
		exit(1);
	}

	if(pipe(fd2)<0){
		perror("pipe2");
		exit(1);
	}

	if ((pid = fork()) < 0)  {
		perror("fork");
		exit(1);
	}
	else if (pid == 0)  {
		//child process는 fd[0]을 사용하므로 fd[1]을 닫음
		close(fd[1]);
		printf("Child : Wait for parent to send data\n");
		//fd[0](parent가 보낸 data)을 읽음, child가 먼저 수행되면 기다림
		if ((n=read(fd[0],buf,MAX_BUF))<0)  {
			perror("read");
			exit(1);
		}
		printf("Child : Received data from parent: ");
		fflush(stdout);
		//STDOUT에 write하면 출력 가능
		write(STDOUT_FILENO, buf, n);
		close(fd2[0]);
		strcpy(buf, "Hello, World2!\n");
		printf("Child: Send data to Parent\n");
		write(fd2[1],buf,strlen(buf)+1);
	}
	else  {
		//parent process는 fd[1]을 사용하므로 fd[0]을 닫음
		close(fd[0]);
		strcpy(buf, "Hello, World!\n");
		printf("Parent: Send data to child\n");
		/* write */
		//fd[1]에 쓰는데, null char까지 보내야하므로 +1까지 보냄
		write(fd[1],buf,strlen(buf)+1);
		
		close(fd2[1]);
		if((n=read(fd2[0],buf,MAX_BUF))<0){
			perror("read");
			exit(1);
		}
		printf("Parent : Received data from child: ");
		fflush(stdout);
		write(STDOUT_FILENO,buf,n);
	}

	exit(0);
}
