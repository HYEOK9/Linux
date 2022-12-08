#include <string.h>
#include <stdio.h>

// [Program Name] : string.c (hw2)
// [Description]  : 포인터와 array로 strlen, strcpy, strcat, strcmp를 구현
// [Input]        : -
// [Output]       : strlen, strcpy, strcat, strcmp 함수 실행후 결과 값을 터미널에 출력
// [Calls]        : strlen_p, strlen_a, strcpy_p, strcpy_a, strcat_p, strcat_a, strcmp_p, strcmp_a
// [특기사항]     : -


// [Function Name] : int strlen_p(char *str)
// [Description]   : 
//     - 파라미터로 들어온 Stirng의 길이를 포인터를 이용하여 구하고 반환한다.
// [Input]         :
//     char *str;     	// value of stirng
// [Output]        :
//     int len;			//파라미터로 들어온 string의 길이
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//     파라미터로 들어온 string의 Length값을 int로 리턴
int strlen_p(char *str){
	int	len = 0;

	while (*(str+len)!='\0')  {
		len++;
	}
	return len;
}

// [Function Name] : int strlen_a(char *str)
// [Description]   : 
//     - 파라미터로 들어온 Stirng의 길이를 array를 이용하여 구하고 반환한다.
// [Input]         :
//     char *str;     	// value of stirng
// [Output]        :
//     int len;			//파라미터로 들어온 string의 길이
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//     파라미터로 들어온 string의 Length값을 int로 리턴
int strlen_a(char str[]){
	int i;

	for (i = 0 ; str[i] != '\0' ; i++)
		;
	return i;
}

// [Function Name] : void strcpy_p(char *dst, char *src)
// [Description]   : 
//     - *src의 string value를 *dst로 포인터를 이용하여 복사한다.
// [Input]         :
//     char *dst, char *src     	// destination, source of stirng
// [Output]        :
//     Nothiong
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//     Nothiong
void strcpy_p(char *dst, char *src){
	while (*src)  {
		*dst++=*src++;
	}
	*dst = *src;
}

// [Function Name] : void strcpy_p(char dst[], char src[])
// [Description]   : 
//     - *src의 string value를 *dst로 array를 이용하여 복사한다.
// [Input]         :
//     char *dst, char *src     	// destination, source of stirng
// [Output]        :
//     Nothiong
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//     Nothiong
void strcpy_a(char dst[], char src[]){
	int i;

	for (i = 0 ; i<strlen_p(src); i++)
		dst[i] = src[i];
	dst[i]=src[i];
}

// [Function Name] : void strcat_p(char *dst, char *src)
// [Description]   : 
//     - *src의 string value를 *dst뒤에 포인터를 이용하여 추가한다.
// [Input]         :
//     char *dst, char *src     	// destination, source of stirng
// [Output]        :
//     Nothiong
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//     Nothiong
void strcat_p(char *dst, char *src){
	while (*dst++)
		;
	dst--;
	while (*src)  {
		*dst++ = *src++;
	}
	*dst = *src;
}

// [Function Name] : void strcat_a(char dst[], char src[])
// [Description]   : 
//     - *src의 string value를 *dst뒤에 array를 이용하여 추가한다.
// [Input]         :
//     char *dst, char *src     	// destination, source of stirng
// [Output]        :
//     Nothiong
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//     Nothiong
void strcat_a(char dst[], char src[]){
	int i, j;

	for (i = 0 ; dst[i] != '\0' ; i++)
		;
	for (j = 0 ; src[j] != '\0' ; j++)
		dst[i+j] = src[j];
	dst[i+j]=src[j];
}

// [Function Name] : int strcmp_p(char *dst, char *src)
// [Description]   : 
//     - *src의 string value와 *dst의 string value의 값을 포인터를 이용하여 비교한다.
// [Input]         :
//     char *dst, char *src     	// 비교할 두 string value
// [Output]        :
//     Nothiong
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//dst>src면 1 리턴
//dst<src면 -1 리턴
//dst=src면 0 리턴
int strcmp_p(char *dst, char *src){

	//dst나 src가 끝날때까지 비교
	while(*dst||*src){
		//dst값이 크면 1을 리턴
		if(*dst>*src) return 1;
		//src값이 크면 -1리턴
		else if (*dst<*src) return -1;
		*dst++, *src++;
	}
	return 0;
}

// [Function Name] : int strcmp_a(char dst[], char src[])
// [Description]   : 
//     - src의 string value와 dst의 string value의 값을 array를 이용하여 비교한다.
// [Input]         :
//     char dst[], char src[]     	// 비교할 두 string value
// [Output]        :
//     Nothiong
// [Call By]       :	        
//     main()
// [Calls]         :	        
//     Nothiong
// [Given]         :
//     Nothing
// [Returns]       :
//dst>src면 1 리턴
//dst<src면 -1 리턴
//dst=src면 0 리턴
int strcmp_a(char dst[], char src[]){

	//dst나 src가 끝날때까지 비교
	for(int i=0; dst[i]||src[i]; i++){
		//dst값이 크면 1을 리턴
		if(dst[i]>src[i]) return 1;
		//src값이 크면 -1리턴
		else if(dst[i]<src[i]) return -1;
	}
	//같은 문자열이면 0 리턴
	return 0;
}

int main(){
	int		len1, len2;
	char	str1[20], str2[20];

	len1 = strlen_p("Hello");
	len2 = strlen_a("Hello");
	printf("strlen: p=%d, a=%d\n", len1, len2);

	strcpy_p(str1, "Hello");
	strcpy_a(str2, "Hello");
	printf("strcpy: p=%s, a=%s\n", str1, str2);

	strcat_p(str1, ", World!");
	strcat_a(str2, ", World!");
	printf("strcat: p=%s, a=%s\n", str1, str2);

	printf("strcmp: p=%d, a=%d\n",strcmp_p("Hello","Hello"),strcmp_a("Hello","Hello"));
	printf("strcmp: p=%d, a=%d\n",strcmp_p("Hello","Hello, World!"),strcmp_a("Hello","Hello, World!"));
	printf("strcmp: p=%d, a=%d\n",strcmp_p("Hello, World!","Hello"),strcmp_a("Hello, World!","Hello"));
}
