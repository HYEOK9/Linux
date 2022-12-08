#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

#define MAX_BUF 1024

//permission정보를 담고있는 배열
char permission[8][4]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};

//file의 mode와 char *p를 인자로 받아 권한정보를 저장
void getPermission(int mode,char* p) {
	strcat(p,permission[(mode>>6)&0x7]);
	strcat(p,permission[(mode>>3)&0x7]);
	strcat(p,permission[(mode)&0x7]);
}

int main(){
	struct stat statbuf;
	DIR *dp;
	struct dirent *dep;
	struct passwd *pwd;
	struct group *g;
	int nBlock=0;

	//dp에 폴더 포인터를 저장하고 open
	if((dp=opendir("."))==NULL){
		perror("opendir");
		exit(0);
	}

	while(dep=readdir(dp)){
		//파일인지 폴더인지를 나타내는 char
		char type='-';

		//파일 정보 가져오기
		if(lstat(dep->d_name,&statbuf)<0){
			perror("lstat");
			exit(0);
		}
		//".", ".."는 생략
		if(strcmp(dep->d_name,".")==0||strcmp(dep->d_name,"..")==0) continue;
		//폴더이면 type='d'
		if(S_ISDIR(statbuf.st_mode)) type='d';

		//UID,GId가져옴
		pwd=getpwuid(statbuf.st_uid);
		g=getgrgid(statbuf.st_gid);
		//permission정보를 가져온 후 permission에 저장
		char permission[9]="";
		getPermission(statbuf.st_mode,permission);

		//block수 저장
		nBlock+=statbuf.st_blocks;
		printf("%c%s %ld %s %s %ld %s\n",type,permission,statbuf.st_nlink,pwd->pw_name,g->gr_name,statbuf.st_size,dep->d_name);
	}
	//블록크기를 512Byte로 계산했으므로 2로 나눠 1024Byte블록의 갯수 출력
	printf("total %d\n",nBlock/2);
	closedir(dp);
}
