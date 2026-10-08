# open(2) — Linux manual page

> Source: https://man7.org/linux/man-pages/man2/open.2.html
> Collected: 2026-10-07
> Published: Unknown

NAME: open, openat, creat - open and possibly create a file.

SYNOPSIS:

    #include <fcntl.h>
    int open(const char *path, int flags, ... /* mode_t mode */);
    int creat(const char *path, mode_t mode);

DESCRIPTION: The open() system call opens the file specified by path. If the specified file does not exist, it may optionally (if O_CREAT is specified in flags) be created by open(). The return value of open() is a file descriptor, a small, nonnegative integer that is an index to an entry in the process's table of open file descriptors. The file descriptor is used in subsequent system calls (read(2), write(2), lseek(2), fcntl(2), etc.) to refer to the open file. The file descriptor returned by a successful call will be the lowest-numbered file descriptor not currently open for the process. The file offset is set to the beginning of the file. A call to open() creates a new open file description, which records the file offset and the file status flags.

The argument flags must include one of the following access modes: O_RDONLY, O_WRONLY, or O_RDWR. These request opening the file read-only, write-only, or read/write, respectively. In addition, zero or more file creation flags and file status flags can be bitwise ORed in flags (e.g. O_CREAT to create a missing file, O_TRUNC to truncate to length 0, O_APPEND for append mode). The mode argument specifies the file mode bits when a new file is created and must be supplied if O_CREAT is specified; the effective mode is modified by the process's umask.

creat(): A call to creat() is equivalent to calling open() with flags equal to O_CREAT|O_WRONLY|O_TRUNC.

openat(): operates like open(), except a relative path is interpreted relative to the directory referred to by the dirfd argument (or the current working directory when dirfd is AT_FDCWD); an absolute path ignores dirfd.

RETURN VALUE: On success, open(), openat(), and creat() return the new file descriptor (a nonnegative integer). On error, -1 is returned and errno is set to indicate the error.

ERRORS (selection): EACCES — requested access not allowed, or search permission denied on a path component. EEXIST — path already exists and O_CREAT and O_EXCL were used. ENOENT — O_CREAT is not set and the named file does not exist. EISDIR — path refers to a directory and writing was requested. ENAMETOOLONG — path was too long. ELOOP — too many symbolic links encountered in resolving path.

STANDARDS: open(), creat(), openat() — POSIX.1-2024.
