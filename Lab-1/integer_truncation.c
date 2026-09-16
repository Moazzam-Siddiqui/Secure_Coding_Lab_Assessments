/* ===========================================================================
 * integer_truncation.c  --  CWE-197: Numeric Truncation Error
 * ---------------------------------------------------------------------------
 * WHAT HAPPENS
 *   large_value is 300. An unsigned char holds 8 bits, range 0..255, so the
 *   assignment keeps only the low 8 bits and discards the rest:
 *
 *       300 = 0x12C   ->   keep 0x2C   ->   44
 *
 *   Note there is no cast in the source: the conversion is implicit, which is
 *   how truncation usually reaches production code.
 *
 * OBSERVED OUTPUT  (gcc 16.1.0, x86-64)
 *   Original value: 300
 *   After conversion: 44
 *
 * COMPILER DETECTION  (gcc 16.1.0, checked against this file)
 *   -Wall -Wextra ..... no warning
 *   -Wconversion ...... WARNS at line 5:
 *                       "conversion from 'int' to 'unsigned char'
 *                        may change value"
 *
 *   -Wconversion is NOT implied by -Wall or -Wextra; it has to be asked for.
 *   Also note that writing an explicit cast, (unsigned char) large_value,
 *   SILENCES the warning without fixing anything. A cast asserts that the
 *   programmer intends the conversion -- it does not validate the value.
 *
 * WHY AN ATTACKER CARES
 *   Truncation usually strikes a length or count on its way into a narrower
 *   field. A 300-byte payload whose length is stored in an unsigned char is
 *   recorded as 44. A later bounds check against 44 passes, while 300 bytes
 *   are actually present or copied -- a 256-byte overflow. The same defect
 *   shows up in protocol length fields and in record counts narrowed into
 *   8- or 16-bit slots.
 *
 * MITIGATION -- range-check against the destination type before assigning
 *
 *       #include <limits.h>
 *
 *       if (large_value < 0 || large_value > UCHAR_MAX) {
 *           fprintf(stderr, "ERROR: %d does not fit in unsigned char\n",
 *                   large_value);
 *       } else {
 *           unsigned char small_value = (unsigned char) large_value;
 *       }
 *
 *   General rule: a narrowing conversion is safe only if converting the
 *   result BACK to the original type reproduces the original value.
 * ========================================================================= */

#include <stdio.h>

int main() {
    int large_value = 300;
    unsigned char small_value = large_value;  /* <== VULNERABLE: 300 -> 44, high bits dropped */

    printf("Original value: %d\n", large_value);
    printf("After conversion: %u\n", small_value);

    return 0;
}
