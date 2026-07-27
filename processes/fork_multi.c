/*
 * Name: Michelle Chen
 * Title: Processes - Multiple children
 * Description: Parent creates 4 children (parent + 4 total roles); each process
 *              uses its own delay from argv[1..5].
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int i;
	int role = 0;	/* 0 = parent, 1..4 = children */
	int delay;
	pid_t pid;

	if (argc != 6) {
		printf("Usage: %s <d1> <d2> <d3> <d4> <d5>\n", argv[0]);
		exit(0);
	}

	for (int k = 1; k <= 4; k++) {
		if (role == 0) {
			pid = fork();
			if (pid < 0) {
				fprintf(stderr, "can't fork, error %d\n", errno); exit(0);
			} if (pid == 0) {
				role = k;
			}
		}
	}

	delay = atoi(argv[role + 1]);

	for (i = 0; i < 10; i++) {
		if (role == 0)
			printf("\t \t \t I am the parent Process displaying iteration %d (delay=%d)\n", i, delay);
		else
			printf("I am child #%d displaying iteration %d (delay=%d)\n", role, i, delay);
		usleep(delay);
	}

	if (role == 0) {
		wait(NULL);
		wait(NULL);
		wait(NULL);
		wait(NULL);
	} else {
		exit(0);
	}
	return 0;
}
