#include <stdio.h>
// #define CHECK_BIT(num, pos) ((num >> pos) & 1) // IF BIT is set, returns one, else zero
#define CHECK_BIT(num, bit) ((num) & (1 << bit))  // IF BIT is set, returns non-zero, else zero

void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

int main() {
    int status = 0b00001010;  // Initial register value (decimal 10)
    int bit_to_check = 1; 

    print_binary(status);
    
    if (CHECK_BIT(status, bit_to_check)) {
        printf("Bit %d is SET \n", bit_to_check);
    } else {
        printf("Bit %d is NOT SET \n", bit_to_check);
    } 

}