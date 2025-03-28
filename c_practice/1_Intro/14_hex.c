#include <stdio.h>

int main() {
    int var = 0x43ff;   // Hex value (base 16)
    // int var = 0X43FF; // Same as 0x = 0X
    printf("%x\n", var);
    printf("%X\n", var);  // Same %x = %X (CAPS)

    printf("%d\n", var); // Decimal value: 
    return 0;
}

