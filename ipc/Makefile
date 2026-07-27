CC = gcc
CFLAGS = -Wall -O2

all: pipe_pipeline pipe_args pipe_producer_consumer shm_producer_consumer

pipe_pipeline: pipe_pipeline.c
	$(CC) $(CFLAGS) -o pipe_pipeline pipe_pipeline.c

pipe_args: pipe_args.c
	$(CC) $(CFLAGS) -o pipe_args pipe_args.c

pipe_producer_consumer: pipe_producer_consumer.c
	$(CC) $(CFLAGS) -o pipe_producer_consumer pipe_producer_consumer.c

shm_producer_consumer: shm_producer_consumer.c
	$(CC) $(CFLAGS) -o shm_producer_consumer shm_producer_consumer.c

clean:
	rm -f pipe_pipeline pipe_args pipe_producer_consumer shm_producer_consumer *.o
