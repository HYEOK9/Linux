/*===============================================================
[Program Name] :	hw3/hole.c
[Description]  :	create file name is "file.hole" which size is 1024 bytes
[Input]        :	None
[Output]       :	file.hole
[Calls]        :	None
[특기사항]     :	-Usage : ./hole
					-file.hole is empty file
==================================================================*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int 	fd;
	char	ch = '\0';

	if ((fd = creat("file.hole", 0400)) < 0)  {
		perror("creat");
		exit(1);
	}

	if (lseek(fd, 1023, SEEK_SET) < 0)  {
		perror("lseek");
		exit(1);
	}
	write(fd, &ch, 1);

	close(fd);
}
