#include <stdio.h>

int main(int argc,char* argv[]){
	if(argc!=2){
		printf("Usage: %s, integer",argv[0]);
		exit(1);
	}
	printf("%d\n",atoi(argv[1])*atoi(argv[1]));
}
