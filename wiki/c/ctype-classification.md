# Character classification in C

> Sources: POSIX Programmer's Manual, 2017; POSIX Programmer's Manual, Unknown
> Raw: [isalnum](../../raw/libft/character-classification/2017-isalnum.md); [isalpha](../../raw/libft/character-classification/2017-isalpha.md); [isascii](../../raw/libft/character-classification/2017-isascii.md); [isdigit](../../raw/libft/character-classification/isdigit-3p.md); [isprint](../../raw/libft/character-classification/2017-isprint.md); [isspace](../../raw/libft/character-classification/isspace-3p.md); [tolower](../../raw/libft/character-classification/2017-tolower.md); [toupper](../../raw/libft/character-classification/2017-toupper.md)
> Updated: 2026-10-15

## Overview

The `<ctype.h>` classification functions test a character class (`isalpha`, `isdigit`, `isalnum`, `isascii`, `isprint`, `isspace`) or transliterate case (`tolower`, `toupper`). They take an `int`, operate per the current locale (except `isascii`), define no errors, and report matches with non-zero rather than a fixed `1` — the fixed `1`/`0` contract is a libft override, not libc.

## Argument domain

- All eight take `int c` from `<ctype.h>`.
- The application must ensure `c` is representable as an `unsigned char` or equal to `EOF`; any other value is undefined behavior. `isdigit` and `isspace` phrase it identically as a character representable as an `unsigned char` or `EOF`.
- The `_l` variants take a `locale_t`; passing `LC_GLOBAL_LOCALE` or an invalid handle is undefined behavior.
- `isascii` is the exception: it is defined on all integer values.

## Return contracts

- `isalpha`, `isalnum`, `isdigit`, `isprint`, `isspace`: return non-zero on match, `0` otherwise. No errors are defined.
- `isascii`: returns non-zero if `c` is a 7-bit US-ASCII code between `0` and octal `0177` inclusive, `0` otherwise. No errors are defined.
- `tolower`: returns the corresponding lowercase letter when the argument is uppercase and a lowercase mapping exists in the locale (`LC_CTYPE`); otherwise returns the argument unchanged.
- `toupper`: mirrors `tolower` in the opposite direction.
- Both case functions have the same domain rule as above: values outside `unsigned char` plus `EOF` are undefined behavior.

## Portability notes

- For portable classification across natural languages, use only these functions and the reference pages in their `SEE ALSO` sections.
- `isascii` cannot be used portably in a localized application and may be removed in a future version.
- Libft reimplementations (`ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`) narrow the libc non-zero contract to exactly `1` on match and `0` otherwise.

## See Also

- [Libft](../42/libft.md)
- [String and memory functions](libc-string-memory.md)
- [Stdlib conversions and allocation](libc-stdlib.md)
