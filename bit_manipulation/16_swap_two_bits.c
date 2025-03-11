#include <stdio.h>

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}


unsigned int swap_bits(unsigned int n, int p1, int p2) {
    // Extract bits at positions p1 and p2
    int bit1 = (n >> p1) & 1;
    int bit2 = (n >> p2) & 1;

    // If bits are the same, no need to swap
    if (bit1 == bit2)
        return n;

    // Toggle bits at positions p1 and p2 using XOR
    n ^= (1 << p1);
    n ^= (1 << p2);

    return n;
}


int main() {
    unsigned int n = 28;  // Binary: 11100
    int p1 = 0, p2 = 3;    // Swap bit at position 0 with bit at position 3

    printf("Before Swap:\n");
    print_binary(n);

    n = swap_bits(n, p1, p2);
    
    printf("\nAfter Swap:\n");
    print_binary(n);

    return 0;
}
