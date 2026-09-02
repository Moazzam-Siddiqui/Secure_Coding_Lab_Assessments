#include <stdio.h>

int main() {
    int large_value = 300;
    unsigned char small_value = large_value;

    printf("Original value: %d\n", large_value);
    printf("After conversion: %u\n", small_value);

    return 0;
}