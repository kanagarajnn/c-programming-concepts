/*

a = a ^ b
b = a ^ b   // (orig a ^ orig b) ^ orig b = orig a
a = a ^ b   // (orig a ^ orig b) ^ orig a = orig b 

a = a ^ b
b = a ^ b   // a ^ b ^ b = a
a = a ^ b   // a ^ b ^ a = b

*/

#include <stdio.h>

void xor_swap(int *a, int *b) {
    if (a == b) return;  // Prevent self-swap issue
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int main() {
    int x = 5, y = 10;

    printf("Before swap: x = %d, y = %d\n", x, y);
    xor_swap(&x, &y);
    printf("After swap: x = %d, y = %d\n", x, y);

    return 0;
}
