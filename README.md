*This project has been created as part of the 42 curriculum by mutzou and hesainte*

# Minishell — 42 Project

## 💡 Overview

**Minishell** is a simplified **Unix shell** written in C, designed to reproduce the core behavior of **Bash**.

The project focuses on understanding how a shell works internally, from reading user input to parsing commands, managing processes, handling pipes and redirections, and interacting with environment variables.

## ⚙️ Features

### Interactive Prompt

- Displays a prompt and waits for user input.

- Supports command history through the readline library.

### Command Execution

- Executes external programs.

- Handles environment variables and executable paths.

### Built-in Commands

- Implements the required shell built-ins.

### Pipes & Redirections

- Supports pipes between commands.

- Handles input/output redirections.

### Environment Management

- Handles environment variables.

- Supports shell environment manipulation through built-in commands.

### Signal Handling

- Manages signals appropriately in both the interactive shell and child processes.

## 🖥️ Usage

Launch the shell after compilation:
```bash
./minishell
```

Once launched, the shell provides an interactive prompt where commands can be entered and executed.

Example:
```bash
$ ./minishell
minishell$ echo "Hello World"
Hello World
minishell$ ls -la | grep minishell
```

## 🚀 Getting Started
### Compilation

Compile the project using the provided Makefile:
```bash
make
```

To remove object files:
```bash
make clean
```

To remove all generated files:
```bash
make fclean
```

To recompile the project from scratch:
```bash
make re
```
## 🛠️ Methodology & Resources
### 🔍 Learning & Documentation

The project required understanding how Unix shells operate, particularly process creation, command execution, file descriptors, pipes, redirections, signals, and environment variables.

Resources used during development:

**Minishell Guide:** https://42-cursus.gitbook.io/guide/3-rank-03/minishell/functions

**Minishell Documentation:** https://minishell.org/cd__builtin_8c.html

**Minishell Tips & Advice:** https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b

### 🧪 Testing & Debugging
#### Valgrind

Valgrind can be used to detect memory leaks and open file descriptors:
```bash
valgrind --leak-check=full --track-fds=yes --suppressions=readline.supp --show-leak-kinds=all ./minishell
```
Created by

Muti Zou (Mutzou) & Heidi Sainte-Catherine (hesainte)