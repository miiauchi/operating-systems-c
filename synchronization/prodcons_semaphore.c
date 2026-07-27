/*
 * Name: Michelle Chen
 * Title: Synchronization - Bounded buffer with semaphores
 * Description: Producer/consumer over a shared bounded buffer, synchronized with
 *              three semaphores: full, empty, and a mutex.
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

int buffer[N];
int in = 0;
int out = 0;

sem_t full;
sem_t empty;
sem_t mutex;

void *producer(void *arg) {
	int item = 1;
	while(1) {
		sleep(1);

		sem_wait(&empty);
		sem_wait(&mutex);

		buffer[in] = item;
		printf("Produced item %d at position %d\n", item, in);

		in = (in + 1) % N;
		item++;

		sem_post(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *arg) {
	int item;
	while(1) {
		sem_wait(&full);
		sem_wait(&mutex);

		item = buffer[out];
		printf("Consumed item %d from position %d\n", item, out);

		out = (out + 1) % N;

		sem_post(&mutex);
		sem_post(&empty);

		sleep(1);
	}
}

int main() {
	pthread_t prod, cons;

	sem_init(&full, 0, 0);
	sem_init(&empty, 0, N);
	sem_init(&mutex, 0, 1);

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	sem_destroy(&full);
	sem_destroy(&empty);
	sem_destroy(&mutex);

	return 0;
}
