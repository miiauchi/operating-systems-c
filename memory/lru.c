/*
# Name: Michelle Chen
# Date: 02/24/2026
# Title: Memory - LRU page replacement
# Description: This program simulates the Least Recently Used (LRU) page replacement algorithm. It tracks access time to replace the least recently used page and prints only page faults.
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
    	int usedTime[cacheSize];
	char pageCache[100];
    	int totalFaults = 0;

    	int i;
    	int t = 0;

    	for (i = 0; i < cacheSize; i++){
        	cache[i].pageno = -1;
        	usedTime[i] = -1;
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
        		usedTime[foundIndex] = t;
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
                		usedTime[emptyIndex] = t;
            		} else {
                		int lruIndex = 0;
                		for (i = 1; i < cacheSize; i++){
                    			if (usedTime[i] < usedTime[lruIndex]){
                        			lruIndex = i;
                    			}
                		}
                		cache[lruIndex].pageno = page_num;
                		usedTime[lruIndex] = t;
            		}	
        	}

        	t++;
    	}

	return 0;
}
