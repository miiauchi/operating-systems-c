CC = gcc
CFLAGS = -Wall -O2

all: read_fixed read_buffered copy_buffered copy_threaded

read_fixed: read_fixed.c
	$(CC) $(CFLAGS) -o read_fixed read_fixed.c -pthread

read_buffered: read_buffered.c
	$(CC) $(CFLAGS) -o read_buffered read_buffered.c -pthread

copy_buffered: copy_buffered.c
	$(CC) $(CFLAGS) -o copy_buffered copy_buffered.c -pthread

copy_threaded: copy_threaded.c
	$(CC) $(CFLAGS) -o copy_threaded copy_threaded.c -pthread

clean:
	rm -f read_fixed read_buffered copy_buffered copy_threaded *.o
