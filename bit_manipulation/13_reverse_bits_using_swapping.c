#include <stdio.h>

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}


// Key logic
// A B C D E F G H  (Swap adjacent)
// B A D C F E H G

// BA DC FE HG  (Swap Pairs)
// DC BA HG FE

// DCBA HGFE  (Swap nibbles)
// HGFE DCBA  

// HGFEDCBA (final result after adjacent bits swap)


unsigned int reverse_bits_optimized(unsigned int n) {
    n = ((n >> 1) & 0x55555555) | ((n & 0x55555555) << 1);  // Swap adjacent bits 
    n = ((n >> 2) & 0x33333333) | ((n & 0x33333333) << 2);  // Swap pairs
    n = ((n >> 4) & 0x0F0F0F0F) | ((n & 0x0F0F0F0F) << 4);  // Swap nibbles
    n = ((n >> 8) & 0x00FF00FF) | ((n & 0x00FF00FF) << 8);  // Swap bytes
    n = ((n >> 16) & 0x0000FFFF) | ((n & 0x0000FFFF) << 16); // Swap halves
    return n;
}

int main() {
    unsigned int n = 0b0000010100101000001111010011100; // Example binary input
    printf("Original: \n");
    print_binary(n);

    n = reverse_bits_optimized(n);
    
    printf("Reversed: \n");
    print_binary(n);

    return 0;
}
