# Libft — your very first own library

> Sources: 42 School, Unknown
> Raw: [Libft subject](../../raw/libft/project-overview/libft-subject.md)
> Updated: 2026-10-15

## Overview

Libft is the 42 introductory library project: reimplement a set of libc functions plus a set of additional string, conversion, output, and linked-list utilities, shipped as `libft.a` from files at the repository root. The subject pins the file layout, compiler and archive rules, and per-function prototypes, allowed externals, and return contracts.

## Deliverables and toolchain

- Files to submit at the repo root: `Makefile`, `libft.h`, `ft_*.c`.
- `Makefile` must provide `NAME`, `all`, `clean`, `fclean`, `re` (plus `bonus` for the list part), compile every `.c` with `-Wall -Wextra -Werror` under `cc`, create the archive with `ar` (`libtool` forbidden), and avoid unnecessary relinking. `libft.a` is created at the repository root.
- Norm applies to mandatory and bonus alike; global variables are forbidden; helper functions that split up a complex function must be `static` to restrict scope to their file; unused files may not be submitted.

## Part 1 — Libc reimplementations

Same prototypes and man-page behavior as the originals, renamed with an `ft_` prefix. Prototypes using the C99 `restrict` qualifier must drop it, and code may not be compiled with `-std=c99`. Part 1 functions must not rely on any external functions, except `malloc` for `calloc` and `strdup`.

- Character tests: `isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`. Libft return contract overrides libc: `1` on match, `0` otherwise.
- Memory and strings: `strlen`, `memset`, `bzero`, `memcpy`, `memmove`, `strlcpy`, `strlcat`, `toupper`, `tolower`, `strchr`, `strrchr`, `strncmp`, `memchr`, `memcmp`, `strnstr`, `atoi`.
- Allocation: `calloc`, `strdup`. For `calloc`, if `nmemb` or `size` is `0`, return a unique pointer value that can later be successfully passed to `free()`.
- Portability note from the subject: `strlcpy`, `strlcat`, and `bzero` are absent from glibc by default; test against the system version with `<bsd/string.h>` and `-lbsd`.

## Part 2 — Additional functions

Each allocates its result with `malloc(3)` unless noted, returning `NULL` on allocation failure:

- `ft_substr(char const *s, unsigned int start, size_t len)` — substring from `start`, at most `len` bytes.
- `ft_strjoin(char const *s1, char const *s2)` — concatenation of prefix `s1` and suffix `s2`.
- `ft_strtrim(char const *s1, char const *set)` — copy of `s1` with `set` characters stripped from both ends.
- `ft_split(char const *s, char c)` — `NULL`-terminated array of independently allocated strings split on `c`; uses `malloc` and `free`; on any allocation failure returns `NULL` after the caller frees each string then the array.
- `ft_itoa(int n)` — decimal string for `n`, negatives handled.
- `ft_strmapi(char const *s, char (*f)(unsigned int, char))` — new string from successive applications of `f` to index plus character.
- `ft_striteri(char *s, void (*f)(unsigned int, char*))` — in-place application of `f` by address; no external function.
- Output via `write`: `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd` (with newline), `ft_putnbr_fd`.

## Part 3 — Linked list (bonus)

Declared in `libft.h`:

```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;
```

- `ft_lstnew(void *content)` (`malloc`) — `content` initialized from the parameter, `next` set to `NULL`.
- `ft_lstadd_front(t_list **lst, t_list *new)` / `ft_lstadd_back(t_list **lst, t_list *new)` — no external function.
- `ft_lstsize(t_list *lst)` — node count; `ft_lstlast(t_list *lst)` — last node.
- `ft_lstdelone(t_list *lst, void (*del)(void *))` (`free`) — frees content via `del` then the node, not the successor.
- `ft_lstclear(t_list **lst, void (*del)(void *))` (`free`) — deletes the node and all successors, then sets the list pointer to `NULL`.
- `ft_lstiter(t_list *lst, void (*f)(void *))` — applies `f` to each content.
- `ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))` (`malloc`, `free`) — new list from successive applications of `f`, using `del` to clean up on failure.

## See Also

- [get_next_line](get-next-line.md)
- [Character classification](../c/ctype-classification.md)
- [String and memory functions](../c/libc-string-memory.md)
- [Stdlib conversions and allocation](../c/libc-stdlib.md)
