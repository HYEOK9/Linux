#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp.h"

int sockfd;
int *n;
struct sockaddr_in servAddr;

int Calc(int number){

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (connect(sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("connect");
		exit(1);
	}

	*n=number;

	if (write(sockfd, (int *)&n, sizeof(n)) < 0)  {
		perror("write");
		exit(1);
	}

	if (read(sockfd, (int *)&n, sizeof(n)) < 0)  {
		perror("read");
		exit(1);
	}

	printf("Calc : %d\n",*n);
	close(sockfd);
	return *n;
}

int main(int argc, char* argv[]){

	int inputNumber=atoi(argv[1]);
	Calc(inputNumber);
	exit(1);
}
