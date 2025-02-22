#include <stdio.h>

// Lookup table for 8-bit reversed values
unsigned char lookup_table[256];

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void initialize_lookup_table() {
    for (int i = 0; i < 256; i++) {  // Loop over all 8-bit values (0 to 255)
        unsigned char rev = 0;
        unsigned char x = i;
        for (int j = 0; j < 8; j++) {  // Reverse 8-bit number
            rev = (rev << 1) | (x & 1); // Append the LSB of x to rev
            x >>= 1; // Shift x to process the next bit
        }
        lookup_table[i] = rev; // Store reversed value in the lookup table
    }
}


unsigned int reverse_bits_lookup(unsigned int n) {
    return (lookup_table[n & 0xFF] << 24) |  // Reverse least significant byte
           (lookup_table[(n >> 8) & 0xFF] << 16) |  // Reverse 2nd byte
           (lookup_table[(n >> 16) & 0xFF] << 8) |  // Reverse 3rd byte
           (lookup_table[(n >> 24) & 0xFF]);  // Reverse most significant byte
}



int main() {
    initialize_lookup_table(); // Initialize lookup table once

    unsigned int n = 0b0000010100101000001111010011100; // Example binary input
    printf("Original: \n");
    print_binary(n);

    n = reverse_bits_lookup(n);
    
    printf("Reversed: \n");
    print_binary(n);

    return 0;
}