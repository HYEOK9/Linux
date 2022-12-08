/*===============================================================
[Program Name] :	hw3/merge.c
[Description]  :	it merges contents of 2 files into a file.
[Input]        :	argv[1] (source file), argv[2] (source file2), argv[3] (destination, create file if doesn't exist)
[Output]       :	merged file that conatins contents of sourceFile1 and sourceFile2.
[Calls]        :	None
[특기사항]     :	Usage : ./merge <sourceFile1> <sourceFile2> <destination>
==================================================================*/
#include <stdio.h>
#include <stdlib.h>

#define	MAX_BUF	1024

int main(int argc, char *argv[])
{
	FILE	*src1, *src2, *dst;
	char	buf[MAX_BUF];
	int		count;

	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source1 source2 dest\n", argv[0]);
		exit(1);
	}

	if ((src1 = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((src2 = fopen(argv[2], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst = fopen(argv[3], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while ((count = fread(buf, 1, MAX_BUF, src1)) > 0)  {
		fwrite(buf, 1, count, dst);
	}

	while ((count = fread(buf, 1, MAX_BUF, src2)) > 0)  {
		fwrite(buf, 1, count, dst);
	}

	fclose(src1);
	fclose(src2);
	fclose(dst);
}