# String and memory functions

> Sources: Linux man-pages, 2026-08-10; Linux man-pages, 2026-07-11; Linux Kernel API, Unknown
> Raw: [bzero](../../raw/libft/string-functions/2026-08-10-bzero-3.md); [memchr](../../raw/libft/string-functions/2026-08-10-memchr-3.md); [memcmp](../../raw/libft/string-functions/2026-08-10-memcmp-3.md); [memcpy](../../raw/libft/string-functions/2026-08-10-memcpy-3.md); [memmove](../../raw/libft/string-functions/2026-08-10-memmove-3.md); [memset](../../raw/libft/string-functions/2026-08-10-memset-3.md); [strchr](../../raw/libft/string-functions/2026-08-10-strchr-3.md); [strdup](../../raw/libft/string-functions/2026-08-10-strdup-3.md); [strlcpy](../../raw/libft/string-functions/2026-07-11-strlcpy-3.md); [strlen](../../raw/libft/string-functions/2026-08-10-strlen-3.md); [strncmp](../../raw/libft/string-functions/2026-08-10-strncmp-3.md); [strnstr](../../raw/libft/string-functions/strnstr.md); [strrchr](../../raw/libft/string-functions/2026-08-10-strrchr-3.md)
> Updated: 2026-10-15

## Overview

Libc splits byte handling into two families: `str*` functions that stop at the terminating null byte, and `mem*` functions that operate on exactly `n` bytes with each byte interpreted as `unsigned char`. All are `MT-Safe`, live in `Standard C library (libc, -lc)`, and follow the C11 and POSIX.1-2008 standards, except `bzero` (no standard, removed from POSIX) and `strlcpy` (POSIX.1-2024).

## Length and fill

- `strlen(const char *s)` returns the byte count excluding the terminating null byte.
- `memset(void *a, int c, size_t n)` fills the first `n` bytes with constant byte `c` and returns a pointer to `a`.
- `bzero(void *a, size_t n)` from `<strings.h>` writes zeros to memory starting at `a`; it is equivalent to `memset(a, '\0', n)` and returns nothing. It is `4.3BSD`, marked `LEGACY` in POSIX.1-2001 and removed in POSIX.1-2008.

## Copy: overlap decides

- `memcpy(void *dest, const void *src, size_t n)` copies `n` bytes and returns `dest`. The areas must not overlap; overlapping use is a significant-bug source (the glibc `2.13` x86-64 optimization exposed such breakages, with a versioned safe symbol added in glibc `2.14`).
- `memmove(void *dest, const void *src, size_t n)` is similar to `memcpy` but the areas may overlap.
- `strlcpy(char dst[restrict dsize], const char *restrict src, size_t dsize)` copies `src` into `dst`, truncating when the string does not fit; `strlcat` concatenates past the existing terminator the same way. Both return the total length of the string they tried to create, as if truncation did not happen. History is OpenBSD `2.4`, POSIX.1-2024, glibc `2.38`; the pages warn both read the entire source string, exposing denial of service risk.
- `strdup(const char *s)` returns a new duplicate obtained with `malloc(3)`, freeable with `free(3)`; on failure it returns `NULL` with `errno` set.

## Search and compare

- `memchr(const void *s, int c, size_t n)` scans the initial `n` bytes for the first instance of `c`, with both sides interpreted as `unsigned char`; returns a pointer to the match or `NULL`.
- `strchr(const char *s, int c)` returns the first occurrence in the string, equivalent to `memchr(s, c, strlen(s) + 1)`; the terminator counts as part of the string, so `'\0'` yields a pointer to the terminator. Returns `NULL` when absent.
- `strrchr(const char *s, int c)` mirrors `strchr` for the last occurrence, equivalent to `memrchr(s, c, strlen(s) + 1)`.
- `strnstr(const char *s1, const char *s2, size_t len)` finds the first occurrence of substring `s2` in `s1` while searching at most `len` characters; it is a GNU extension outside standard libc, available in the Linux kernel API.
- `memcmp(const void *s1, const void *s2, size_t n)` compares the first `n` bytes as `unsigned char`; returns less than, equal to, or greater than zero for less, match, or greater, with the sign set by the first differing pair. `n` of zero returns zero. Do not use it for secrets: timing depends on content, inviting side-channel attacks.
- `strncmp(const char s1[], const char s2[], size_t n)` compares only the first (at most) `n` bytes, with the same sign convention as `memcmp`.

## See Also

- [Libft](../42/libft.md)
- [Character classification](ctype-classification.md)
- [Stdlib conversions and allocation](libc-stdlib.md)
- [read syscall](read-syscall.md)
