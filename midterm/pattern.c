#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
	
	FILE * fp;

	if(argc!=3){
		printf("arg must be 3");
		exit(1);
	}

	if((fp=fopen(argv[1],"rb"))<0)
}
