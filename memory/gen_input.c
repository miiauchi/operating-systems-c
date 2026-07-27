/*
# Name: Michelle Chen
# Date: 02/24/2026
# Title: Memory - Reference-string generator
# Description: This program generates testInput.txt containing random page numbers to simulate page requests.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    	FILE *fp;
    	char buffer[100];
    	int i;

    	if (argc < 3) {
        	fprintf(stderr, "Usage: %s <numRequests> <maxPageNumber>\n", argv[0]);
        	return 1;
    	}

    	int numRequests = atoi(argv[1]);
    	int maxPageNumber = atoi(argv[2]);

    	if (numRequests <= 0 || maxPageNumber <= 0) {
        	fprintf(stderr, "numRequests and maxPageNumber must be > 0\n");
        	return 1;
    	}

    	fp = fopen("testInput.txt", "w");
    	if (fp == NULL) {
        	fprintf(stderr, "Error: could not open testInput.txt for writing\n");
        	return 1;
    	}

    	for (i = 0; i < numRequests; i++) {
        	sprintf(buffer, "%d\n", rand() % maxPageNumber);
        	fputs(buffer, fp);
    	}

    	fclose(fp);
    	return 0;
}
