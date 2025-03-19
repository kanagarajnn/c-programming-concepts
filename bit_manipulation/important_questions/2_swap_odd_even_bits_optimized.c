/*
    Swap odd and even bits (swap adjacent bits)
    input  = 1001  0100
    output = 0110  1000


1. Understand
    - swap odd and even bits
    - input: integer bit sequence
    - output: swapped bit sequence

2. Solutions
    1) Solution 1: Loop over the bits, extract two bits, clear and swap
        Time: O(N)
        Space: O(1)
    2) Solution 2: Loop over the bits, extract two bits and if not same, just toggle the bits using XOR
        Time: O(N)
        Space: O(1)
    3) Solution 3: Create ODD MASK and EVEN MASK, extract ODD and EVEN, shift and create the swapped result
        Time: O(1)
        Space: O(1)
        Algorithm:
            - 0x55 - 0x01010101 ODD Bitmask
            - shift left
            - 0xAA - 0x10101010 EVEN Bitmask
            - shift right
            - combine both

3. Design
4. Coding
5. Complexity
6. Validation
7. Testing

Key Learnings:
1) Use Inline Functions for Efficiency
    Embedded firmware, especially for cellular modems, benefits from inline functions to avoid unnecessary function call overhead.
2) size_t is architecture dependant
3) since i is always in the range [0 to 7], you can use uint8_t instead. In embedded systems, size_t may be 16-bit or 32 bit
4) Static keyword for local binding (not accessible outside of the file)

*/

#include <stdio.h>
#include <stdint.h>

#define ODD_BIT_MASK  0x55  // 0b01010101 - Odd-positioned bits
#define EVEN_BIT_MASK 0xAA  // 0b10101010 - Even-positioned bits

uint8_t swap_odd_even_bits_loop_1(uint8_t input) {
    for (uint8_t i = 0; i < 8; i = i + 2) {
        int first_bit = (input >> i) & 1;
        int second_bit = (input >> (i + 1)) & 1;

        if (first_bit != second_bit) {
            input &= ~(1 << (i + 1)); // clear the second bit
            input |= first_bit << (i + 1); // set the first bit in second bit position

            input &= ~(1 << i); // clear the first bit
            input |= second_bit << i; // set the second bit in first bit postion
        }
    }

    return input;
}

uint8_t swap_odd_even_bits_loop_2_with_xor(uint8_t input) {
    for (uint8_t i = 0; i < 8; i = i + 2) {
        // Check if the adjacent bits are different, then swap using XOR
        if (((input >> i) & 1) != ((input >> (i + 1)) & 1)) {
            input ^= (1 << i) | (1 << (i + 1)); // Toggle both bits
        }
    }
    return input;
}

static inline uint8_t swap_odd_even_bits_bitmask(uint8_t input) {
    return ((input & ODD_BIT_MASK) << 1 | (input & EVEN_BIT_MASK) >> 1);
}

void print_bits(uint8_t input) {
    printf("0b");
    for (uint8_t i = 8; i > 0; i--) {  // Start from 8 instead of 7
        printf("%c", (input & (1 << (i - 1))) ? '1' : '0');
    }
    printf(" (%d)\n", input);
}


int main() {
    uint8_t testcases[] = {0b00000000, 0b11111111, 0b10101010, 0b01010101, 0b10000001};

    for (size_t i = 0; i < sizeof(testcases) / sizeof(testcases[0]); i++) {
        uint8_t input = testcases[i];

        printf("\n\nTestcase %zu\n", i + 1);
        printf("Solution 1: ===========\n");
        printf("Original: ");
        print_bits(input);
        printf("Swapped : ");
        print_bits(swap_odd_even_bits_loop_1(input));

        printf("\nSolution 2: ===========\n");
        printf("Original: ");
        print_bits(input);
        printf("Swapped : ");
        print_bits(swap_odd_even_bits_loop_2_with_xor(input));

        printf("\nSolution 3: ===========\n");    
        printf("Original: ");
        print_bits(input);
        printf("Swapped : ");
        print_bits(swap_odd_even_bits_bitmask(input));
    }

    return 0;
}