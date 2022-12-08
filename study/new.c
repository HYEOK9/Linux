#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){

	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;

	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(1);
	}
	int a=9999999999;
	char *fileName;
	while(dep=readdir(dp)){

		if(lstat(dep->d_name,&statbuf)<0){
			perror("lstat");
			exit(1);
		}
		
		if(strcmp(dep->d_name,".")==0 || strcmp(dep->d_name,"..")==0) continue;

		if(a<statbuf.st_ctime){
			a=statbuf.st_ctime;
			fileName=dep->d_name;
		}
	}
	printf("%s\n",fileName);
}
