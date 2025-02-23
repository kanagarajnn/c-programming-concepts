#include <stdio.h>
#include <stdint.h>  // For fixed-width integers

// Left rotate (ROL)
uint32_t rotate_left(uint32_t num, int shift) {
    int bits = sizeof(num) * 8;  // 32 bits for uint32_t
    shift = shift % bits;  // Prevents overflow
    return (num << shift) | (num >> (bits - shift));
}

// Right rotate (ROR)
uint32_t rotate_right(uint32_t num, int shift) {
    int bits = sizeof(num) * 8;  // 32 bits
    shift = shift % bits;
    return (num >> shift) | (num << (bits - shift));
}

int main() {
    uint32_t num = 0x12345678;  // Example: 305419896 (Hex: 0x12345678)
    int shift = 8; // Rotate by 8 bits

    printf("Original: 0x%X\n", num);
    printf("Left Rotate by %d: 0x%X\n", shift, rotate_left(num, shift));
    printf("Right Rotate by %d: 0x%X\n", shift, rotate_right(num, shift));

    return 0;
}

