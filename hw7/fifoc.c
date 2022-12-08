#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "fifo.h"


main()
{
	char		fname[MAX_FIFO_NAME];
	int			fd, sfd, n;
	MsgType		msg;
	
	//.fifo+자신의 pid를 해서 특정이름의 specific fifo 생성
	sprintf(fname, ".fifo%d", getpid());
	if (mkfifo(fname, 0600) < 0)  {
		perror("mkfifo");
		exit(1);
	}

	//자신이 사용할 fifo
	if ((fd = open(fname, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}
	//server에 보낼 fifoㅇ
	if ((sfd = open(SERV_FIFO, O_RDWR)) < 0)  {
		perror("open");
		exit(1);
	}

	//message를 만든 뒤
	strcpy(msg.returnFifo, fname);
	sprintf(msg.data, "This is a request from %d.", getpid());
	
	//server의 fd에 write
	write(sfd, (char *)&msg, sizeof(msg));
	printf("Sent a request.....");

	//본인이 만든 fd의 fif를 기다림
	if ((n = read(fd, (char *)&msg, sizeof(msg))) < 0)  {
		perror("read");
		exit(1);
	}

	printf("Received reply: %s\n", msg.data);

	close(fd);
	close(sfd);

	//본인이 만든 fifo remove
	if (remove(fname) < 0)  {
		perror("remove");
		exit(1);
	}
}
