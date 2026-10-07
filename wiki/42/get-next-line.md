# get_next_line

> Sources: 42 School, Unknown
> Raw: [Get Next Line — Subject (Version 14.3)](../../raw/42/get-next-line-subject-v14-3.md)
> Updated: 2026-10-07

## Overview

get_next_line is a 42 curriculum project that implements a C function returning one line per call from a file descriptor, teaching static variables along the way. The subject pins the exact prototype, allowed functions, build flags, and edge-case behavior, plus bonus and README requirements.

## Mandatory spec

- Prototype: `char *get_next_line(int fd);`, declared at minimum in `get_next_line.h`; helpers live in `get_next_line_utils.c`. Files to submit, at the repo root: `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`.
- Only `read`, `malloc`, and `free` may be used externally. `libft`, `lseek()`, and global variables are forbidden.
- Repeated calls yield the file one line at a time, working for both regular files and standard input. Each returned line keeps its terminating `\n`, except a final line at end-of-file without one. Nothing left to read or any error returns `NULL`.
- Reads go through a compile-time `BUFFER_SIZE` passed as `-D BUFFER_SIZE=n`, e.g. `cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c`. The project must also compile without the flag, using a default of the author's choice; evaluators vary the value to test edge cases such as `9999`, `1`, and `10000000`.
- Read as little as possible per call: return the current line once a newline is found instead of slurping the whole file first.
- Undefined behavior cases: the file changes between calls before `read()` hits end-of-file, and reading a binary file (which may still be handled in some logical way).

## Bonus

Requires a single static variable and simultaneous state for multiple file descriptors (e.g. interleaved reads from fd 3, 4, and 5 without losing track). Bonus files use the `_bonus.[c\h]` suffix: `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`. Bonus is only assessed if the mandatory part is perfect.

## README and evaluation

- A root `README.md` is required, opening with an italicized attribution line naming the authors logins, followed by Description, Instructions, and Resources sections (the latter documenting AI usage by task and part), plus a detailed justification of the chosen algorithm. English is recommended.
- Common rules: C with the Norm, no crashes, no leaks, a Makefile with `$(NAME)`, `all`, `clean`, `fclean`, `re` (and `bonus` when applicable), work submitted to the assigned Git repo, Deepthought grading after peer evaluation.
- Defense tips: buffer size and line size vary widely, and file descriptors are not only regular files. Evaluation may include a small live modification to verify understanding. Version covered here: 14.3.
