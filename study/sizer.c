#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void recursive(char *path,int size){

	DIR *dp;
	struct dirent *dep;
	struct stat statbuf;
	char fullpath[80];
	char curpath[80];

	if((dp=opendir(path))==NULL){
		perror("opendir");
		exit(0);
	}

	while(dep=readdir(dp)){
		if(strcmp(dep->d_name,".")==0||strcmp(dep->d_name,"..")==0) continue;
		strcpy(curpath,path);
		strcat(curpath,"/");
		strcat(curpath,dep->d_name);
		if(lstat(curpath,&statbuf)<0){
			printf("err at %s\n",curpath);
			perror("lstat");
			exit(1);
		}
		if(statbuf.st_size<=size && !S_ISDIR(statbuf.st_mode)) printf("%s\n",dep->d_name);
	}

	rewinddir(dp);
	while(dep=readdir(dp)){
		if(strcmp(dep->d_name,".")==0||strcmp(dep->d_name,"..")==0) continue;
		strcpy(fullpath,path);
		strcat(fullpath,"/");
		strcat(fullpath,dep->d_name);
		if(lstat(fullpath,&statbuf)<0){
			perror("lstat");
			exit(1);
		}
		if(S_ISDIR(statbuf.st_mode)) recursive(fullpath,size);		
	}

	closedir(dp);
}

int main(int argc,char* argv[]){
	if(argc!=2){
		printf("Usage: %s size",argv[0]);
		exit(1);
	}
	recursive(".",atoi(argv[1]));
}


