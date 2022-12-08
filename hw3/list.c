/*===============================================================
[Program Name] :	hw3/list.c
[Description]  :	it prints source file's texts line by line
[Input]        :	source file (argv[1])
[Output]       :	None
[Calls]        :	None
[특기사항]     :	Usage : ./list <sourceFile>
==================================================================*/
#include <stdio.h>
#include <stdlib.h>

#define	MAX_BUF	256

int main(int argc, char *argv[])
{
	FILE	*fp;
	char	buf[MAX_BUF];
	int		line;

	if (argc != 2)  {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}

	if ((fp = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	line = 1;
	while (fgets(buf,MAX_BUF,fp)!=NULL)  {
		printf("%4d: %s", line++, buf);
	}

	fclose(fp);
}
