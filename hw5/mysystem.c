#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int mysystem(char* cmd){

    pid_t pid;
    int status;
    char *argv[]={"sh","-c",cmd,NULL};

    pid=fork();
    
    if(pid<0){
    	perror("fork");
        exit(1);
    }
    else if(pid==0){
    	if(execv("/bin/sh",argv)<0){
		    perror("exec");
		    exit(1);
	    }
    }
    else{
    	if(waitpid(pid,&status,0)<0){
		perror("waitpid");
		exit(1);
	}
    }
}

int main(){
    mysystem("ls -al");
    mysystem("date");
    mysystem("who");
}
