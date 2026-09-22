#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    char name[20];
    int age;
    int choice = 1;

    printf("Enter your name: ");
    gets(name);

    printf("Enter your age: ");
    scanf("%d", &age);

    if (age > 0) {
        if (age < 100) {
            if (choice == 1) {
                printf("Name: %s\n", name);
                printf("Age: %d\n", age);

                if (age > 18) {
                    printf("Adult\n");
                } else {
                    printf("Minor\n");
                }
            }
        }
    }

    if (age == 999) {
        printf("This is dead code\n");
    }

    char buffer[10];
    strcpy(buffer, name);

    int unused = 50;

    return 0;
}