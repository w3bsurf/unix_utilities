#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    FILE *file;
    int i, j, count;
    char c;

    if (argc<2) { /* Exit if no file given */
        printf("my-unzip: file [file2 ...]\n");
        exit(1);
    }

    /* Go through each file */
    for (i = 1; i<argc; i++) {
        if ((file = fopen(argv[i], "r"))==NULL) {
            printf("my-unzip: cannot open file\n");
            exit(1);
        }
        count = 0;
        while (1) {
            /* Loop until end of file */ 
            if (feof(file)) {
                break;
            }
            /* Read count and char from file */
            fread(&count, 4, 1, file);
            fread(&c, 1, 1, file);
            /* Print each char times count */
            for (j = 0; j<count; j++) {
                printf("%c", c);
            }
            count = 0;
        }
        fclose(file);
    }    
    return 0;
}