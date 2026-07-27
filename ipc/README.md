# 2 - Inter-Process Communication

Communication between separate processes using pipes and shared memory.

## Programs
- **pipe_pipeline.c** — replicates `ls -l | more` with `pipe()`, `fork()`, and
  `dup2()` file-descriptor redirection
- **pipe_args.c** — a writer sends data through a pipe to a reader using a **1-byte
  buffer**, showing correct handling via `read()`'s returned byte count
- **pipe_producer_consumer.c** — producer/consumer exchanging values over a pipe
- **shm_producer_consumer.c** — producer/consumer over a System V **shared-memory**
  segment (`shmget`/`shmat`/`shmdt`/`shmctl`)

## Concepts
Anonymous pipes, redirecting stdin/stdout with `dup2`, the producer-consumer
pattern over two different IPC mechanisms, and shared-memory lifecycle management.

## Build & run
```
make
./pipe_args the quick brown fox
```
