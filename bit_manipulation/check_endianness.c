#include <stdio.h>
#include <stdint.h>

int check_endianness() {
    union {
        unsigned int i;   // 4-byte integer
        unsigned char c[4];  // 4 bytes in an array
    } test = {0x12345678};  // Initialize integer with known value

    return (test.c[0] == 0x12) ? 0 : 1; // 0 = Big Endian, 1 = Little Endian
}

/*
A union allows multiple data types to share the same memory.
Here, test.i and test.c[4] share memory:
test.i = 0x12345678 stores the integer.
test.c[4] represents the same memory as an array of bytes.
*/


uint16_t swap_endian16(uint16_t value) {
    return (value >> 8) | (value << 8);
}


uint32_t swap_endian32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |  // Move byte 0 to byte 3
           ((value >> 8)  & 0x0000FF00) |  // Move byte 1 to byte 2
           ((value << 8)  & 0x00FF0000) |  // Move byte 2 to byte 1
           ((value << 24) & 0xFF000000);   // Move byte 3 to byte 0
}


uint64_t swap_endian64(uint64_t value) {
    return ((value >> 56) & 0x00000000000000FF) |  // Move byte 0 to byte 7
           ((value >> 40) & 0x000000000000FF00) |  // Move byte 1 to byte 6
           ((value >> 24) & 0x0000000000FF0000) |  // Move byte 2 to byte 5
           ((value >> 8)  & 0x00000000FF000000) |  // Move byte 3 to byte 4
           ((value << 8)  & 0x000000FF00000000) |  // Move byte 4 to byte 3
           ((value << 24) & 0x0000FF0000000000) |  // Move byte 5 to byte 2
           ((value << 40) & 0x00FF000000000000) |  // Move byte 6 to byte 1
           ((value << 56) & 0xFF00000000000000);   // Move byte 7 to byte 0
}


int main() {
    if (check_endianness())
        printf("System is Little Endian\n");
    else
        printf("System is Big Endian\n");
 

    // 16 bit
    uint16_t num1 = 0x1234; // Little-endian representation
    uint16_t swapped1 = swap_endian16(num1);
    printf("Original: 0x%04X, Swapped: 0x%04X\n", num1, swapped1);


    // 32 bit
    uint32_t num2 = 0x12345678;
    uint32_t swapped2 = swap_endian32(num2);
    printf("Original: 0x%08X, Swapped: 0x%08X\n", num2, swapped2);
    
    // 64 bit
    uint64_t num3 = 0x123456789ABCDEF0;
    uint64_t swapped3 = swap_endian64(num3);
    printf("Original: 0x%016llX, Swapped: 0x%016llX\n", num3, swapped3);
    
    return 0;
}

