/*
 * Name: Michelle Chen
 * Title: IPC - Pipe pipeline (ls -l | more)
 * Description: Uses pipe() and two forked children with dup2() redirection to
 *              replicate the shell pipeline "ls -l | more".
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	int fds[2];
	pipe(fds);
	/* child 1 redirects stdin to downstream of pipe */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("more", "more", (char *)NULL);
	}
	/* child 2 redirects stdout to upstream of pipe */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("ls", "ls", "-l", (char *)NULL);
	}
	else {  /* parent closes both ends and waits for children */
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
}
