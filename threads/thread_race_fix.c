/*
 * Name: Michelle Chen
 * Title: Threads - Race condition fix
 * Description: The common pitfall is passing &i (a shared address) to every
 *              thread; this version gives each thread its own copy via ids[i]
 *              so each prints a correct, unique iteration value.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *go(void *);
#define NTHREADS 10

pthread_t threads[NTHREADS];
int ids[NTHREADS];

int main() {
	int i;
	for (i = 0; i < NTHREADS; i++) {
		ids[i] = i;
		pthread_create(&threads[i], NULL, go, &ids[i]);
	}

	for (i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i],NULL);
		printf("Thread %d returned\n", i);
	}

	printf("Main thread done.\n");
	return 0;
}

void *go(void *arg) {
	printf("Hello from thread %lu with iteration %d\n", (unsigned long) pthread_self(), *(int *)arg);
	pthread_exit(0);
}
