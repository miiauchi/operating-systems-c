/*
# Name: Michelle Chen
# Date: 02/24/2026
# Title: Memory - FIFO page replacement
# Description: This program simulates the FIFO page replacement algorithm. It reads page requests from standard input and prints only the page numbers that result in page faults.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    	int pageno;
} ref_page;

int main(int argc, char *argv[]){
    	int cacheSize = atoi(argv[1]);
    	if (cacheSize <= 0) {
        	fprintf(stderr, "Usage: %s <cacheSize>\n", argv[0]);
        	return 1;
    	}

    	ref_page cache[cacheSize];
    	char pageCache[100];
    	int totalFaults = 0;

    	int i;
    	int placeInArray = 0;

    	for (i = 0; i < cacheSize; i++){
        	cache[i].pageno = -1;
    	}

    	while (fgets(pageCache, 100, stdin)) {
        	int page_num = atoi(pageCache);
        if (page_num == 0 && pageCache[0] != '0') {
            	continue;
        }

        bool foundInCache = false;
        for (i = 0; i < cacheSize; i++){
            	if (cache[i].pageno == page_num){
                	foundInCache = true;
                	break;
            	}
        }

        if (foundInCache == false){
            	printf("%d\n", page_num);

            	cache[placeInArray].pageno = page_num;
            	totalFaults++;
            	placeInArray++;
            	if (placeInArray == cacheSize){
                	placeInArray = 0;
            	}
        	}
    	}

	return 0;
}
