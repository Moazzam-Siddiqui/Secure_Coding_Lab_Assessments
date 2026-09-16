#include <stdlib.h>

int main(void)
{
    int *number = malloc(sizeof(*number));

    if (number == NULL) {
        return 1;
    }

    *number = 42;
    free(number);
    free(number);
    return 0;
}
