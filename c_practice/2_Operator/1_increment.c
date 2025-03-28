#include <stdio.h>

int main() {
    int a = 4, b = 3;
    // printf("%d", a+++b); // Prints 7

    // printf("%d", a + ++b); // Prints 8

    printf("%d", a+++++b); // Error 
    // a ++ ++ + b // Error
    return 0;
}