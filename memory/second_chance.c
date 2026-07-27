/*
# Name: Michelle Chen
# Date: 02/24/2026
# Title: Memory - Second-Chance (Clock) page replacement
# Description: This program simulates the Second Chance (Clock) page replacement algorithm using reference bits and prints only the page numbers that result in page faults.
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
    	int refbit[cacheSize];
    	char pageCache[100];
    	int totalFaults = 0;

    	int i;
    	int hand = 0;

    	for (i = 0; i < cacheSize; i++){
        	cache[i].pageno = -1;
        	refbit[i] = 0;
    	}

    	while (fgets(pageCache, 100, stdin)) {
        	int page_num = atoi(pageCache);
        	if (page_num == 0 && pageCache[0] != '0') {
            		continue;
        	}

        	bool foundInCache = false;
        	int foundIndex = -1;

        	for (i = 0; i < cacheSize; i++){
            		if (cache[i].pageno == page_num){
                		foundInCache = true;
                		foundIndex = i;
                		break;
            		}
        	}

        	if (foundInCache == true){
            		refbit[foundIndex] = 1;
        	} else {
            		printf("%d\n", page_num);
            		totalFaults++;

            		int emptyIndex = -1;
            		for (i = 0; i < cacheSize; i++){
                		if (cache[i].pageno == -1){
                    			emptyIndex = i;
                    			break;
                		}
            		}

            		if (emptyIndex != -1){
                		cache[emptyIndex].pageno = page_num;
                		refbit[emptyIndex] = 1;
            		} else {
                		while (refbit[hand] == 1){
                    			refbit[hand] = 0;
                    			hand++;
                    			if (hand == cacheSize){
                        			hand = 0;
                    			}
                		}

                		cache[hand].pageno = page_num;
                		refbit[hand] = 1;
	
                		hand++;
                		if (hand == cacheSize){
                    			hand = 0;
                		}
            		}
        	}
    	}

	return 0;
}
