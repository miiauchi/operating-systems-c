/*
 * Name: Michelle Chen
 * Title: IPC - Producer/consumer over shared memory
 * Description: One process writes numbers 1-10 into a System V shared-memory
 *              segment; another reads and prints them.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 10

int main() {
	key_t key = 1234;
	int shmid = shmget(key, SIZE * sizeof(int), IPC_CREAT | 0666);
	int *buffer = (int *) shmat(shmid, NULL, 0);

	if (fork() == 0) { /* Producer */
		for (int i = 0; i < SIZE; i++) {
			buffer[i] = i + 1;
		}
		exit(0);
	}
	else {
		wait(0); /* wait for producer */
		for (int i = 0; i < SIZE; i++) {
			printf("Consumed: %d\n", buffer[i]);
		}
		shmdt(buffer);
		shmctl(shmid, IPC_RMID, NULL);
	}
	return 0;
}
