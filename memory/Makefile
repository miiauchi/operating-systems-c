CC = gcc
CFLAGS = -Wall -O2

all: gen_input fifo lru second_chance

gen_input: gen_input.c
	$(CC) $(CFLAGS) -o gen_input gen_input.c

fifo: fifo.c
	$(CC) $(CFLAGS) -o fifo fifo.c

lru: lru.c
	$(CC) $(CFLAGS) -o lru lru.c

second_chance: second_chance.c
	$(CC) $(CFLAGS) -o second_chance second_chance.c

clean:
	rm -f gen_input fifo lru second_chance *.o
