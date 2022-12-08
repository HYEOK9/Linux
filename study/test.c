#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("argc != 2");
		exit(1);
	}

	FILE *src;
	if ((src = fopen(argv[1], "rt")) == NULL) {
		perror("fopen");
		exit(1);
	}

	int ch;
	int was_space = 1;
	int is_space;
	int result = 0;
	while ((ch = fgetc(src)) != EOF) {
		is_space = isspace(ch) ? 1 : 0;
		if (was_space == is_space) {
			continue;
		}
		else if (is_space) {
			was_space = 1;
			result++;
		}
		else {
			was_space = 0;
		}
	}
	printf("%d\n", result);

	fclose(src);

	return 0;
}
