# Static Variables in C

> Source: https://www.geeksforgeeks.org/c/static-variables-in-c/
> Collected: 2026-10-07
> Published: 2025-07-23

In C programming, a static variable is declared using static keyword and have the property of retaining their value between multiple function calls. It is initialized only once and is not destroyed when the function returns a value. It extends the lifetime of the variable till the end of the program.

Example: a function `fun()` with `static int count = 0;` that increments and returns count prints `1 2` across two calls. Explanation: count is only initialized once. In the first call it becomes 1; a normal local would be created and initialized again on the second call, but count is 2 because it was not destroyed with the function. That is why it was able to retain its value between multiple function calls.

Syntax: a static variable is declared by prefixing the static keyword before the normal variable declaration:

    static dataType variableName;

Return address of a local variable: as static variables live till the end of the program, they can be used to return data by reference from a function. Example: `fun()` creates `static int local_var = 123;` and returns `&local_var`; `main()` prints 123. Unlike normal local variables, which are destroyed when the function exits, the static local retains its value.

Control recursion depth: as these variables are only initialized once and retain their value, they can be used to control recursion in case of infinite recursive calls and avoid stack overflow. Example: a recursive `fun(n)` that prints from n downward uses `static int depth = 0;` and returns when `n == 0 || depth > 10`; calling `fun(-1)` prints `-1 -2 -3 -4 -5 -6 -7 -8 -9 -10 -11` then terminates. The static variable depth retains its value across recursive calls, allowing the function to track the recursion depth.

Global static variables: static variables are generally declared inside functions, but they can also be declared outside functions (at the global scope). Global static variables have their scope limited to the file they are defined in (internal linkage). It means that they cannot be accessed outside the current translation unit (C source file). Other than that, there is no effect of static on global variables in C. Example: `static int globalVar = 5;` with a `display()` function printing it; after `globalVar = 10;`, output is 5 then 10.

Interesting facts:

- Static variables (like global variables) are initialized as 0 if not initialized explicitly.
- In C, static variables can only be initialized using constant literals.

Local vs static local variables:

- Scope: both are local to the function or block.
- Lifetime: a local exists only during function execution; a static exists throughout the program execution.
- Initialization: a local is reinitialized each time the function is called; a static is initialized only once.
- Storage: a local is stored in the stack; a static is stored in the data segment.
