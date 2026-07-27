/*
 * Name: Michelle Chen
 * Title: IPC - Producer/consumer over a pipe
 * Description: The producer writes numbers 1-10 into a pipe; the consumer reads
 *              and prints them.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int fds[2];
	pipe(fds);

	if (fork() == 0) { /* Producer */
		close(fds[0]);
		for (int i = 1; i <= 10; i++) {
			write(fds[1], &i, sizeof(i));
		}
		close(fds[1]);
		exit(0);
	}
	else if (fork() == 0) { /* Consumer */
		int num;
		close(fds[1]);
		while (read(fds[0], &num, sizeof(num)) > 0) {
			printf("Consumed: %d\n", num);
		}
		close(fds[0]);
		exit(0);
	}
	else {
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
