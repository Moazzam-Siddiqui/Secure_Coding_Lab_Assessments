#include <stdio.h>
#include <stdlib.h>

int main() {

    int size = 5;

    // Allocate memory
    int *p = malloc(size * sizeof(int));

    // Check malloc
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize array
    for (int i = 0; i < size; i++) {
        p[i] = i + 1;
    }

    printf("Pointer after malloc: %p\n", p);
    printf("Size: %d bytes\n", size * sizeof(int));

    // Increase size
    size = 10;

    int *q = realloc(p, size * sizeof(int));

    // Check realloc
    if (q == NULL) {
        printf("Memory reallocation failed\n");
        free(p);
        p = NULL;
        return 1;
    }

    p = q;

    // Initialize new elements
    for (int i = 5; i < size; i++) {
        p[i] = 0;
    }

    printf("Pointer after realloc: %p\n", p);
    printf("Size: %d bytes\n", size * sizeof(int));

    // Free memory
    free(p);

    // Remove dangling pointer
    p = NULL;

    printf("Pointer after free: %p\n", p);

    return 0;
}