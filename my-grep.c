#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	int i;
	char *line;
	size_t buffer_size = 100;
	FILE* file;

	if (argc<2) { /* Exit if no arguments given */
		printf("my-grep: searchterm [file ...]\n");
		exit(0);
	}

	line = (char *)malloc(buffer_size * sizeof(char));
	if (line == NULL) {
        printf("Unable to allocate buffer");
        exit(1);
    }

    if (argc==2) {
    	/* getline from stdin if no file given */ 
    	getline(&line, &buffer_size, stdin);
    	/* check line for searchterm */
    	if (strstr(line, argv[1])) {
    		printf("%s", line);
    	}
    } else {
    	/* Go through each file */
    	for (i=2; i<argc; i++) { 
			if ((file = fopen(argv[i], "r"))==NULL) {
				printf("my-grep: cannot open file\n");
				exit(1);
			}

			/* getline from file */
			while ((getline(&line, &buffer_size, file)!=-1))  {
				/* check line for searchterm */
				if (strstr(line, argv[1])) {
		    		printf("%s", line);
		    	}
			}
			printf("\n");
			
			fclose(file);
		}
    }

	free(line);
	return 0;
}