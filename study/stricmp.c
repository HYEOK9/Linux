#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int stricmp_p(char* dst,char* src){
	while(*dst||*src){
		*dst=toupper(*dst);
		*src=toupper(*src);
		if(*dst>*src) return 1;
		else if(*dst<*src) return -1;
		*dst++, *src++;
	}
	return 0;
}

void main() {
	char str1[] = "Hello";
        char str2[] = "hello";
        char str3[] = "World!";
        printf("%d : %d\n", stricmp_p(str1, str2),stricmp_p(str1, str3));
}

