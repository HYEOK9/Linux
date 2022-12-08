#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#define	MAX_PATH	256

void JustDoIt(char *path) {
	DIR				*dp;
	struct dirent	*dep;
	struct stat		statbuf;
	char			fullpath[MAX_PATH];

	//path이름의 directory를 open하고 그 pointer를 dp에 저장
	if ((dp = opendir(path)) == NULL)  {
		perror("opendir");
		exit(0);
	}

	//path출력
	printf("\n%s:\n", path);
	
	//폴더 내의 파일, 디렉토리 이름 출력
	while (dep = readdir(dp))  {
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;
		printf("%s\n", dep->d_name);
	}

	//dp 초기화
	rewinddir(dp);

	//다시 읽으면서
	while (dep = readdir(dp))  {
		if (strcmp(".", dep->d_name) == 0 || strcmp("..", dep->d_name) == 0)
			continue;
		//path의 이름을 업데이트 
		strcpy(fullpath, path);
		strcat(fullpath, "/");
		strcat(fullpath, dep->d_name);

		//파일 읽기 오류시 종료
		if (lstat(fullpath,&statbuf)<0)  {
			perror("lstat");
			exit(1);
		}

		//directory인경우 재귀적으로 실행
		if (S_ISDIR(statbuf.st_mode))  {
			JustDoIt(fullpath);
		}
	}
	
	//폴더 닫기
	closedir(dp);
}

int main() {
	JustDoIt(".");
}
