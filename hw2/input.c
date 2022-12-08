#include <stdio.h>

/*===============================================================
[Program Name] :	hw2/input.c
[Description]  :	get input character, string, integer, long, float, double from user and print it in console
[Input]        :	None
[Output]       :	None
[Calls]        :	None
[특기사항]     :	-Usage : ./input
==================================================================*/

int main()
{
	char c, s[80];
	int i; long l;
	float f; double d;
	
	scanf("%c %s %d %ld %f %lf", &c, s, &i, &l, &f, &d); //유저로 부터 각각의 type들을 입력받고
	printf("Output: %c %s %d %ld %.4f %.2lf\n", c, s, i, l, f, d); //출력

	c = getchar(); //char 입력 받음
	putchar(c);//char 출력

	gets(s);//문자열 입력 받음
	puts(s);//문자열 출력
}