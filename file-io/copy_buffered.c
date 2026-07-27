/*
# Name: Michelle Chen
# Date: 03/03/2026
# Title: File I/O - File copy, variable buffer
# Description: Copies an input file to a newly created output file using sequential fread/fwrite with a buffer size provided on the command line.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

static void make_outname(char *out, size_t outlen, const char *infile, size_t buf_sz) {
    	snprintf(out, outlen, "copy_%s_buf%zu.out", infile, buf_sz);
}

int main(int argc, char *argv[]) {
    	if (argc != 3) {
        	fprintf(stderr, "Usage: %s <input_file> <buffer_size_bytes>\n", argv[0]);
        	return 1;
    	}

    	const char *infile = argv[1];
    	size_t buf_sz = parse_size(argv[2]);

    	FILE *in = fopen(infile, "rb");
    	if (!in) { perror("fopen input"); return 1; }

    	char outname[512];
    	make_outname(outname, sizeof(outname), infile, buf_sz);

    	FILE *out = fopen(outname, "wb");
    	if (!out) { perror("fopen output"); fclose(in); return 1; }

    	unsigned char *buffer = (unsigned char *)malloc(buf_sz);
    	if (!buffer) {
        	fprintf(stderr, "malloc failed for %zu bytes\n", buf_sz);
        	fclose(in);
        	fclose(out);
        	return 1;
    	}

    	while (1) {
        	size_t nread = fread(buffer, 1, buf_sz, in);
        	if (nread == 0) break;

        	size_t nwritten = fwrite(buffer, 1, nread, out);
        	if (nwritten != nread) {
            		perror("fwrite");
            		free(buffer);
            		fclose(in);
            		fclose(out);
            		return 1;
        	}
    	}

    	if (ferror(in)) {
        	perror("fread");
        	free(buffer);
        	fclose(in);
        	fclose(out);
        	return 1;
    	}

    	free(buffer);
    	fclose(in);
    	fclose(out);
    	return 0;
}
