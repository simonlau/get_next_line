# TST - Simple C Testing Framework

> Source: https://github.com/rdentato/tst
> Collected: 2026-10-07
> Published: Unknown

A lightweight, single-header unit testing framework for C and C++ with zero dependencies. By Remo Dentato. Licensed under the MIT License. Single header file, less than 300 lines of code, no external dependencies. Requires C99 or later (C89 compatible with minor limitations), C++98 or later. Tested with GCC 7.0+, Clang 6.0+, MSVC 2017+, MinGW-w64 8.0+. Works on Linux, macOS, Windows WSL2, and Windows.

Installation (recommended): download `tst.h` and copy it into the project:

    curl -o tst.h https://raw.githubusercontent.com/rdentato/tst/main/src/tst.h

First test (`test_example.c`):

    #include "tst.h"

    tstsuite("My First Test Suite") {
        tstcase("Basic Arithmetic") {
            tstcheck(1 + 1 == 2, "Addition works");
            tstcheck(5 * 4 == 20, "Multiplication works");
        }

        tstcase("String Functions") {
            tstcheck(strlen("hello") == 5);
            tstcheck(strcmp("abc", "abc") == 0);
        }
    }

Compile with no special flags (`gcc -o test_example test_example.c`) and run `./test_example`. Output reports each case with PASS/FAIL/SKIP counts and a final RSLT line.

Core concepts: a test suite is the top-level container (one per source file); a test case groups related checks with partial results; a test section is an isolated subsection with setup/teardown. Assertions: `tstcheck` continues on failure, `tstassert` aborts on failure, `tstexpect` is silent on pass. `tstskipif` skips at runtime. Cases accept tags for selective execution from the command line (`+Tag` / `-Tag`). Arrays named `tstdata` drive parameterized tests via `tstsection`. `tstclock` measures CPU time with `tstelapsed()`.

Running: `./test_program` runs everything; `--list` lists tests and tags; `--report-error` returns an error code on failure for CI pipelines. The `TSTOPTIONS` environment variable sets default options. Shell-based tests are supported through a `tst.sh` bash library producing TST-formatted output, and the `t2h` utility converts logs into interactive HTML reports.

License text (abridged): Copyright (c) 2023-2025 Remo Dentato. Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software.
