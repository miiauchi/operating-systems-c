/*
 * Name: Michelle Chen
 * Title: Synchronization - Mutex lock
 * Description: A pthread mutex ensures only one thread enters the critical
 *              section at a time.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NTHREADS 10

pthread_mutex_t mutex;

void *go(void *arg) {
	printf("Thread %ld is attempting to enter the critical section...\n", (long)arg);
	pthread_mutex_lock(&mutex);
	printf("Thread %ld is now in the critical section.\n", (long)arg);
	sleep(1);
	printf("Thread %ld is leaving the critical section.\n", (long)arg);
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[NTHREADS];
	pthread_mutex_init(&mutex, NULL);

	for(long i = 0; i < NTHREADS; i++) {
		pthread_create(&threads[i], NULL, go, (void*)i);
	}

	for(int i = 0; i < NTHREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	return 0;
}
