#include <stdio.h>

/*===============================================================
[Program Name] :	hw2/args.c
[Description]  :	print args in order that entered by uer
[Input]        :	anyArgs..
[Output]       :	None
[Calls]        :	None
[특기사항]     :	-Usage : ./args anyArgs1 anyArgs2 ...
==================================================================*/

int main(int argc, char *argv[])
{
	int		i;

	for (i = 0 ; i < argc ; i++)
		printf("argv[%d]=%s\n", i, argv[i]); //유저가 입력한 args들을 출력
}
