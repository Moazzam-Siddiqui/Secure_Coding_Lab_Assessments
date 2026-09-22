#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));

    *ptr = 10;

    free(ptr);
    ptr = NULL;

    return 0;
}