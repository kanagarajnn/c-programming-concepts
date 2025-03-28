#include <stdio.h>

int main() {
    int var = (printf("%s\n", "HELLO!"), 5);

    printf("%d", var);
    
    // Comma operator is the least precedence among all operators in C.
    int a;
    a = 3, 4, 8;  // => (a = 3), 4, 8 => a is 3
    printf("%d\n", a);

    a = (3, 4, 8);  // => a = (3, 4, 8) => a is 8
    printf("%d\n", a);

    // int b = 3, 4, 8; // Comma operator acts like a separator within function calls and definitions, variable declarations and enum declarations.
    // Error

    int var1;
    int num1;

    num1 = (var1 = 15, var1 + 35);
    printf("%d\n", num1);

    return 0;
}