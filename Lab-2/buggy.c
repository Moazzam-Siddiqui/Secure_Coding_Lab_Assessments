#include <stdio.h>
#include <stdlib.h>

int main() {

    int size = 5;

    // Allocate memory
    int *p = malloc(size * sizeof(int));

    printf("Pointer after malloc: %p\n", p);
    printf("Size: %d bytes\n", size * sizeof(int));

    // Initialize array
    for (int i = 0; i < size; i++) {
        p[i] = i + 1;
    }

    // Increase array size
    size = 10;
    p = realloc(p, size * sizeof(int));

    printf("Pointer after realloc: %p\n", p);
    printf("Size: %d bytes\n", size * sizeof(int));

    // Free memory
    free(p);

    printf("Pointer after free: %p\n", p);

    // ERROR: use-after-free
    p[0] = 100;

    return 0;
}