#include <stdio.h>

/*
- Assume 32 bit architecture (word size = 32 bit)
- CPU will read 4 bytes (32 bit) in one cycle

Memory is important - use structure packing
CPU cycles is important - use structure padding
Both Memory & Cycle - Keep the members aligned as much as possible (same types together)

*/

struct st1 {
    char a;     // 1 byte
    char b;     // 1 byte + 2 bytes padding (to align)
    int c;      // 4 bytes 
} s1;   // Total size = 8 bytes

struct st2 {
    char a;     // 1 byte + 3 bytes padding
    int c;      // 4 bytes 
    char b;     // 1 byte + 3 bytes padding
} s2;   // Total size = 12 bytes

#pragma pack(1)

struct st3 {
    char a;     // 1 byte + 3 bytes padding
    int c;      // 4 bytes 
    char b;     // 1 byte + 3 bytes padding
} s3;   // Total size = 12 bytes

int main() {
    printf("Size of struct s1 is %lu\n", sizeof(s1)); // 8 bytes
    printf("Size of struct s2 is %lu\n", sizeof(s2)); // 12 bytes
    printf("Size of struct s3 is %lu", sizeof(s3));  // 6 bytes after structure packing

    return 0;
}