#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define	MAX_BUF	256

int main(int argc, char *argv[])
{
	char	buf[MAX_BUF];
	
	//buf에 현재 디렉토리를 저장ㅎ
	if (!getcwd(buf,MAX_BUF))  {
		perror("getcwd");
		exit(1);
	}

	printf("%s\n", buf);
}
