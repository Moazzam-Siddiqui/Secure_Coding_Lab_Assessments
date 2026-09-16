/* ===========================================================================
 * integer_overflow.c  --  CWE-190: Integer Overflow or Wraparound
 * ---------------------------------------------------------------------------
 * WHAT HAPPENS
 *   value holds UINT_MAX (4294967295), the largest 32-bit unsigned int.
 *   Adding 1 does not give 4294967296 -- that does not fit in 32 bits, so the
 *   result wraps around to 0.
 *
 * OBSERVED OUTPUT  (gcc 16.1.0, x86-64)
 *   Before overflow: 4294967295
 *   After overflow: 0
 *
 * IS THIS UNDEFINED BEHAVIOUR?  No -- and that is exactly the trap.
 *   C defines unsigned arithmetic as modulo 2^n, so this wrap is perfectly
 *   legal and completely silent. It is a well-defined WRONG ANSWER, not a
 *   crash. (Signed overflow would be undefined behaviour; unsigned is not.)
 *
 * COMPILER DETECTION  (gcc 16.1.0, checked against this file)
 *   -Wall -Wextra ..................... no warning
 *   -Wconversion -Wsign-conversion .... no warning
 *   Nothing is reported, because nothing here is illegal. Detecting it needs
 *   a run-time check, or a sanitiser such as clang's
 *   -fsanitize=unsigned-integer-overflow (not run here).
 *
 * WHY AN ATTACKER CARES
 *   The textbook case is an allocation size computed from attacker input:
 *
 *       buf = malloc(count * sizeof(elem));
 *
 *   If count * sizeof(elem) wraps, malloc returns a buffer far smaller than
 *   the caller believes it asked for, and every following write runs off the
 *   end of the heap chunk. The same pattern breaks length counters, loop
 *   bounds and reference counts (a wrapped refcount frees live memory).
 *
 * MITIGATION -- test BEFORE the operation, never inspect the result after.
 *   Checking "if (value + 1 < value)" is already too late: it examines a
 *   value that has been wrapped.
 *
 *       if (value > UINT_MAX - 1) {
 *           fprintf(stderr, "ERROR: increment would overflow, refused\n");
 *       } else {
 *           value = value + 1;
 *       }
 *
 *   Or use a checked builtin, which returns non-zero on overflow:
 *
 *       if (__builtin_add_overflow(value, 1u, &value)) { ...refuse... }
 * ========================================================================= */

#include <stdio.h>
#include <limits.h>

int main(){
    unsigned int value = UINT_MAX;
    printf("Before overflow: %u\n", value);
    value = value + 1;      /* <== VULNERABLE: wraps 4294967295 -> 0, silently */
    printf("After overflow: %u\n", value);
    return 0;
}
