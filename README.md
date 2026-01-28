*This project has been created as part of the 42 curriculum by ssutarmi.*

# Pipex — Parallel pipeline executor (mandatory + bonus)

## Description
**Pipex** is a small UNIX pipeline runner written in C. It reproduces the shell behavior of:

```bash
< file1 cmd1 | cmd2 > file2
```

and (bonus) extends it to **multiple commands** and **here_doc**:

```bash
< file1 cmd1 | cmd2 | ... | cmdN > file2
cmd << LIMITER | cmd1 >> file
```

The goal is to practice core UNIX process primitives:
- `pipe()` to create byte-stream channels between processes
- `fork()` to spawn children
- `dup2()` to redirect standard I/O
- `execve()` to replace a process image with a command
- `wait()/waitpid()` to synchronize and retrieve exit codes

A key design choice of this version is that **children are executed in parallel** (the pipeline is “alive” end-to-end), which matches how a real shell runs pipelines.

---

## Features

### Mandatory
- `./pipex file1 cmd1 cmd2 file2`
- Reproduces: `< file1 cmd1 | cmd2 > file2`
- Handles file opening, pipe setup, forking, and `execve()`

### Bonus
- Multiple pipes / multiple commands:
  - `./pipex file1 cmd1 cmd2 ... cmdN file2`
- `here_doc` support:
  - `./pipex here_doc LIMITER cmd1 cmd2 ... cmdN file`
  - Reproduces: `cmd1 << LIMITER | cmd2 | ... >> file` (append mode)

---

## Instructions

### Build
This project is expected to ship with a 42-compliant `Makefile` (targets: `all`, `clean`, `fclean`, `re`, and `bonus`).

Typical usage:

```bash
make            # builds mandatory (./pipex)
make bonus      # builds bonus version (still usually named ./pipex)
make clean
make fclean
make re
```

> Note: exact binary names/targets depend on your Makefile (some implementations output `pipex_bonus` for the bonus target). Check `make -n` if unsure.

### Run (mandatory)
```bash
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
```

Equivalent shell commands:
```bash
< infile ls -l | wc -l > outfile
< infile grep a1 | wc -w > outfile
```

### Run (bonus)
Multiple commands:
```bash
./pipex infile "cat" "grep foo" "wc -l" outfile
# equivalent to: < infile cat | grep foo | wc -l > outfile
```

`here_doc`:
```bash
./pipex here_doc EOF "cat" "wc -l" outfile
# then type lines, finish with a line containing EOF
# equivalent to: cat << EOF | wc -l >> outfile
```

---

## Parallel execution strategy (why it matters)
A shell pipeline is **not sequential**. If you run `cmd1` to completion before starting `cmd2`, you can deadlock:

- `cmd1` writes into a pipe buffer.
- If nobody is reading yet, the pipe buffer fills (typically **tens of KiB**, often around **64 KiB** on Linux).
- Once full, `write()` blocks and `cmd1` stalls forever.

To avoid this, Pipex forks **all pipeline processes** so readers and writers run concurrently. This allows continuous streaming: as soon as `cmd1` writes, `cmd2` can read.

### Quick “parallelism” tests
These are good sanity checks that your pipeline behaves like a shell:

1) **Infinite producer + early consumer**
```bash
./pipex /dev/null "yes X" "head -n 1" out
cat out
# expected: one line "X" (or similar) and the program exits quickly
```

2) **Big output through the pipe**
```bash
./pipex /dev/null "dd if=/dev/zero bs=1K count=256 2>/dev/null" "wc -c" out
cat out
# expected: 262144 (256 * 1024) or very close depending on tool behavior
```

If a *sequential* implementation is used, tests like these are where you often observe blocking when the producer fills the pipe buffer before any consumer starts.

---

## Implementation overview

### Mandatory (2 commands)
Conceptually:
1. `pipe(pipe_fd)`
2. `fork()` **child 1** → redirects:
   - `stdin  <- open(file1)`
   - `stdout -> pipe_fd[1]`
   - `execve(cmd1)`
3. `fork()` **child 2** → redirects:
   - `stdin  <- pipe_fd[0]`
   - `stdout -> open(file2, O_TRUNC)`
   - `execve(cmd2)`
4. Parent closes both pipe ends and waits for both children.

Crucially: **both children are forked before waiting**, so they run in parallel.

### Bonus (N commands + here_doc)
A common approach is either:
- allocate `N-1` pipes up front, or
- use a **rolling pipe** pattern (track the “previous read end” `fd_in`, create a new pipe for the next stage).

This implementation uses the rolling pattern:
- `fd_in` represents the read-end feeding the next command.
- each iteration creates a fresh `pipe_fd` for the current command’s output.
- parent closes unneeded FDs immediately to prevent descriptor leaks.
- all children are forked without waiting; parent waits after the last fork.

`here_doc` is treated as a special “producer” stage:
- read from `stdin` until `LIMITER`
- write lines into the first pipe
- the last command writes to the output file in **append** mode (`>>` behavior).

---

## Error handling notes
The project expects you to “handle errors like the shell” where reasonable:
- file open failures should print a meaningful error and follow shell-like behavior
- `execve()` failures should report command-not-found / permission errors consistently

Because 42 evaluations focus heavily on robustness:
- no unexpected crashes
- no leaks
- correct `close()` discipline (avoid FD leaks that keep pipes “alive” and prevent EOF)

---

## Project files (high level)
- `main.c`, `piping.c`, `children.c` — mandatory flow (2 commands)
- `main_bonus.c`, `piping_bonus.c`, `children_bonus.c` — bonus flow (N commands + here_doc)
- `pipex.h` — data structures and prototypes
- `cleaning.c`, `utils.c` — helpers (freeing, error messages, env helpers)
- `Libft/` — custom libft (including `get_next_line` and `ft_printf` equivalent)

---

## Resources
Classic references used for this project:
- `man 2 pipe`, `man 2 fork`, `man 2 dup2`, `man 2 execve`, `man 2 waitpid`, `man 2 open`
- The Linux Programming Interface (Michael Kerrisk) — chapters on processes and pipes
- 27 video series of "Unix processes" on youtube
- My Stackoverflow account and all saved answers

### AI usage
AI was used as a **productivity aid**, not as an implementation shortcut:
- to clarify shell vs. pipeline semantics (parallelism, pipe-buffer blocking)
- to enumerate failure modes and evaluation gotchas (FD leaks, EOF behavior, wait strategy)
- to draft and structure this `README.md`

All C implementation decisions and code were written and validated by the author.
