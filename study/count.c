#include <stdlib.h>
#include <stdio.h>


int main(int argc,char* argv[]){
	if(argc!=3){
		printf("Usage: %s filename character\n",argv[0]);
		exit(1);
	}
	FILE *fp;
	int curChar;
	int total=0;

	if((fp=fopen(argv[1],"rt"))==NULL){
		perror("foepn");
		exit(1);
	}

	while((curChar=fgetc(fp))!=EOF)
		if(curChar==*argv[2]) total++;

	printf("%d\n",total);
}
