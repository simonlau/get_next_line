# read syscall

> Sources: man7.org read(2), Unknown
> Raw: [read(2) — Linux manual page](../../raw/c/read-2-man-page.md)
> Updated: 2026-10-07

## Overview

`read` pulls up to a requested number of bytes from a file descriptor into a caller-supplied buffer, advancing the file offset by the amount actually transferred. It is the only input primitive `get_next_line` may use, so its three-way return contract drives the whole loop design.

## Return contract

- Positive: that many bytes were stored; a short count (fewer than requested) is normal near end-of-file or on pipes and terminals, never an error by itself.
- Zero: end-of-file — nothing more will ever come from this offset.
- `-1`: error, with the reason in `errno` (`EBADF` for a bad or write-only fd, `EINTR` for signal interruption, `EFAULT` for a bad buffer, `EIO` and `EISDIR` among others). Whether the file offset moved is then unspecified.

## Notes for line readers

Because short reads are legal at any time, a single `read` never guarantees a full line — the caller must loop, accumulate, and scan for a newline itself. A zero `count` argument is a no-op returning zero. Count values above `SSIZE_MAX` are implementation-defined, which is one more reason to keep request sizes modest.

## See Also

- [open syscall](open-syscall.md)
- [get_next_line](../42/get-next-line.md)
