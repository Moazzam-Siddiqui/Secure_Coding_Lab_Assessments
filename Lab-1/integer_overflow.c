#include <stdio.h>
#include <limits.h>

int main(){
    unsigned int value = UINT_MAX;
    printf("Before overflow: %u\n", value);
    value = value + 1;
    printf("After overflow: %u\n", value);
    return 0;
}