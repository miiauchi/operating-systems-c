# 5 - Memory (Page Replacement)

Simulations of three page-replacement algorithms, with a comparative fault-rate
study.

## Programs
- **gen_input.c** — generates a random page-reference trace for testing
- **fifo.c** — FIFO replacement (circular index)
- **lru.c** — Least Recently Used (tracks per-page access time, evicts the oldest)
- **second_chance.c** — Second-Chance / Clock (reference bits + a clock hand)

Each reads a reference stream on stdin and prints the pages that cause faults.

## Study
Benchmarked across cache sizes 10, 50, 100, 250, and 500 on a 10,000-reference
trace, comparing fault counts across the three algorithms.

## Build & run
```
make
cat accesses.txt | ./lru 100 | wc -l
```
