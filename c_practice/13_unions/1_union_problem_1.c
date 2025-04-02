#include <stdio.h>

struct {
    short s[5];     // 5 * 2 bytes = 10 bytes 
    union {
        float y;    // 4 bytes
        long z;     // 8 bytes
    } u;    // max(4, 8) => 8 bytes
} t; // Total is 18 bytes + 6 bytes for padding => 24 bytes

int main() {
    printf("size of struct t is %lu\n", sizeof(t));
    return 0;
}