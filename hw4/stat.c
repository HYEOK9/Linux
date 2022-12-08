#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat	statbuf;
	char		*mode;
	int			i;

	for (i = 1 ; i < argc ; i++)  {
		printf("%s: ", argv[i]);	//argv들의 속성을 출력
		if (lstat(argv[i], &statbuf) < 0)  {	//에러시 다음argv로
			perror("lstat");
			continue;
		}
		if (S_ISREG(statbuf.st_mode))//regularFile인지
			mode = "regular";
		else if (S_ISDIR(statbuf.st_mode))//directory인지
			mode = "directory";
		else if (S_ISCHR(statbuf.st_mode))//character special file인지
			mode = "character special";
		else if (S_ISBLK(statbuf.st_mode))//block special file인지
			mode = "block special";
		else if (S_ISFIFO(statbuf.st_mode))//FIFO file인지
			mode = "FIFO";
		else if (S_ISLNK(statbuf.st_mode))//symbolic link file인지
			mode = "symbolic link";
		else if (S_ISSOCK(statbuf.st_mode))//socket file인지
			mode = "socket";
		printf("%s\n", mode);
		printf("\tst_mode = %d\n", statbuf.st_mode);
		printf("\tst_ino = %ld\n", statbuf.st_ino);
		printf("\tst_dev = %ld\n", statbuf.st_dev);
		printf("\tst_rdev = %ld\n", statbuf.st_rdev);
		printf("\tst_nlink = %ld\n", statbuf.st_nlink);
		printf("\tst_uid = %d\n", statbuf.st_uid);
		printf("\tst_gid = %d\n", statbuf.st_gid);
		printf("\tst_size = %ld\n", statbuf.st_size);
		printf("\tst_atime = %ld\n", statbuf.st_atime);
		printf("\tst_mtime = %ld\n", statbuf.st_mtime);
		printf("\tst_ctime = %ld\n", statbuf.st_ctime);
		printf("\tst_blksize = %ld\n", statbuf.st_blksize);
		printf("\tst_blocks = %ld\n", statbuf.st_blocks);
	}
}
