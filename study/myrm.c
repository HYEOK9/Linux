#include <stdlib.h>
#include <stdio.h>

int main(int argc,char* argv[]){
	
	if(argc<2){
		printf("Usage: ./%s filesToRemove\n",argv[0]);
		exit(1);
	}

	for(int i=1; i<argc; i++){
		remove(argv[i]);
	}
}
