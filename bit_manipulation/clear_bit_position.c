#include <stdio.h>
#define CLEAR_BIT(num, pos) ((num) & ~(1 << pos))

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int main() {
    int reg = 0b00001110;  // Initial register value (decimal 14)
    int bit_position = 2;  // We want to set the 2nd bit

    print_binary(reg);
    
    reg = CLEAR_BIT(reg, bit_position);   
    printf("\nAfter setting bit %d: \n", bit_position);
    
    print_binary(reg);
}