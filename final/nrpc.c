#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "tcp.h"

int Sockfd;

int main(){
	int			newSockfd, cliAddrLen;
	int *n;
	int result=0;
	struct sockaddr_in	cliAddr, servAddr;

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	bzero((char *)&servAddr, sizeof(servAddr));
	servAddr.sin_family = PF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(SERV_TCP_PORT);

	if (bind(Sockfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0)  {
		perror("bind");
		exit(1);
	}

	listen(Sockfd, 5);

	while(1){
		newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);
		if (newSockfd < 0)  {
			perror("accept");
			exit(1);
		}
		
		if (read(newSockfd, (int *)&n, sizeof(n)) < 0)  {
			perror("read");
			exit(1);
		}

		for(int i=0; i<*n; i++) result+=i;
		*n=result;
		printf("Calc = %d\n",*n);

		if (write(newSockfd, (int *)&n, sizeof(n)) < 0)  {
			perror("write");
			exit(1);
		}

		close(newSockfd);
	}
}
