# Pipex Project

## Introduction

This repository contains the Pipex project, a 42 school curriculum assignment that mimics the behavior of the Unix `pipe` command in C programming. This project challenges students to understand inter-process communication and the use of file descriptors to implement a basic version of a pipe. The bonus part of the project extends functionality to support `here_doc` feature and multiple pipes, allowing for a more complex command line data processing.

## Features

- Simulates the Unix `pipe` command to redirect the output from one process to the input of another process using file descriptors.
- Handles external commands passed as arguments.
- **Bonus**: Implements the `here_doc` functionality similar to the shell, allowing for input redirection from a delimiter.
- **Bonus**: Supports multiple pipes, enabling a chain of commands to be executed sequentially.

## Dependencies

Pipex is written in C and requires the following to compile and run:

- GCC or Clang compiler
- Make (for compiling)
- Unix-based operating system (Linux or MacOS)

## Installation

To compile the main Pipex project, follow these steps:

1. Clone the repository to your local machine:

```bash
git clone git@github.com:akhellad/pipex.git
```

2. Navigate to the cloned directory:

```bash
cd pipex
```

3. Compile the project for the main functionality:

```bash
make
```

To compile the bonus part (including `here_doc` and multipipe functionality), use the following command:

```bash
make bonus
```

This will create an executable named `pipex_bonus`.

## Usage

### Main Project

To execute the Pipex program, use the following syntax:

```bash
./pipex file1 cmd1 cmd2 file2
```

This command will take the output of `cmd1` executed on `file1` as its input and then use it as input for `cmd2`, with the final output being written to `file2`.

### Bonus Part

- For using the `here_doc` functionality, the syntax is:

```bash
./pipex_bonus here_doc DELIMITER cmd1 cmd2 file
```

- For multipipe support, allowing the execution of multiple commands in a sequence, use:

```bash
./pipex_bonus file1 cmd1 cmd2 ... cmdN file2
```

Replace `file1`, `file2`, `DELIMITER`, `cmd1`, `cmd2`, etc., with your actual filenames, delimiter, and commands.

## Credits

This project was developed by Ahmed Khelladi, a student at Ecole 42. The Pipex project demonstrates a deep understanding of Unix piping and redirection mechanisms, enhanced with the bonus features of `here_doc` and multipipe support for advanced command line data processing.
