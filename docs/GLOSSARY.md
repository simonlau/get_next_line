# get_next_line

Reading a file descriptor one line at a time, keeping what is unread for the next call.

## Language

**Line**:
A single `\n`-terminated chunk, or the final fragment at end-of-file without `\n`.
_Avoid_: string, row, output

**Stash**:
Unreturned data kept between calls.
_Avoid_: leftover, remainder, left_over, buffer

**Refill**:
New data taken from the file descriptor and appended to the stash.
_Avoid_: read chunk, fill, slurp

**Drain**:
One line taken from the stash, leaving the rest for the next call.
_Avoid_: pop, split, consume
