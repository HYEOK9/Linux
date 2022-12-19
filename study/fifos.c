#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include "fifo.h"

void sigIntHandler(){
	remove(SERV_FIFO);
	printf("\n");
	exit(1);
}

int main(){
	int fd;
	FILE* dst;
	MsgType msg;

	signal(SIGINT,sigIntHandler);

	if(mkfifo(SERV_FIFO,0600)<0){
		perror("mkfifo");
		exit(1);
	}

	if((fd=open(SERV_FIFO,O_RDONLY))<0){
		perror("open");
		exit(1);
	}

	while(1){
		if(read(fd,(char*)&msg,sizeof(msg))<0){
			if(errno==EINTR){
				continue;
			}
			else{
				perror("read");
				exit(1);
			}
		}
		if(msg.isWrite==0) continue;
		if((dst=fopen(msg.writer,"at"))<0){
			perror("fopen");
			exit(1);
		}

		if(fputs(msg.data,dst)<0){
			perror("fputs");
			exit(1);
		}
		fputs(" ",dst);
		fclose(dst);
		msg.isWrite=0;
	}
}
