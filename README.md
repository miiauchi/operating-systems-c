# operating-systems-c

Systems programming projects in C from my Operating Systems coursework (CSEN
121/177), spanning the core of how an OS manages processes, memory, and I/O.
Each section isolates one concept with small, focused programs.

## Contents
| Section | Topic | Key concepts |
|---|---|---|
| **1-processes** | Process management | `fork`, `exec`, `wait`, multi-process spawning |
| **2-ipc** | Inter-process communication | pipes, `dup2` redirection, shared memory, producer-consumer |
| **3-threads** | Multithreading | `pthreads`, data races, parallel matrix multiplication |
| **4-synchronization** | Concurrency control | semaphores, mutexes, condition variables |
| **5-memory** | Page replacement | FIFO, LRU, Second-Chance (Clock) + fault-rate study |
| **6-file-io** | I/O performance | buffered & threaded file copy + throughput benchmarks |

## Highlights
- **Producer-consumer, two ways** — solved with counting semaphores and again
  with condition variables, illustrating the tradeoffs between the two.
- **Page-replacement study** — three algorithms benchmarked across cache sizes
  10–500 on a 10K-reference trace, comparing fault rates.
- **File-I/O performance** — measured how buffer size (100 B–100 KB) and thread
  count (2–64) affect copy throughput.

## Building
Each section has its own `Makefile`. To build a section:
