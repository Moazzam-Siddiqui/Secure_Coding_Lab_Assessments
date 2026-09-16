# Experiment 14: Memory Management Error Identification and Remediation

This folder preserves intentionally vulnerable faculty-style examples in `original/` and their corrected versions in `fixed/`. The original files are for analysis only; do not execute them outside a controlled sanitizer environment.

| Original snippet | Error type | Security impact | Correct pattern applied |
| --- | --- | --- | --- |
| `unchecked_allocation.c` | Unchecked `malloc` return value / null-pointer dereference | Denial of service; in some contexts, unchecked allocation failures can cause unsafe program behavior | Check the returned pointer before dereferencing it. |
| `use_after_free.c` | Use-after-free (dangling-pointer access) | Denial of service, information disclosure, or arbitrary code execution when heap memory is reused | Free the allocation, set the pointer to `NULL`, and never dereference it afterward. |
| `double_free.c` | Double free | Heap corruption, denial of service, information disclosure, or arbitrary code execution | Release the allocation exactly once and set the pointer to `NULL`. |

## ASan verification

From this directory, run:

```powershell
.\verify_asan.ps1
```

The script compiles every fixed snippet with `gcc -fsanitize=address -Wall -Wextra -Werror`, runs it, and succeeds only if every program exits cleanly. Build outputs are placed in `build/`, which is intentionally untracked.

Expected successful output:

```text
Running double_free_fixed.c...
Number: 42
Memory released exactly once.
Running unchecked_allocation_fixed.c...
First number: 42
Running use_after_free_fixed.c...
Number before free: 42
Pointer cleared after free: yes
All fixed snippets completed cleanly with AddressSanitizer.
```
