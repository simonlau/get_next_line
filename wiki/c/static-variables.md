# Static variables in C

> Sources: GeeksforGeeks, 2025-07-23
> Raw: [Static Variables in C](../../raw/c/2025-07-23-static-variables-in-c.md)
> Updated: 2026-10-07

## Overview

A static variable is declared with the `static` keyword and keeps its value between function calls: it is initialized only once, is not destroyed when the function returns, and lives till the end of the program. This makes it the standard tool for hidden persistent state — exactly what `get_next_line` needs to remember unread data across calls.

## Local statics

Declared as `static dataType variableName;` inside a function. Compared with ordinary locals, which live only during function execution, are reinitialized on every call, and sit in the stack, a static local exists throughout program execution, is initialized only once, and is stored in the data segment. Two consequences worth knowing: an uninitialized static starts as 0, and a static may only be initialized with constant literals.

Because statics outlive the call, a function can safely return a pointer to a static local, and a recursive function can use one (e.g. a depth counter that stops recursion past a limit) to guard against runaway recursion and stack overflow.

## Global statics

Declared outside any function, a static has internal linkage: its scope is limited to the file it is defined in, so it cannot be accessed from another translation unit. Otherwise it behaves like any global.

## See Also

- [get_next_line](../42/get-next-line.md)
- [Defining C macros at compile time with -D](compile-time-define-flag.md)
