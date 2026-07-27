CC = gcc
CFLAGS = -Wall -O2

all: fork_basic fork_delay fork_multi fork_exec

fork_basic: fork_basic.c
	$(CC) $(CFLAGS) -o fork_basic fork_basic.c

fork_delay: fork_delay.c
	$(CC) $(CFLAGS) -o fork_delay fork_delay.c

fork_multi: fork_multi.c
	$(CC) $(CFLAGS) -o fork_multi fork_multi.c

fork_exec: fork_exec.c
	$(CC) $(CFLAGS) -o fork_exec fork_exec.c

clean:
	rm -f fork_basic fork_delay fork_multi fork_exec *.o
