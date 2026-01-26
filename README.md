*This project has been created as part of the 42 curriculum by ssutarmi.*

## Description

**pipex** is a 42 curriculum project focused on reproducing the UNIX pipe mechanism by implementing the equivalent of:

```sh
< file1 cmd1 | cmd2 > file2
```

The goal is to practice process creation and coordination (`fork`, `waitpid`), inter-process communication (`pipe`), file descriptor redirections (`dup2`), command execution (`execve`), PATH resolution (`access`), and robust error handling similar to a real shell.

Bonus features (if compiled with the `bonus` target) include:
- chaining **multiple commands** through a pipeline;
- supporting **here_doc** mode (`<< LIMITER` then `>> file`).

## Instructions

### Compilation

This repository includes a custom **libft** (located in `Libft/`). The provided `Makefile` builds `Libft/libft.a` automatically and moves it to the project root before linking.

Mandatory build:
```sh
make
```

Bonus build (replaces the binary with the bonus implementation):
```sh
make bonus
```

Cleanup:
```sh
make clean     # removes libft.a (and cleans Libft/ during libft build)
make fclean    # removes libft.a and the pipex binary
make re
make rebonus
```

### Execution

#### Mandatory usage

```sh
./pipex file1 "cmd1 with options" "cmd2 with options" file2
```

Equivalent shell behavior:
```sh
< file1 cmd1 | cmd2 > file2
```

Examples:
```sh
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
```

#### Bonus usage (multiple pipes)

```sh
./pipex file1 "cmd1" "cmd2" "cmd3" ... "cmdn" file2
```

Equivalent shell behavior:
```sh
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

#### Bonus usage (here_doc)

```sh
./pipex here_doc LIMITER "cmd1" "cmd2" ... file
```

Equivalent shell behavior:
```sh
cmd1 << LIMITER | cmd2 >> file
```

Notes on here_doc behavior in this implementation:
- input is read from **stdin** until the limiter is reached;
- output is opened in **append** mode (`>>`) in here_doc mode, otherwise it is **truncated** (`>`).

## Notes and Limitations

- Command parsing is performed by splitting on spaces. This means shell-level quoting/escaping inside a command string is **not** fully supported (e.g., complex quotes, escaped spaces, nested quotes).
- Command lookup uses the `PATH` environment variable. Absolute paths (commands starting with `/`) are also supported when executable.
- Error messages are printed to mimic a shell-like style (based on `errno` / `strerror` when relevant).

## Resources

Classic references for the concepts used in this project:

- `man 2 pipe`
- `man 2 fork`
- `man 2 dup2`
- `man 2 execve`
- `man 2 waitpid`
- `man 2 open`
- `man 2 access`
- *Advanced Programming in the UNIX Environment* (Stevens & Rago)
- *The Linux Programming Interface* (Michael Kerrisk)

### AI usage disclosure

- AI was used to **draft this README.md** from the official subject requirements and the project’s current source code.
- No other AI usage is claimed in this document. If AI was used for additional tasks (e.g., design exploration, debugging assistance, implementation suggestions), update this section to specify **which tasks** and **which parts of the project** were affected, as required by the subject.
