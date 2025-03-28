#include <stdio.h>

int main() {
    int a = 4, b = 3;
    
    printf("Before XOR, a = %d and b = %d\n", a, b);
    
    a = a ^ b;  // 4 ^ 3
    b = a ^ b;  // 4 ^ 3 ^ 3
    a = a ^ b;  // 4 ^ 3 ^ 4

    printf("After XOR, a = %d and b = %d\n", a, b);

    return 0;
}