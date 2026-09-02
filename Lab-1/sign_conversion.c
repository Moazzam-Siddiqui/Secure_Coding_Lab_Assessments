#include <stdio.h>

int main() {
    int signed_value = -10;
    unsigned int unsigned_value = signed_value;

    printf("Signed value: %d\n", signed_value);
    printf("After sign conversion: %u\n", unsigned_value);

    return 0;
}
