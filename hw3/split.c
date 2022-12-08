/*===============================================================
[Program Name] :	hw3/split.c
[Description]  :	it devides contents of a source file and put them in 2 files.
[Input]        :	argv[1] (source file), argv[2] (destination, create file if doesn't exist), argv[3] (destination2)
[Output]       :	2 files that each contains half the contents of the source file.
[Calls]        :	filesize()
[특기사항]     :	Usage : ./split <sourceFile> <destination1> <destination2>
==================================================================*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define	MAX_BUF	1024

/*===============================================================
[Function Name] :	long filesize(FILE *fp)
[Description]   :	move location of current cursor in file and calculate size of file. then return it.
[Input]         :	FILE *fp
[Output]        :	long size;	//size of file 
[Call By]       :	main()
[Calls]         :	None
[Given]         :	None
[Returns]       :	long size;
==================================================================*/
long filesize(FILE *fp){
	long	cur, size;

	cur = ftell(fp);
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, cur, SEEK_SET);
	return(size);
}

int main(int argc, char *argv[])
{
	FILE	*src, *dst1, *dst2;
	char	buf[MAX_BUF];
	int		count, size;

	if (argc != 4)  {
		fprintf(stderr, "Usage: %s source dest1 dest2\n", argv[0]);
		exit(1);
	}

	if ((src = fopen(argv[1], "rb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst1 = fopen(argv[2], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}
	if ((dst2 = fopen(argv[3], "wb")) == NULL)  {
		perror("fopen");
		exit(1);
	}

	size = filesize(src) / 2;

	while (size > 0)  {
		count = (size > MAX_BUF) ?  MAX_BUF : size;
		fread(buf, 1, count, src); 
		fwrite(buf, 1, count, dst1);
		size -= count;
	}

	while ((count = fread(buf, 1, MAX_BUF, src)) > 0)  {
		fwrite(buf, 1, count, dst2);
	}

	fclose(src);
	fclose(dst1);
	fclose(dst2);
}