# open syscall

> Sources: man7.org open(2), Unknown
> Raw: [open(2) — Linux manual page](../../raw/c/open-2-man-page.md)
> Updated: 2026-10-07

## Overview

`open` turns a pathname into a file descriptor: a small nonnegative integer indexing the process's open-file table, used by all later I/O on that file. A successful call always returns the lowest-numbered descriptor not currently in use, and starts the file offset at the beginning. `openat` is the same operation with directory-relative path resolution.

## Flags and modes

`flags` must contain exactly one access mode: `O_RDONLY`, `O_WRONLY`, or `O_RDWR`. Creation and status flags are OR-ed on top: `O_CREAT` creates a missing file (requiring a `mode` argument, masked by the umask), `O_EXCL` with `O_CREAT` fails if the path exists, `O_TRUNC` empties a writable regular file, and `O_APPEND` forces writes to the end. The `creat` shorthand is exactly `open` with `O_CREAT|O_WRONLY|O_TRUNC`.

## Examples

```c
#include <fcntl.h>

int fd;

/* read-only: fails with ENOENT if the file does not exist */
fd = open("notes.txt", O_RDONLY);

/* read/write, created with rw-r--r-- when missing */
fd = open("notes.txt", O_RDWR | O_CREAT, 0644);

/* write-only, created when missing, emptied when present */
fd = open("notes.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

/* create-only: fails with EEXIST if already there */
fd = open("notes.txt", O_WRONLY | O_CREAT | O_EXCL, 0644);

/* append: every write lands at the end of the file */
fd = open("log.txt", O_WRONLY | O_APPEND);

/* directory-relative: resolved against dirfd, not cwd */
fd = openat(dirfd, "notes.txt", O_RDONLY);

if (fd == -1)
{
    /* inspect errno: ENOENT, EACCES, EISDIR, ... */
}
```

## Failures

On error the return is `-1` with `errno` set: `ENOENT` when creation was not asked and nothing exists there, `EACCES` for permission or path-search denial, `EEXIST` for a guarded create collision, `EISDIR` when writing to a directory, plus overlong or over-symlinked paths. For a line reader these matter at startup: a bad `open` means there is no fd to read from at all.

## See Also

- [read syscall](read-syscall.md)
- [get_next_line](../42/get-next-line.md)
