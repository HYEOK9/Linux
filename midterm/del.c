#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void del(char str[], char c){
	
	for(int i=0; i<strlen(str); i++){
		if(str[i]!=c) printf("%c",str[i]);
	}
	printf("\n");
}

int main(){
	char str[20]="Hello";
	del(str,'l');
}
