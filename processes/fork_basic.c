/*
 * Name: Michelle Chen
 * Title: Processes - Basic fork()
 * Description: Creates a child process with fork(); parent and child each loop,
 *              interleaving their output.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main() {
	pid_t  pid;
	int i, n = 3000; /* delay in microseconds */
	printf("\n Before forking.\n");
	pid = fork();
	if (pid < 0) {
		fprintf(stderr, "can't fork, error %d\n", errno);
		exit(0);
	}
	if (pid){
		for (i=0;i<10;i++) {
			printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
			usleep(n);
		}
		wait(NULL);
	}
	else{
		for (i=0;i<10;i++) {
			printf("I am the child process displaying iteration %d\n",i);
			usleep(n);
		}
	}
	return 0;
}
