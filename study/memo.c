#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "fifo.h"

int main(int argc,char* argv[]){
	
	int sfd;
	MsgType msg;

	if(argc==2){
		char cmd[32]="cat ";
		char writer[32];
		strcpy(writer,argv[1]);
		strcat(cmd,writer);
		system(cmd);
		printf("\n");
		exit(1);
	}

	strcpy(msg.writer,argv[1]);
	strcpy(msg.data,argv[2]);

	if ((sfd=open(SERV_FIFO,O_WRONLY))<0){
		perror("open");
		exit(1);
	}
	msg.isWrite=1;

	write(sfd,(char*)&msg,sizeof(msg));
	close(sfd);
}
