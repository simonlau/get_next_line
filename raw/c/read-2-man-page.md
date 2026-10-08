# read(2) — Linux manual page

> Source: https://man7.org/linux/man-pages/man2/read.2.html
> Collected: 2026-10-07
> Published: Unknown

NAME: read - read from a file descriptor.

SYNOPSIS:

    #include <unistd.h>
    ssize_t read(int fd, void buf[count], size_t count);

DESCRIPTION: read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf. On files that support seeking, the read operation commences at the file offset, and the file offset is incremented by the number of bytes read. If the file offset is at or past the end of file, no bytes are read, and read() returns zero. If count is zero, read() may detect errors; otherwise a read() with a count of 0 returns zero and has no other effects. If count is greater than SSIZE_MAX, the result is implementation-defined; on Linux, read() transfers at most 0x7ffff000 (2,147,479,552) bytes.

RETURN VALUE: On success, the number of bytes read is returned (zero indicates end of file), and the file position is advanced by this number. It is not an error if this number is smaller than the number of bytes requested; this may happen for example because fewer bytes are actually available right now (maybe because we were close to end-of-file, or because we are reading from a pipe, or from a terminal), or because read() was interrupted by a signal. On error, -1 is returned, and errno is set to indicate the error. In this case, it is left unspecified whether the file position (if any) changes.

ERRORS (selection): EBADF — fd is not a valid file descriptor or is not open for reading. EFAULT — buf is outside your accessible address space. EINTR — the call was interrupted by a signal before any data was read. EINVAL — fd is attached to an object which is unsuitable for reading. EIO — I/O error. EISDIR — fd refers to a directory.

STANDARDS: POSIX.1-2008. HISTORY: SVr4, 4.3BSD, POSIX.1-2001.
