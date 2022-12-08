#include <stdio.h>

int main(){
	int n=10;
	while(1){
		if(n==0) break;
		for(int i=1; i<n; i++){
			printf("%d ",i);
		}
		n--;
		printf("\n");
	}
}
