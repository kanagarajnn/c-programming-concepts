/*

sum = A ^ B
carry = A & B

*/

#include <stdio.h>

int main() {
    int x = 7, y = 2;
    int a = x, b = y;
    int sum, carry;

    while (b != 0) {
        sum = a ^ b;
        carry = (a & b) << 1;
        a = sum;
        b = carry;
    }

    printf("%d + %d = %d", x, y, sum);
    return 0;
}