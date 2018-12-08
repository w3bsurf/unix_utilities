#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
	FILE *file;
	int i;
	char buffer[100];

	if (argc<2) { /* Exit if no file given */
		printf("my-cat: file [file2 ...]\n");
		exit(0);
	}

	/* Open file in read mode and print contents */
	for (i=1; i<argc; i++) { /* Go through each file */
		if ((file = fopen(argv[i], "r"))==NULL) {
			printf("my-cat: cannot open file\n");
			exit(1);
		}

		while (fgets(buffer, 100, file)!=NULL) {
			printf("%s", buffer);
		}
		fclose(file);
	}
	return 0;
}
