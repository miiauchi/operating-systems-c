/*
 * Name: Michelle Chen
 * Title: Synchronization - Bounded buffer with condition variables
 * Description: The same producer/consumer problem as prodcons_semaphore, solved
 *              with a mutex and condition variables to avoid busy-waiting.
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5

int buffer[N];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;

void *producer(void *arg) {
	int item = 1;
	while(1) {
		sleep(1);
		pthread_mutex_lock(&mutex);

		while(count == N) {
			pthread_cond_wait(&empty, &mutex);
		}

		buffer[in] = item;
		printf("Produced item %d at position %d\n", item, in);

		in = (in + 1) % N;
		count++;
		item++;

		pthread_cond_signal(&full);
		pthread_mutex_unlock(&mutex);
	}
}

void *consumer(void *arg) {
	int item;
	while(1) {
		pthread_mutex_lock(&mutex);

		while(count == 0) {
			pthread_cond_wait(&full, &mutex);
		}

		item = buffer[out];
		printf("Consumed item %d from position %d\n", item, out);

		out = (out + 1) % N;
		count--;

		pthread_cond_signal(&empty);
		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}

int main() {
	pthread_t prod, cons;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&full, NULL);
	pthread_cond_init(&empty, NULL);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&full);
	pthread_cond_destroy(&empty);

	return 0;
}
