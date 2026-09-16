/* ===========================================================================
 * sign_conversion.c  --  CWE-195: Signed to Unsigned Conversion Error
 * ---------------------------------------------------------------------------
 * WHAT HAPPENS
 *   signed_value is -10. Assigning it to an unsigned int reinterprets the
 *   two's-complement bit pattern 0xFFFFFFF6 as a plain magnitude:
 *
 *       -10   ->   2^32 - 10   =   4294967286
 *
 *   A small negative number becomes one of the largest positive numbers the
 *   type can hold. The conversion is implicit; no cast appears in the source.
 *
 * OBSERVED OUTPUT  (gcc 16.1.0, x86-64)
 *   Signed value: -10
 *   After sign conversion: 4294967286
 *
 * COMPILER DETECTION  (gcc 16.1.0, checked against this file)
 *   -Wall -Wextra ......... no warning
 *   -Wsign-conversion ..... WARNS at line 5:
 *                           "conversion to 'unsigned int' from 'int'
 *                            may change the sign of the result"
 *
 *   -Wsign-conversion is not implied by -Wall or -Wextra.
 *
 * WHY AN ATTACKER CARES -- the classic negative-length bug
 *   A length is validated while it is still signed, then used as a size_t:
 *
 *       #define MAX_COPY 16
 *       int len = attacker_controlled();     [ suppose len is -1        ]
 *       if (len > MAX_COPY) return -1;       [ -1 > 16 is FALSE,        ]
 *                                            [ so the check PASSES      ]
 *       memcpy(buffer, src, len);            [ len converts to size_t:  ]
 *                                            [ 18446744073709551615     ]
 *
 *   Both sides of that comparison are int, so it is a signed comparison and
 *   the negative value sails through the upper-bound test. memcpy's third
 *   parameter is size_t, so the negative length then becomes enormous. The
 *   missing test is the LOWER bound.
 *
 * MITIGATION -- reject negatives before converting, and bound both ends
 *
 *       if (signed_value < 0) {
 *           fprintf(stderr, "ERROR: negative value cannot be unsigned\n");
 *       } else {
 *           unsigned int unsigned_value = (unsigned int) signed_value;
 *       }
 *
 *   For any length or index, always check BOTH ends before use:
 *
 *       if (len < 0 || len > (int) capacity) { ...refuse... }
 *
 *   Better still, carry sizes in size_t from the start so a negative value
 *   can never be represented in the first place.
 * ========================================================================= */

#include <stdio.h>

int main() {
    int signed_value = -10;
    unsigned int unsigned_value = signed_value;  /* <== VULNERABLE: -10 -> 4294967286 */

    printf("Signed value: %d\n", signed_value);
    printf("After sign conversion: %u\n", unsigned_value);

    return 0;
}
