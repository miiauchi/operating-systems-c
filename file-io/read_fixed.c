/*
# Name: Michelle Chen
# Date: 03/03/2026
# Title: File I/O - Sequential read, fixed 10KB buffer
# Description: Reads a file sequentially from beginning to end using a fixed 10,000-byte buffer.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    	if (argc != 2) {
        	fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        	return 1;
    	}

    	const char *infile = argv[1];
    	FILE *fp = fopen(infile, "rb");
    	if (!fp) {
        	perror("fopen");
        	return 1;
    	}

    	char buffer[10000];
    	while (1) {
        	size_t n = fread(buffer, 1, sizeof(buffer), fp);
        	if (n == 0) break;
    	}

    	if (ferror(fp)) {
        	perror("fread");
        	fclose(fp);
        	return 1;
    	}

    	fclose(fp);
    	return 0;
}
