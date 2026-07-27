CC = gcc
CFLAGS = -Wall -O2

all: thread_race_fix matmul_row matmul_element

thread_race_fix: thread_race_fix.c
	$(CC) $(CFLAGS) -o thread_race_fix thread_race_fix.c -pthread

matmul_row: matmul_row.c
	$(CC) $(CFLAGS) -o matmul_row matmul_row.c -pthread

matmul_element: matmul_element.c
	$(CC) $(CFLAGS) -o matmul_element matmul_element.c -pthread

clean:
	rm -f thread_race_fix matmul_row matmul_element *.o
