#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <ctype.h>

void* print(void* d_name){
	struct stat statbuf;
	if(lstat((char*) d_name,&statbuf)<0){
		perror("lstat");
		exit(1);
	}
       printf("%s %ld\n",(char*) d_name,statbuf.st_size);	
}

void makethread(char *d_name){
	pthread_t tid;
	pthread_create(&tid,NULL,print,d_name);
}

int main(){
	DIR *dp;
	struct dirent *dep;

	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(1);
	}

	while(dep=(readdir(dp))){

		if(strcmp(dep->d_name,".")==0||strcmp(dep->d_name,"..")==0) continue;
		makethread(dep->d_name);
	}
}
