/*===============================================================
[Program Name] :	hw3/tab.c
[Description]  :	it converts *.c files to *.c.t and makes tab width-4
[Input]        :	*.c files by args
[Output]       :	*.c.t
[Calls]        :	conv()
[특기사항]     :	-Usage : ./tab *.c files
==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { FALSE, TRUE };

/*===============================================================
[Function Name] :	void conv(char *fname)
[Description]   :	receive a file pointer by params and make a new file that *.c.t which has tab width-4 with same contents
[Input]         :	char *fname
[Output]        :	None
[Call By]       :	main()
[Calls]         :	None
[Given]         :	None
[Returns]       :	None
==================================================================*/
void conv(char *fname)
{
	FILE	*src, *dst;
	char	fdest[40];
	int		ch, first;

	if ((src = fopen(fname, "rt")) == NULL)  {
		perror("fopen");
		return;
	}

	//fdest에 fname을 copy하고 open
	strcpy(fdest, fname);
	strcat(fdest, ".t");
	if ((dst = fopen(fdest, "wt")) == NULL)  {
		perror("fopen");
		return;
	}

	first = TRUE;
	while ((ch = fgetc(src)) != EOF)  {
		//file을 읽으면서 \t면 4칸 띄움
		if (first && ch == '\t')  {
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
			fputc(' ', dst);
		}
		//\t가 아니면 그냥 copy
		else  {
			fputc(ch, dst);
			if (first)
				first = FALSE;
			if (ch == '\n')
				first = TRUE;
		}
	}

	fclose(src);
	fclose(dst);
}

int main(int argc, char *argv[])
{
	//모든 args에 대해 conv실행
	while (--argc)  {
		conv(argv[argc]);
	}
}