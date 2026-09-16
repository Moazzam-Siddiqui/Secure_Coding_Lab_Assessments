Name: Moazzam Ahmad Siddiqui

Roll NO: 2301730082

Course: BTech CSE (AI/ML) Section-B

---

# Lab 2 — Integer Conversion Vulnerabilities in C

## Aim

To demonstrate three classes of integer-handling defect in C — overflow,
truncation and sign conversion — printing each value before and after the
conversion; to determine which compiler warnings actually detect them; and to
state the range check that prevents each one.

## Programs

| File | Defect | CWE |
|---|---|---|
| `integer_overflow.c` | Unsigned wraparound past `UINT_MAX` | CWE-190 |
| `integer_truncation.c` | Value narrowed into `unsigned char` | CWE-197 |
| `sign_conversion.c` | Negative `int` reinterpreted as unsigned | CWE-195 |

## Build and run

```sh
gcc -std=c11 -Wall -Wextra -Wconversion -Wsign-conversion -o integer_overflow   integer_overflow.c
gcc -std=c11 -Wall -Wextra -Wconversion -Wsign-conversion -o integer_truncation integer_truncation.c
gcc -std=c11 -Wall -Wextra -Wconversion -Wsign-conversion -o sign_conversion    sign_conversion.c
```

## Observed results

| Program | Before | After | What happened |
|---|---|---|---|
| `integer_overflow` | 4294967295 | 0 | `+1` wrapped modulo 2³² |
| `integer_truncation` | 300 | 44 | low 8 bits kept: `300 & 0xFF = 44` |
| `sign_conversion` | −10 | 4294967286 | bit pattern read as `2³² − 10` |

## Which warnings actually catch these

Tested with gcc 16.1.0 (MinGW-W64 x86-64) against these exact files:

| Program | `-Wall -Wextra` | `-Wconversion -Wsign-conversion` |
|---|---|---|
| `integer_overflow` | no warning | no warning |
| `integer_truncation` | no warning | **warns**, line 5 |
| `sign_conversion` | no warning | **warns**, line 5 |

Three findings worth stating:

1. **`-Wall -Wextra` catches none of the three.** Neither `-Wconversion` nor
   `-Wsign-conversion` is implied by `-Wall` or `-Wextra`; both must be
   requested explicitly. A build that only uses `-Wall -Wextra` — which is
   most builds — sees nothing wrong with any of these files.

2. **Nothing catches the unsigned overflow, because it is not an error.**
   C defines unsigned arithmetic as modulo 2ⁿ, so the wrap is legal, silent,
   and gives a wrong answer. (Signed overflow *would* be undefined behaviour;
   unsigned overflow is fully defined.) Catching it requires a run-time check
   or a sanitiser such as clang's `-fsanitize=unsigned-integer-overflow`.

3. **An explicit cast does not fix any of these.** Writing
   `(unsigned char) large_value` silences the diagnostic while leaving the
   behaviour exactly as it was. A cast asserts that the programmer *intends*
   the conversion; it does not validate the value.

## Security impact and mitigation

| Defect | How it becomes a vulnerability | Fix |
|---|---|---|
| **Overflow** (CWE-190) | `malloc(count * sizeof(elem))` wraps, returning a buffer far smaller than requested; subsequent writes overflow the heap chunk. | Test *before* the operation: `if (value > UINT_MAX - 1) refuse;` or use `__builtin_add_overflow()`. Testing the result afterwards is too late. |
| **Truncation** (CWE-197) | A 300-byte length stored in an `unsigned char` is recorded as 44; a bounds check against 44 passes while 300 bytes are copied. | Range-check against the destination type: `if (v < 0 \|\| v > UCHAR_MAX) refuse;` |
| **Sign conversion** (CWE-195) | `int len = -1;` passes a signed `if (len > MAX)` check, then converts to `size_t` for `memcpy` and becomes 18446744073709551615. | Reject negatives first, and bound **both** ends: `if (len < 0 \|\| len > capacity) refuse;` Better still, carry sizes as `size_t` throughout. |

The general rule behind all three: **a conversion is safe only if converting
the result back to the original type reproduces the original value.** Validate
first, convert second.

## Result

All three programs compiled and ran, and each reproduced its defect: the
unsigned value wrapped from 4294967295 to 0, the value 300 truncated to 44,
and −10 became 4294967286. The compiler reported none of them under
`-Wall -Wextra`, and only the two conversion defects under `-Wconversion`
and `-Wsign-conversion`. The overflow was not diagnosed at compile time at
all. This confirms that the compiler cannot be relied on to find integer
conversion defects — the range checks have to be written explicitly.
