#include <stdio.h>
#include <signal.h>

void
SigAlarmHandler(int signo)
{
	/* nothing to do, just return to wake up the pause */
	return;
}

unsigned int
mysleep(unsigned int nsecs)
{
	//nsecs후 SigAlrmHanler 실행
	if (signal(SIGALRM,SigAlarmHandler)==SIG_ERR)  {
		return nsecs;
	}

	//nsecs 이후 signal 보냄, 그때까지 pause
	alarm(nsecs);

	pause();

	return alarm(0);//0초후 알람 보내라. 사실상 의미없음.
}

main()
{
	printf("Wait for 5 seconds...\n");

	mysleep(5);
}
