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
    printf("Number: %d\n", *number);

    free(number);
    number = NULL;
    printf("Memory released exactly once.\n");
    return 0;
}
