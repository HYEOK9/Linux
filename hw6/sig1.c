#include <stdio.h>
#include <signal.h>

void
SigIntHandler(int signo)
{
	printf("Received a SIGINT signal\n");
	printf("Terminate this process\n");

	exit(0);
}

main()
{
	/* SIGINT signal handler: SigIntHandler */
	/* signal */
	
	signal(SIGINT,SigIntHandler);	//^C를 누르게되면 SigIntHandler 실행
	printf("Press ^C to quit\n");

	for ( ; ; )
		pause();
}
