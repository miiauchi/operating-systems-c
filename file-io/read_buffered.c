/*
# Name: Michelle Chen
# Date: 03/03/2026
# Title: File I/O - Sequential read, variable buffer
# Description: Reads a file sequentially using a buffer size provided on the command line.
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static size_t parse_size(const char *s) {
    	errno = 0;
    	char *end = NULL;
    	long v = strtol(s, &end, 10);
    	if (errno != 0 || end == s || *end != '\0' || v <= 0 || v > INT_MAX) {
        	fprintf(stderr, "Invalid buffer size: %s\n", s);
        	exit(1);
    	}
    	return (size_t)v;
}

int main(int argc, char *argv[]) {
    	if (argc != 3) {
        	fprintf(stderr, "Usage: %s <input_file> <buffer_size_bytes>\n", argv[0]);
        	return 1;
    	}

    	const char *infile = argv[1];
    	size_t buf_sz = parse_size(argv[2]);

    	FILE *fp = fopen(infile, "rb");
    	if (!fp) {
        	perror("fopen");
        	return 1;
    	}

    	unsigned char *buffer = (unsigned char *)malloc(buf_sz);
    	if (!buffer) {
        	fprintf(stderr, "malloc failed for %zu bytes\n", buf_sz);
        	fclose(fp);
        	return 1;
    	}

    	while (1) {
        	size_t n = fread(buffer, 1, buf_sz, fp);
        	if (n == 0) break;
    	}

    	if (ferror(fp)) {
        	perror("fread");
        	free(buffer);
        	fclose(fp);
        	return 1;
    	}

    	free(buffer);
    	fclose(fp);
    	return 0;
}
