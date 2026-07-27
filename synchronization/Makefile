CC = gcc
CFLAGS = -Wall -O2

all: semaphore_mutex mutex_lock prodcons_semaphore prodcons_condvar

semaphore_mutex: semaphore_mutex.c
	$(CC) $(CFLAGS) -o semaphore_mutex semaphore_mutex.c -pthread

mutex_lock: mutex_lock.c
	$(CC) $(CFLAGS) -o mutex_lock mutex_lock.c -pthread

prodcons_semaphore: prodcons_semaphore.c
	$(CC) $(CFLAGS) -o prodcons_semaphore prodcons_semaphore.c -pthread

prodcons_condvar: prodcons_condvar.c
	$(CC) $(CFLAGS) -o prodcons_condvar prodcons_condvar.c -pthread

clean:
	rm -f semaphore_mutex mutex_lock prodcons_semaphore prodcons_condvar *.o
