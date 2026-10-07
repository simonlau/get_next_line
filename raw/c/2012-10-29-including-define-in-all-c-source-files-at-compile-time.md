# Including a #define in all .c source files at compile time

> Source: https://stackoverflow.com/questions/13127810/including-a-define-in-all-c-source-files-at-compile-time
> Collected: 2026-10-07
> Published: 2012-10-29

Question by Will Brode (score 12, tags: c, gcc):

I need to include a `#define` at the top of around 300 .c files. I would prefer not to change the code as it is open source code but if I have to I will just write a script to modify all the files. Is there a way using gcc to add a `#define` or header file include to the top of every source file during compilation? The `#define` is this:

    #define malloc MYmalloc

Accepted answer by ouah (score 28):

You can pass `-Dmalloc=MYmalloc` to the `gcc` options.

For more information about the `-D` option: http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html

Note that if you want to modify the behavior of `malloc` function for debugging purposes, you may also be interested in `glibc` `malloc` hooks: https://web.archive.org/web/20121024093236/http://www.gnu.org/software/libc/manual/html_node/Hooks-for-Malloc.html

Answer by joe (score 8):

gcc option `-D`:

    -D name
        Predefine name as a macro, with definition 1.

    -D name=definition
        ....

so, in your case, `gcc ... -Dmalloc=MYmalloc`

Answer by grundprinzip (score 1):

If you strive for redirecting `malloc()` calls to a custom function I would rather recommend to provide your custom code via pre-loading of your implementation at runtime. See this question for details: https://stackoverflow.com/questions/262439/create-a-wrapper-function-for-malloc-and-free-in-c
