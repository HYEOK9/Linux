#include <stdio.h>

#define	MAX_CMD		256

//입력받은 string 출력후 1초간 sleep
void
DoCmd(char *cmd)
{
	printf("Doing %s", cmd);
	sleep(1);
	printf("Done\n");
}

int main()
{
	char	cmd[MAX_CMD];

	while (1)  {
		printf("CMD> ");
		fgets(cmd, MAX_CMD, stdin);
		//user가 q로 시작하는 단어 입력시 종료	
		if (cmd[0] == 'q')
			break;

		DoCmd(cmd);
	}
}
