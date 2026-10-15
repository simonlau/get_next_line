*This project has been created as part of the 42 curriculum by choolau.*

# get_next_line

## Description

This project implements a C function that returns one line per call from a file descriptor. Beyond adding a reusable function to the collection, its goal is to teach an important C concept: static variables.

Repeated calls (e.g. in a loop) read the file pointed to by the descriptor one line at a time, working for both regular files and standard input. Each returned line keeps its terminating `\n`, except a final line at end-of-file without one. The function returns `NULL` when there is nothing left to read or an error occurs.

- Prototype: `char *get_next_line(int fd);` (declared in `get_next_line.h`; helpers in `get_next_line_utils.c`)
- Only `read`, `malloc`, and `free` may be used. `libft`, `lseek()`, and global variables are forbidden.
- Reads use a compile-time `BUFFER_SIZE` (`-D BUFFER_SIZE=n`); the project must also compile without the flag, using a chosen default.

## Instructions

Compile with (buffer size 42 shown as an example):

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c <your_main>.c
```

To exercise the function, write a small test program that opens a file (or uses standard input) and calls `get_next_line()` in a loop until it returns `NULL`, freeing each returned line.

Ready-made test drivers live in `tests/` and use the vendored single-header framework `tests/tst.h` (TST by Remo Dentato, MIT, v0.7.3-rc): run `make test` for the mandatory part or `make test_bonus` for the bonus part (both honor `make BUFFER_SIZE=n test`). Unimplemented cases report as SKIP until filled in. `make fclean` removes the built test binaries.

Bonus files, when implemented, carry the `_bonus.[c/h]` suffix: `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`.

## Algorithm

Static `stash` (`char *`) holds unreturned data between calls (see `docs/GLOSSARY.md`: line / stash / refill / drain). Each call refills: `read(fd, buf, BUFFER_SIZE)` into a heap buffer (`malloc(BUFFER_SIZE+1)`, so `BUFFER_SIZE=10000000` never touches the stack), `ft_strjoin` onto the stash until `\n` is found (`ft_strchr`) or `read` hits `0`/`-1`. Then drains one line: `ft_substr` for the line plus `ft_strdup` for the remainder; empty remainder is freed so EOF returns `NULL`. Read errors free the stash and return `NULL`. Helpers are libft-adapted (`strlen/strchr/strdup/substr/strjoin`, see `docs/adr/0001-adapt-libft-instead-of-linking.md`) to keep only `read/malloc/free` as externals. Mandatory tracks a single fd; multi-fd is bonus scope.

## Resources

- Subject: `docs/get_next_line.pdf` (Get Next Line, Version 14.3) — also ingested into `wiki/42/get-next-line.md`
- `man 2 read`, `man 3 malloc`, `man 3 free`
- C static storage duration and file descriptors (any standard C reference)

AI usage: an AI assistant converted the subject PDF to Markdown (via the anydoc CLI) and ingested it into the `wiki/` knowledge base; it also drafted this README's structure and the spec-derived sections above. No project code has been generated with AI at this stage.
