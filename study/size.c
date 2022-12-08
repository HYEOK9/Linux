#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc,char* argv[]){
	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;

	if(argc!=2){
		printf("Usage: %s size",argv[0]);
		exit(1);
	}

	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(1);
	}

	while(dep=readdir(dp)){
		if(lstat(dep->d_name,&statbuf)<0){
			perror("lstat");
			exit(1);
		}

		if(strcmp(dep->d_name,".")==0||strcmp(dep->d_name,"..")==0) continue;
		if(statbuf.st_size>=atoi(argv[1]))
			printf("%s\n",dep->d_name);
	}
}
