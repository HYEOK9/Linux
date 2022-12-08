#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[]){
	if(argc!=2){
		printf("Usage:%s TextFileName\n",argv[0]);
		exit(1);
	}

	char *cmd[1024];
	strcat(cmd,"wc -w ");
	strcat(cmd,argv[1]);
	system(cmd);
}
