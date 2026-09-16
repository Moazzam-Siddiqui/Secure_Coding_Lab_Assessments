#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *numbers = malloc(5 * sizeof(*numbers));

    if (numbers == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return 1;
    }

    numbers[0] = 42;
    printf("First number: %d\n", numbers[0]);

    free(numbers);
    numbers = NULL;
    return 0;
}
