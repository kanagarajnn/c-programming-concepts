#include <stdio.h>

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

// Approach 1: Using Mask based approach
unsigned int swap_odd_even_bits_xor(unsigned int n) {
    // Mask for even bits (0xAAAAAAAA = 10101010101010101010101010101010 in binary)
    unsigned int even_mask = 0xAAAAAAAA; 
    
    // Mask for odd bits (0x55555555 = 01010101010101010101010101010101 in binary)
    unsigned int odd_mask = 0x55555555;  

    // Shift even bits right by 1
    unsigned int even_bits = (n & even_mask) >> 1;

    // Shift odd bits left by 1
    unsigned int odd_bits = (n & odd_mask) << 1;

    // Combine the swapped bits
    return (even_bits | odd_bits);
}

// Approach 2: Using Loop, Extract, XOR
unsigned int swap_odd_even_bits_loop(unsigned int n) {
    for (int i = 0; i < 31; i += 2) { // Iterate through bit pairs
        unsigned int bit1 = (n >> i) & 1;     // Get odd-position bit
        unsigned int bit2 = (n >> (i + 1)) & 1; // Get even-position bit
        
        if (bit1 != bit2) { // Swap only if bits are different
            n ^= (1 << i);       // Toggle odd bit
            n ^= (1 << (i + 1)); // Toggle even bit
        }
    }
    return n;
}

// Approach 3: Using Loop, Extract, Clear and Set
unsigned int swap_odd_even_bits_extract(unsigned int n) {
    unsigned int result = n;

    for (int i = 0; i < 31; i += 2) {
        unsigned int bit1 = (n >> i) & 1;     // Extract odd-position bit
        unsigned int bit2 = (n >> (i + 1)) & 1; // Extract even-position bit

        result &= ~(1 << i);       // Clear bit at i
        result &= ~(1 << (i + 1)); // Clear bit at i+1

        result |= (bit1 << (i + 1)); // Set bit1 at even position
        result |= (bit2 << i);       // Set bit2 at odd position
    }

    return result;
}


// Approach 4: Using Lookup Table (Precomputed) - Additional Memory
unsigned char precomputed_swap[256]; // Lookup table for 8-bit swapping

void initialize_lookup_table() {
    for (int i = 0; i < 256; i++) {
        precomputed_swap[i] = ((i & 0xAA) >> 1) | ((i & 0x55) << 1);
    }
}

unsigned int swap_odd_even_bits_lookup(unsigned int n) {
    return (precomputed_swap[n & 0xFF] << 0) |
           (precomputed_swap[(n >> 8) & 0xFF] << 8) |
           (precomputed_swap[(n >> 16) & 0xFF] << 16) |
           (precomputed_swap[(n >> 24) & 0xFF] << 24);
}


int main() {
    unsigned int n = 23; // Binary: 00010111
    
    // Approach 1: Using Mask based approach
    printf("Before Swap:\n");
    print_binary(n);
    n = swap_odd_even_bits_xor(n);
    printf("\nAfter Swap:\n");
    print_binary(n);

    // Approach 2: Using Loop, Extract, XOR
    printf("\nBefore Swap:\n");
    print_binary(n);
    n = swap_odd_even_bits_loop(n); 
    printf("\nAfter Swap:\n");
    print_binary(n);
    
    // Approach 3: Using Loop, Extract, Clear and Set
    printf("\nBefore Swap:\n");
    print_binary(n);
    n = swap_odd_even_bits_extract(n); 
    printf("\nAfter Swap:\n");
    print_binary(n);

    // Approach 4: Using Lookup Table (Precomputed) - Additional Memory
    initialize_lookup_table(); //  Initialize table once
    printf("\nBefore Swap:\n");
    print_binary(n);
    n = swap_odd_even_bits_lookup(n); 
    printf("\nAfter Swap:\n");
    print_binary(n);

    return 0;
}
