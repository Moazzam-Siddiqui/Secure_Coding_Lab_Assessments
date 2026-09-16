#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *number = malloc(sizeof(*number));

    if (number == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return 1;
    }

    *number = 42;
    printf("Number before free: %d\n", *number);

    free(number);
    number = NULL;
    printf("Pointer cleared after free: %s\n", number == NULL ? "yes" : "no");
    return 0;
}
