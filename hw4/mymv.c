#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s old new\n", argv[0]);
		exit(1);
	}
	
	//argv[1]의 이름을 arvg[2]로 변경
	if (rename(argv[1],argv[2])<0)  {
		perror("rename");
		exit(1);
	}
}
