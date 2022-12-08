/*===============================================================
[Program Name] :	hw3/upper.c
[Description]  :	it prints capital letter texts from argv[1] file in console.
[Input]        :	argv[1] (source file)
[Output]       :	None
[Calls]        :	None
[특기사항]     :	Usage : ./upper textfile
==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_BUF 1024

int main(int argc,char * argv[]){

	FILE *fp;
	char buf[MAX_BUF];

	if(argc!=2){
		printf("Usage: %s textfile\n",argv[0]);
		exit(1);
	}
	if((fp=fopen(argv[1],"rb"))==NULL){
		perror("fopen");
		exit(1);
	}
	while((fgets(buf,MAX_BUF,fp))!=NULL){
		for(int i=0; buf[i]; i++){
			buf[i]=toupper(buf[i]);
		}
		printf("%s",buf);
	}
	fclose(fp);
}

