#include <stdio.h>

#pragma pack(1) 

struct {
    double a; // 8 bytes
    union { // 8 bytes
        char b[4];  // 4 * 1 = 4 bytes
        double c;   // 8 bytes (max size: union size)
        int d;      // 4 bytes
    } e; // max(4, 8) => 8 bytes
    char f[4]; // 4 * 1 = 4 bytes
} s; // Total is 20 bytes


union {
    double a; // 8 bytes
    struct { // 8 bytes
        char b[4];  // 4 * 1 = 4 bytes
        double c;   // 8 bytes
        int d;      // 4 bytes
    } e; // 16 bytes
    char f[4]; // 4 * 1 = 4 bytes
} u; // Total is 16 bytes (due to union)


int main() {
    printf("size of struct s is %lu\n", sizeof(s));  // 20 bytes (without padding)
    printf("size of union u is %lu\n", sizeof(u)); // 16 bytes (due to max union size)
    return 0;
}