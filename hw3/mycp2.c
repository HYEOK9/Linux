/*===============================================================
[Program Name] :	hw3/mycp2.c
[Description]  :	it creats copied binary file from source(argv[1]) with c library functions (fread,fwrite)
[Input]        :	argv[1] (source file), argv[2] (destination, create file if doesn't exist)
[Output]       :	coped file which name is user's input(argv[2]), its content is same with argv[1]
[Calls]        :	None
[특기사항]     :	Usage : ./mycp2 <sourceFile> <destination>
==================================================================*/
#include <stdio.h>
#include <stdlib.h>

#define	MAX_BUF	1024

int main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];
	int		count;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst);
	}

	fclose(src);
	fclose(dst);
}