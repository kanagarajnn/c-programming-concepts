#include<stdio.h>

int main() {
    // char *str1;
    // scanf("%s", str1);
    // str1 points to a random memory location
    // str1 is an uninitialized pointer, and using it with scanf causes undefined behavior. 
    // You're telling scanf to write user input to a memory location that hasn't been allocated.

    char str1[10];
    printf("Enter a string:\n");
    scanf("%9s", str1);

    printf("Entered string: %s\n", str1);
    return 0;
}