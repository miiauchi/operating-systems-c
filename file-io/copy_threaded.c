/*
# Name: Michelle Chen
# Date: 03/03/2026
# Title: File I/O - Threaded copy to multiple outputs
# Description: Copies an input file to multiple output files concurrently using pthreads.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>

typedef struct {
    	const char *infile;
    	size_t buf_sz;
    	int tid;
} thread_arg_t;

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

static int parse_int(const char *s) {
    	errno = 0;
    	char *end = NULL;
    	long v = strtol(s, &end, 10);
    	if (errno != 0 || end == s || *end != '\0' || v <= 0 || v > INT_MAX) {
        	fprintf(stderr, "Invalid integer: %s\n", s);
        	exit(1);
    	}
    	return (int)v;
}

static void make_outname(char *out, size_t outlen, const char *infile, size_t buf_sz, int tid) {
    	snprintf(out, outlen, "copy_%s_buf%zu_t%02d.out", infile, buf_sz, tid);
}

static void *copy_worker(void *argp) {
    	thread_arg_t *arg = (thread_arg_t *)argp;

    	FILE *in = fopen(arg->infile, "rb");
    	if (!in) {
        	perror("fopen input");
        	return (void *)1;
    	}

    	char outname[512];
    	make_outname(outname, sizeof(outname), arg->infile, arg->buf_sz, arg->tid);

    	FILE *out = fopen(outname, "wb");
    	if (!out) {
        	perror("fopen output");
        	fclose(in);
        	return (void *)1;
    	}

    	unsigned char *buffer = (unsigned char *)malloc(arg->buf_sz);
    	if (!buffer) {
        	fprintf(stderr, "malloc failed for %zu bytes\n", arg->buf_sz);
        	fclose(in);
        	fclose(out);
        	return (void *)1;
    	}

    	while (1) {
        	size_t nread = fread(buffer, 1, arg->buf_sz, in);
        	if (nread == 0) break;

        	size_t nwritten = fwrite(buffer, 1, nread, out);
        	if (nwritten != nread) {
            		perror("fwrite");
            		free(buffer);
            		fclose(in);
            		fclose(out);
            		return (void *)1;
        	}
    	}

    	if (ferror(in)) {
        	perror("fread");
        	free(buffer);
        	fclose(in);
        	fclose(out);
        	return (void *)1;
    	}
	
    	free(buffer);
    	fclose(in);
    	fclose(out);
    	return (void *)0;
}

int main(int argc, char *argv[]) {
    	if (argc != 4) {
        	fprintf(stderr, "Usage: %s <input_file> <buffer_size_bytes> <num_threads>\n", argv[0]);
        	return 1;
    	}

    	const char *infile = argv[1];
    	size_t buf_sz = parse_size(argv[2]);
    	int nthreads = parse_int(argv[3]);

    	if (nthreads <= 0) {
        	fprintf(stderr, "num_threads must be > 0\n");
        	return 1;
    	}

    	pthread_t *threads = (pthread_t *)calloc((size_t)nthreads, sizeof(pthread_t));
    	thread_arg_t *args = (thread_arg_t *)calloc((size_t)nthreads, sizeof(thread_arg_t));
    	if (!threads || !args) {
        	fprintf(stderr, "calloc failed\n");
        	free(threads);
        	free(args);
        	return 1;
    	}

    	for (int i = 0; i < nthreads; i++) {
        	args[i].infile = infile;
        	args[i].buf_sz = buf_sz;
        	args[i].tid = i;
        	int rc = pthread_create(&threads[i], NULL, copy_worker, &args[i]);
        	if (rc != 0) {
            		fprintf(stderr, "pthread_create failed (rc=%d)\n", rc);
            		free(threads);
            		free(args);
            		return 1;
        	}
    	}

    	int any_fail = 0;
    	for (int i = 0; i < nthreads; i++) {
        	void *ret = NULL;
        	pthread_join(threads[i], &ret);
        	if (ret != 0) any_fail = 1;
    	}

    	free(threads);
    	free(args);
    	return any_fail ? 1 : 0;
}
