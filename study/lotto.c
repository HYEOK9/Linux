#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

int count=0,cur=0;
int num[6];

void sigIntHandler(int signo){
	printf("\n");
	printf("count : %d\n",count);
	num[cur]=count;
	cur++;

	if(cur==6){
		printf("Lotto number: ");
		for(int i=0; i<6; i++){
			if(i==5) printf("%d\n",num[i]);
			else printf("%d,",num[i]);
		}
		exit(1);
	}
}


void generate(){
	while(count<=45){
		if(count==45){
			count=1;
			continue;
		}
		else count++;
	}
}

int main(){
	signal(SIGINT,sigIntHandler);

	for(int i=0; i<6; i++)
		generate();
}
