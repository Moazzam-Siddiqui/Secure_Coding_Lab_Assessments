#include <stdlib.h>

int main(void)
{
    int *numbers = malloc(5 * sizeof(*numbers));

    numbers[0] = 42;
    free(numbers);
    return 0;
}
