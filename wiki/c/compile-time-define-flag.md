# Defining C macros at compile time with -D

> Sources: Stack Overflow, 2012-10-29
> Raw: [Including a #define in all .c source files at compile time](../../raw/c/2012-10-29-including-define-in-all-c-source-files-at-compile-time.md)
> Updated: 2026-10-07

## Overview

gcc's `-D` option predefines a macro for every translation unit at compile time, with no source edits needed. It is the standard way to inject a `#define` (or a header-wide setting like a buffer size) across many files from the build command.

## Forms

- `-D name` predefines the name as a macro with definition 1.
- `-D name=definition` predefines it with the given replacement, so `-Dmalloc=MYmalloc` acts as if `#define malloc MYmalloc` sat at the top of each source file.

## Notes

- Handy when the sources should not be touched, e.g. third-party code compiled as-is.
- For redirecting allocator calls specifically, alternatives exist: pre-loading a custom implementation at runtime, or glibc malloc hooks when the goal is debugging allocator behavior.

## See Also

- [get_next_line](../42/get-next-line.md)
