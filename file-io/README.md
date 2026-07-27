# 6 - File I/O Performance

How buffer size and threading affect file read/copy throughput.

## Programs
- **read_fixed.c** — sequential read with a fixed 10 KB buffer (baseline)
- **read_buffered.c** — sequential read with a command-line buffer size
- **copy_buffered.c** — file copy (read + write) with a variable buffer
- **copy_threaded.c** — concurrent copy to multiple outputs with `pthreads`,
  with robust argument parsing and per-thread error handling

## Study
Test files from 100 KB to 100 MB, swept across buffer sizes (100 B - 100 KB) and
thread counts (2 - 64), timed to measure throughput.

## Build & run
```
make
./copy_threaded file1.txt 10000 8
```
