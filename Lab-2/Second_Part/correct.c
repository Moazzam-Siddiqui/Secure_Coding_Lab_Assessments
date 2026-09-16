#include <stdio.h>
#include <stdlib.h>

/*
 * Experiment 2.2: Correct memory-management patterns.
 * - Check every allocation result before dereferencing it.
 * - Set a pointer to NULL immediately after free.
 * - Release each allocation exactly once.
 */
int main(void)
{
    int *checked_number = malloc(sizeof(*checked_number));
    if (checked_number == NULL) {
        fputs("Allocation for checked_number failed.\n", stderr);
        return 1;
    }
    *checked_number = 10;
    printf("Checked allocation: %d\n", *checked_number);
    free(checked_number);
    checked_number = NULL;

    int *safe_number = malloc(sizeof(*safe_number));
    if (safe_number == NULL) {
        fputs("Allocation for safe_number failed.\n", stderr);
        return 1;
    }
    *safe_number = 20;
    printf("Value before free: %d\n", *safe_number);
    free(safe_number);
    safe_number = NULL;
    printf("Pointer cleared after free: %s\n", safe_number == NULL ? "yes" : "no");

    int *single_free_number = malloc(sizeof(*single_free_number));
    if (single_free_number == NULL) {
        fputs("Allocation for single_free_number failed.\n", stderr);
        return 1;
    }
    *single_free_number = 40;
    printf("Released exactly once: %d\n", *single_free_number);
    free(single_free_number);
    single_free_number = NULL;

    return 0;
}
