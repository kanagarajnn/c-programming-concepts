#include <stdio.h>

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}


unsigned int reverse_bits_naive(unsigned int n) {
    unsigned int result = 0;
    
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1); // Append LSB to result
        n >>= 1;  // Shift input right
    }
    
    return result;
}

int main() {
    unsigned int n = 0b0000010100101000001111010011100; // Example binary input
    printf("Original: \n");
    print_binary(n);

    n = reverse_bits_naive(n);
    
    printf("Reversed: \n");
    print_binary(n);

    return 0;
}
