/*
    Swap two bits
    input  = 1001  0100, bit position 1 & 4 (assume bit position starts from 0)
    output = 1000  0110 


1. Understand
    - swap two bits
    - input: integer bit sequence
    - output: swapped bit sequence

2. Solutions
    1) Solution 1: Extract two bits, clear and swap
        Time: O(1)
        Space: O(1)
    2) Solution 2: Extract two bits, if not same, just toggle both using XOR
        Time: O(1)
        Space: O(1)

3. Design
4. Coding
5. Complexity
6. Validation
7. Testing

Key Learnings:
1) Use static inline for Performance Optimization
    Why? In embedded firmware, function call overhead should be minimized.
    How? Declare frequently used small functions as static inline to ensure zero overhead function calls.

2) Add edge case testing for robustness

*/

#include <stdio.h>
#include <stdint.h>


static inline uint8_t swap_two_bits_1(uint8_t input, uint8_t p1, uint8_t p2) {
    int first_bit = (input >> p1) & 1;
    int second_bit = (input >> p2) & 1;

    if (first_bit != second_bit) {
        input &= ~(1 << p2); // clear the second bit
        input |= first_bit << p2; // set the first bit in second bit position

        input &= ~(1 << p1); // clear the first bit
        input |= second_bit << p1; // set the second bit in first bit postion
    }

    return input;
}

static inline uint8_t swap_two_bits_2_with_xor(uint8_t input, uint8_t p1, uint8_t p2) {
    // Check if the bits are different, then swap using XOR
    if (((input >> p1) & 1) != ((input >> p2) & 1)) {
        input ^= (1 << p1) | (1 << p2); // Swaps bits directly
    }
 
    return input;
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
        print_bits(swap_two_bits_1(input, 1, 4));

        printf("\nSolution 2: ===========\n");
        printf("Original: ");
        print_bits(input);
        printf("Swapped : ");
        print_bits(swap_two_bits_2_with_xor(input, 1, 4));
    }

    return 0;
}