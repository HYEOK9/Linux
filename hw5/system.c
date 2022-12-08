#include <stdio.h>
#include <stdlib.h>

int main()
{
	int		status;
	
	//cli에서 "date"입력한 것과 동일하게 동작
	if ((status = system("date")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	//nosuchcommand라는 command는 없음
	if ((status = system("nosuchcommand")) < 0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);

	//cli에서 "who; exit 44"를 입력한 것과 ㄱ동일하게 동작
	/* $ who; exit 44 */
	if ((status=system("who; exit 44"))<0)  {
		perror("system");
		exit(1);
	}
	printf("exit status = %d\n", status);
}
