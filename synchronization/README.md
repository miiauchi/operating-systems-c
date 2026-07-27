# 4 - Synchronization

Concurrency control primitives, culminating in the bounded-buffer problem solved
two different ways.

## Programs
- **semaphore_mutex.c** — a POSIX named semaphore guarding a critical section,
  with a `SIGINT` handler for cleanup
- **mutex_lock.c** — mutual exclusion with a `pthread_mutex`
- **prodcons_semaphore.c** — bounded-buffer producer-consumer using three counting
  semaphores (`full`, `empty`, `mutex`)
- **prodcons_condvar.c** — the same problem with a mutex + condition variables,
  avoiding busy-waiting

## Concepts
Semaphores vs. mutexes vs. condition variables, the bounded-buffer problem, and
the tradeoffs between semaphore-based and condition-variable-based solutions.

## Build & run
```
make
./prodcons_condvar
```
