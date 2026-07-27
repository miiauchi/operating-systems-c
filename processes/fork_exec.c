/*
 * Name: Michelle Chen
 * Title: Processes - fork() + exec()
 * Description: Forks once; the child runs "ls" via execlp and the parent waits
 *              for it to terminate before exiting.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main() {
	pid_t pid;

	printf("\n Before forking.\n");
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(0);
	}

	if (pid == 0) {
		execlp("/bin/ls", "ls", (char *)0);
		fprintf(stderr, "execlp failed, error %d\n", errno);
		exit(1);
	} else {
		wait(NULL);
		printf("Child has completed the task! \n");
		exit(0);
	}
}
