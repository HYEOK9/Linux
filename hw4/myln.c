#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destinaion\n", argv[0]);
		exit(1);
	}
	
	//argv[2]에 argv[1]의 hardlink 생성
	if (link(argv[1],argv[2]) < 0)  {
		perror("link");
		exit(1);
	}
}
