#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	FILE *file;
	char c, *line;
	int i, j, count, len;
	size_t buffer_size = 100;

	if (argc<2) { /* Exit if no file given */
		printf("my-zip: file [file2 ...]\n");
		exit(1);
	}

	line = (char *)malloc(buffer_size * sizeof(char));
	if (line == NULL) {
	    printf("Unable to allocate buffer");
	    exit(1);
	}

	/* Go through each file */
	for (i=1; i<argc; i++) {
		if ((file = fopen(argv[i], "r"))==NULL) {
			printf("my-zip: cannot open file\n");
			exit(1);
		}

		/* getline from file */
		while ((getline(&line, &buffer_size, file)!=-1))  {
			c = line[0];
			count = 1;
			len = strlen(line); 
			/* Iterate through line char by char and count consecutive chars */
		    for (j=0; j<len; j++) { 
		    	c = line[j];
		        if (line[j] != line[j+1]) { /* Check when char changes */
		    		/* Write Count in 4 bytes and char in 1 byte */
		        	fwrite(&count, 4, 1, stdout);
		        	fwrite(&c, 1, 1, stdout);
		        	count = 0;
		        }
		        count++;         
			} 
		}
		fclose(file);
	}
	free(line);
	
	return 0;
}