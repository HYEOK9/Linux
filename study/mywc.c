#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
	
int main(int argc,char* argv[]){
	pid_t pid;
	int status;

	if(argc!=2){
		printf("Usage: %s filename\n",argv[0]);
		exit(1);
	}

	pid=fork();

	if(pid<0){
		perror("fork");
		exit(1);
	}
	else if(pid==0){
		char* args[]={"wc","-c",argv[1],NULL};
		if(execvp("wc",args)<0){
			perror("execvp");
			exit(1);
		}
	}
	else{
		wait(&status);
	}
	
}
