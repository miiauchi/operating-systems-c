# 3 - Threads

Multithreading with POSIX threads, including a classic concurrency bug and
parallel computation.

## Programs
- **thread_race_fix.c** — the classic pitfall of passing a shared loop variable's
  address to every thread, fixed by giving each thread its own argument
- **matmul_row.c** — parallel matrix multiply, one thread per **row** of the result
- **matmul_element.c** — finer-grained: one thread per **element** of the result

## Concepts
Creating and joining threads, passing per-thread arguments safely (data races),
and how thread granularity (row vs. element) affects a parallel workload.

## Build & run
```
make
./matmul_row 3 4 5
```
