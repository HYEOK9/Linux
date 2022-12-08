#include <stdio.h>

/*===============================================================
[Program Name] :	hw2/output.c
[Description]  :	print character, string, integer, long, float, double, memory address in console
[Input]        :	None
[Output]       :	None
[Calls]        :	None
[특기사항]     :	-Usage : ./output
==================================================================*/

int main()
{
	char c = 'a', s[] = "hello";
	int i = 100; long l = 99999;
	float f = 3.14; double d = 99.999;
	int *p = &i;
	
	printf("Output: %c %s %d %#X %ld %.4f %.2lf %p\n", c, s, i, i, l, f, d, p); //위의 값들 순서대로 출력
	putchar(c); //char 출력
	puts(s); //string 출력
}
