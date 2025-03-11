#include <stdio.h>

// Time: O(total number of bits)
int count_set_bits_naive(unsigned int n) {
    int count = 0;
    while (n) {
        count += n & 1; // Check if LSB is 1
        n >>= 1;        // Shift right by 1
    }
    return count;
}

// Time: O(number of 1s)
int count_set_bits_optimized(unsigned int n) {
    int count = 0;
    while (n) {
        n &= (n - 1); // Drop the lowest set bit
        count++;
    }
    return count;
}


int main() {
    unsigned int num = 0b111011; // 11101 in binary
    printf("Naïve Count of 1s: %d\n", count_set_bits_naive(num));
    printf("Optimized Count of 1s: %d\n", count_set_bits_optimized(num));
    return 0;
}
