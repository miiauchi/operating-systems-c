# 1 - Processes

Process creation and management with the UNIX process API.

## Programs
- **fork_basic.c** — creates a child with `fork()`; parent and child interleave output
- **fork_delay.c** — same, with a user-supplied `usleep` delay to control interleaving
- **fork_multi.c** — spawns parent + 4 children, each with its own delay, tracking roles
- **fork_exec.c** — `fork()` + `execlp("ls")` + `wait()`: the full process lifecycle

## Concepts
`fork()` return-value semantics (parent vs. child), replacing a process image with
`exec`, reaping children with `wait()`, and coordinating multiple processes.

## Build & run
```
make
./fork_delay 3000
```
