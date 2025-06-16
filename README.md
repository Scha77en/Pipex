# Pipex

Pipex is a UNIX command pipeline emulator written in C for the 42 Network curriculum. It replicates the shell’s piping mechanism, allowing the user to pass the output of one command as input to another. This project focuses on process management, file descriptors, and system calls.

## Features

- Emulates shell piping: `< infile cmd1 | cmd2 > outfile`
- Handles multiple pipes and commands (bonus)
- Supports quoted arguments and PATH resolution
- Handles errors gracefully

### Bonus

- Support for any number of commands: `< infile cmd1 | cmd2 | ... | cmdn > outfile`
- Implementation of `here_doc` (heredoc) functionality

## Usage

### Basic

```bash
./pipex infile "cmd1" "cmd2" outfile
```

Equivalent to:
```bash
< infile cmd1 | cmd2 > outfile
```

### Bonus: Multiple Commands

```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdn" outfile
```

### Bonus: Here Document

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
<< LIMITER cmd1 | cmd2 >> outfile
```

## Installation

```bash
make
```

## Project Structure

- `src/` — source code
- `includes/` — header files
- `Makefile` — build instructions

## Author

- Scha77en

---
