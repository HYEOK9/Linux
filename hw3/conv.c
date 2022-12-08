/*===============================================================
[Program Name] :	hw3/conv.c
[Description]  :	read text file and write in binary file by record
[Input]        :	argv[1] (sourceFile), argv[2] (destination, create file if doesn't exist)
[Output]       :	None
[Calls]        :	None
[특기사항]     :	-Usage : ./conv <sourceFile> <destinaion>
					-write by record
==================================================================*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "record.h"

int main(int argc, char *argv[])
{
	FILE	*src, *dst;
	Record	rec;

	if (argc != 3)  {
		fprintf(stderr, "Usage: %s source dest\n", argv[0]);
		exit(1);
	}

	//text file read mode로 open
	if ((src = fopen(argv[1], "rt")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	//binary file write mode로 open
	if ((dst = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	while (fgets(rec.stud, SMAX, src))  {
		*strchr(rec.stud, '\n') = '\0';
		fgets(rec.num, DMAX, src);
		*strchr(rec.num, '\n') = '\0';
		fgets(rec.dept, DMAX, src);
		*strchr(rec.dept, '\n') = '\0';

		fwrite(&rec, sizeof(rec), 1, dst);
	}

	fclose(src);
	fclose(dst);
}