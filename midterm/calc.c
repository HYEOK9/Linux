#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char* argv[]){
	if(argc!=4){
		printf("ex) %s 11 x 22",argv[0]);
		exit(1);
	}


	if(strcmp(argv[2],"+")==0){
		printf("%d\n",atoi(argv[1])+atoi(argv[3]));
		exit(0);
	}

	else if(strcmp(argv[2],"-")==0){
		printf("%d\n",atoi(argv[1])-atoi(argv[3]));
		exit(0);
	}

	else if (strcmp(argv[2],"x")==0){
		printf("%d\n",atoi(argv[1])*atoi(argv[3]));
		exit(0);
	}

	else if (strcmp(argv[2],"/")==0){
		printf("%d\n",atoi(argv[1])/atoi(argv[3]));
		exit(0);
	}
	else
	{
		printf("%s\n","Inavlid input");
		exit(1);
	}
}
