#include <stdio.h>
#include <string.h>

#define NAME_SIZE 20
#define BUFFER_SIZE 20
#define MIN_AGE 1
#define MAX_AGE 99
#define ADULT_AGE 18

int main(void) {
    char name[NAME_SIZE];
    char buffer[BUFFER_SIZE];
    int age;

    printf("Enter your name: ");

    if (fgets(name, sizeof(name), stdin) == NULL) {
        fprintf(stderr, "Error reading name.\n");
        return 1;
    }

    name[strcspn(name, "\n")] = '\0';

    printf("Enter your age: ");

    if (scanf("%d", &age) != 1) {
        fprintf(stderr, "Invalid age input.\n");
        return 1;
    }

    if (age < MIN_AGE || age > MAX_AGE) {
        fprintf(stderr, "Age must be between %d and %d.\n",
                MIN_AGE, MAX_AGE);
        return 1;
    }

    if (snprintf(buffer, sizeof(buffer), "%s", name)
        < 0) {
        fprintf(stderr, "Error copying name.\n");
        return 1;
    }

    printf("Name: %s\n", buffer);
    printf("Age: %d\n", age);

    if (age >= ADULT_AGE) {
        printf("Adult\n");
    } else {
        printf("Minor\n");
    }

    return 0;
}