#include <stdio.h>
#define TOGGLE_BIT(num, pos) ((num) ^ ((1 << pos)))

void print_binary(unsigned int number) {
    for (int i = sizeof(number) * 8 - 1; i >= 0; i--) {
        printf("%d", (number >> i) & 1);
    }
    printf("\n");
}

int main() {
    int reg = 0b00001010;   // Register with Decimal value 10
    int bit_position = 1;   // We want to toggle the 1st bit

    print_binary(reg);
    
    reg = TOGGLE_BIT(reg, bit_position);
    printf("After toggling bit %d: \n", bit_position);
    
    print_binary(reg);

    return 0;
}