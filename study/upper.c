#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
	char a[8]="hello, ";
	char b[7]="world!";
	for(int i=0; i<strlen(a); i++) printf("%c",toupper(a[i]));
	for(int i=0; i<strlen(b); i++) printf("%c",toupper(b[i]));	
	printf("\n");
}
