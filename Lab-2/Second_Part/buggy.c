#include <stdlib.h>

/*
 * Experiment 2.2: Intentionally vulnerable examples.
 *
 * 1. Unchecked malloc return value / NULL-pointer dereference.
 *    Impact: denial of service; unsafe failure handling can cause undefined behavior.
 *
 * 2. Use-after-free (dangling-pointer access).
 *    Impact: denial of service, information disclosure, or arbitrary code execution.
 *
 * 3. Double free.
 *    Impact: heap corruption, denial of service, information disclosure,
 *    or arbitrary code execution.
 *
 * Do not execute this file except for controlled sanitizer demonstrations.
 */
int main(void)
{
    int *unchecked_number = malloc(sizeof(*unchecked_number));
    *unchecked_number = 10;
    free(unchecked_number);

    int *freed_number = malloc(sizeof(*freed_number));
    if (freed_number == NULL) {
        return 1;
    }
    *freed_number = 20;
    free(freed_number);
    *freed_number = 30;

    int *double_freed_number = malloc(sizeof(*double_freed_number));
    if (double_freed_number == NULL) {
        return 1;
    }
    *double_freed_number = 40;
    free(double_freed_number);
    free(double_freed_number);

    return 0;
}
