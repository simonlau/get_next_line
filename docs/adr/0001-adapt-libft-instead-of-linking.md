# Adapt libft helpers instead of linking libft

The ticket asks to reuse libft with minimal changes, but the subject allows only `read`, `malloc`, and `free` and forbids linking `libft`. We copy-adapt `strlen`, `strchr`, `strdup`, `substr`, and `strjoin` into `get_next_line_utils.c` as `gnl_*` with `NULL`-safe, Norm-clean logic.

Considered Options: link `-lft` (rejected: fails `nm` / evaluation), rewrite from scratch (rejected: larger diff from proven libft code).
