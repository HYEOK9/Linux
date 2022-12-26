#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "chat.h"
#include <sys/time.h>

#define	DEBUG
#define	MAX_CLIENT	5
#define	MAX_ID		32
#define	MAX_BUF		256

typedef	struct  {
	int			sockfd;
	int			inUse;
	char		uid[MAX_ID];
} ClientType;

int Sockfd;
ClientType Client[MAX_CLIENT];


int GetID() {
	int	i;

	for (i = 0 ; i < MAX_CLIENT ; i++)  {
		if (! Client[i].inUse)  {
			Client[i].inUse = 1;
			return i;
		}
	}
}

void SendToOtherClients(int id, char *buf) {
	int		i;
	char	msg[MAX_BUF+MAX_ID];

	sprintf(msg, "%s> %s", Client[id].uid, buf);
#ifdef	DEBUG
	printf("%s", msg);
	fflush(stdout);
#endif

	for (i = 0 ; i < MAX_CLIENT ; i++)  {
		if (Client[i].inUse && (i != id))  {
			if (send(Client[i].sockfd, msg, strlen(msg)+1, 0) < 0)  {
				perror("send");
				exit(1);
			}
		}
	}
}
	

void ProcessClient(int id) {
	char	buf[MAX_BUF];
	int		n;

	if ((n = recv(Client[id].sockfd, Client[id].uid, MAX_ID, 0)) < 0)  {
		perror("recv");
		exit(1);
	}
	printf("Client %d log-in(ID: %s).....\n", id, Client[id].uid);

	while (1)  {
		if ((n = recv(Client[id].sockfd, buf, MAX_BUF, 0)) < 0)  {
			perror("recv");
			exit(1);
		}
		if (n == 0)  {
			printf("Client %d log-out(ID: %s).....\n", id, Client[id].uid);

			close(Client[id].sockfd);
			Client[id].inUse = 0;

			strcpy(buf, "log-out.....\n");
			SendToOtherClients(id, buf);

		}

		SendToOtherClients(id, buf);
	}
}


void CloseServer(int signo) {
	int		i;

	close(Sockfd);

	for (i = 0 ; i < MAX_CLIENT ; i++)  {
		if (Client[i].inUse)  {
			close(Client[i].sockfd);
		}
	}

	printf("\nChat server terminated.....\n");

	exit(0);
}

int main(int argc, char *argv[]) {
	int	newSockfd, cliAddrLen, id, one = 1;
	struct sockaddr_in	cliAddr, servAddr;
	fd_set	fdvar;
	int		count;

	signal(SIGINT, CloseServer);

	if ((Sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)  {
		perror("socket");
		exit(1);
	}

	if (setsockopt(Sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)  {
		perror("setsockopt");
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

	printf("Chat server started.....\n");

	cliAddrLen = sizeof(cliAddr);

	while (1)  {
		FD_ZERO(&fdvar);
		FD_SET(Sockfd, &fdvar);

		//기존 thread방식을 select로 변경
		if ((count = select(10, &fdvar, (fd_set *)NULL, (fd_set *)NULL, 
			(struct timeval *)NULL)) < 0)  {
			perror("select");
			exit(1);
		}
		while (count--)  {
			newSockfd = accept(Sockfd, (struct sockaddr *) &cliAddr, &cliAddrLen);

			if (newSockfd < 0)  {
				perror("accept");
				exit(1);
			}

			id = GetID();
			Client[id].sockfd = newSockfd;

			if (FD_ISSET(Sockfd, &fdvar))  {
				ProcessClient(id);
			}
		}
	}
}