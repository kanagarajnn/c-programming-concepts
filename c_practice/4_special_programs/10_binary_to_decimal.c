/*

Binary to Decimal
1 0 0 1


*/

#include <stdio.h>

int main() {
    int input_binary = 1010;
    int binary = input_binary;
    int decimal = 0;
    int weight = 1;
    int rem = 0;

    while (binary != 0) {
        rem = binary % 10;
        decimal += rem * weight;
        binary /= 10;
        weight *= 2; // weight <<= 1; (efficient)
    }

    printf("Binary: %d => Decimal: %d", input_binary, decimal);
    
    return 0;
}