# TST testing framework

> Sources: rdentato/tst on GitHub, Unknown
> Raw: [TST - Simple C Testing Framework](../../raw/c/tst-simple-c-testing-framework.md)
> Updated: 2026-10-07

## Overview

TST is a single-header unit testing framework for C (with C++ compatibility) and zero dependencies — one header under 300 lines, no build system required. Tests are organized as suites containing cases containing sections, and the runner prints per-case PASS/FAIL/SKIP tallies plus a final result line.

## Writing tests

Drop the header into the project, include it, and declare a suite (one per source file):

```c
    tstsuite("My First Test Suite") {
        tstcase("Basic Arithmetic") {
            tstcheck(1 + 1 == 2, "Addition works");
        }
    }
```

Compile like any source file with no special flags and run the binary. Assertion flavors: `tstcheck` continues after a failure, `tstassert` aborts the run, and `tstexpect` only prints on failure. `tstskipif` skips a block at runtime, which suits not-yet-implemented cases. Cases take `+Tag`/`-Tag` filters from the command line, arrays named `tstdata` feed parameterized runs through `tstsection`, and `tstclock` with `tstelapsed()` times code. `--list` shows available tests, `--report-error` yields a nonzero exit on failure for CI, and defaults can come from the `TSTOPTIONS` environment variable. Companion tools exist for shell-based tests and HTML reports.

## Notes

TST needs C99 or later and is confirmed on GCC, Clang, MSVC, and MinGW across Linux, macOS, and Windows. It is MIT licensed, so vendoring the header (keeping its license notice) is all the setup there is.

## See Also

- [get_next_line](../42/get-next-line.md)
