/*===============================================================
[Program Name] :	hw3/tcp2.c
[Description]  :	it creats copied text file from source(argv[1]) with c library functions(fgetc)
[Input]        :	argv[1] (source file), argv[2] (destination, create file if doesn't exist)
[Output]       :	coped text file which name is user's input(argv[2]), its content(text) is same with argv[1]
[Calls]        :	None
[특기사항]     :	Usage : ./tcp2 <sourceFile> <destination>
==================================================================*/
#include <stdio.h>
#include <stdlib.h>

#define	MAX_BUF	256

int main(int argc, char *argv[])
{
	FILE	*src, *dst;
	char	buf[MAX_BUF];

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source destination\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	if ((dst = fopen(argv[2], "wt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while (fgets(buf, MAX_BUF, src) != NULL)  {
		fputs(buf, dst);
	}

	fclose(src);
	fclose(dst);
}