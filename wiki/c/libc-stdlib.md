# Stdlib conversions and allocation

> Sources: Linux man-pages, 2026-02-08
> Raw: [atoi](../../raw/libft/stdlib-functions/2026-02-08-atoi-3.md); [calloc](../../raw/libft/stdlib-functions/2026-02-08-calloc-3.md)
> Updated: 2026-10-15

## Overview

Two `<stdlib.h>` workhorses behind libft: `atoi` converts a decimal prefix to `int` with no error reporting, and `calloc` allocates a zeroed array with overflow-checked multiplication. Both are `MT-Safe` (atoi is `MT-Safe locale`), Standard C library (`libc, -lc`), C11 and POSIX.1-2008.

## atoi: unchecked decimal conversion

- Synopsis: `int atoi(const char *nptr)` (with `long atol` and `long long atoll` siblings).
- Behavior is the same as `strtol(nptr, NULL, 10)`, except `atoi` does not detect errors.
- Return value is the converted value, or `0` on error; POSIX.1 leaves the error return unspecified, while glibc, musl libc, and uClibc return `0`.
- Limits: `errno` is not set, so `0` as error is indistinguishable from `0` as value; no overflow or underflow checks are done; only base-10 input converts. New programs should use the `strtol` and `strtoul` family instead.
- History: C99, POSIX.1-2001, SVr4, `4.3BSD` (C89 and POSIX.1-1996 carry only `atoi` and `atol`).

## calloc: zeroed, overflow-aware allocation

- Synopsis: `void *calloc(size_t n, size_t size)` (with `malloc`, `free`, `realloc`, `reallocarray` on the same page).
- Allocates memory for an array of `n` elements of `size` bytes each, set to zero, suitably aligned for any fitting type; returns `NULL` with `ENOMEM` on error.
- If `n` or `size` is `0`, returns a unique pointer value that can later be successfully passed to `free()`.
- If `n` times `size` would overflow, returns an error; by contrast `malloc(n * size)` would not detect the overflow and would allocate an incorrectly sized block.
- Note: Linux follows an optimistic allocation strategy — non-`NULL` is no guarantee the memory is really available; blocks above `MMAP_THRESHOLD` (`128 kB` by default) go through `mmap(2)` as a private anonymous mapping.

## See Also

- [Libft](../42/libft.md)
- [Character classification](ctype-classification.md)
- [String and memory functions](libc-string-memory.md)
