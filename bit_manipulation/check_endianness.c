#include <stdio.h>

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

// AB CD EF GH
//          AB
//       CD
//    EF
// GH

unsigned int swap_endianness(unsigned int n) {
    return ((n >> 24) & 0xFF) |  // Move byte 0 to byte 3
           ((n >> 8) & 0xFF00) |  // Move byte 1 to byte 2
           ((n << 8) & 0xFF0000) |  // Move byte 2 to byte 1
           ((n << 24) & 0xFF000000);  // Move byte 3 to byte 0
}


int main() {
    if (check_endianness())
        printf("System is Little Endian\n");
    else
        printf("System is Big Endian\n");
    return 0;
}

