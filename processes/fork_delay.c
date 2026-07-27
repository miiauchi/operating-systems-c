/*
 * Name: Michelle Chen
 * Title: Processes - fork() with user-supplied delay
 * Description: Interleaving delay is provided on the command line.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	pid_t  pid;
	int i, n;

	if (argc != 2) {
		printf("Usage: %s <delay>\n", argv[0]);
		exit(0);
	}
	n = atoi(argv[1]);

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
