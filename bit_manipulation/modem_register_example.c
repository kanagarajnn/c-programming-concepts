#include <stdio.h>

#define POWER_ON        (1 << 0)    // Bit 0: Modem power state
#define NETWORK_UP      (1 << 1)    // Bit 1: Network connectivity status
#define DATA_MODE       (1 << 2)    // Bit 2: Data mode enabled
#define CALL_ACTIVE     (1 << 3)    // Bit 3: Active voice call


void print_binary(unsigned int num) {
    for (int i = sizeof(num) * 8 - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}


int main() {
    int modem_register = 0;     // All flags initially off
    printf("Modem Register Initial Value: \n");
    print_binary(modem_register);

    // Enable POWER_ON and NETWORK_UP
    modem_register |= (POWER_ON | NETWORK_UP);

    printf("Modem Register After Power & Network On: \n");
    print_binary(modem_register);

    // Disable NETWORK_UP (Clear Bit)
    modem_register &= ~NETWORK_UP;
    printf("Modem Register After Network OFF: \n");
    print_binary(modem_register);
    
    // Toggle CALL_ACTIVE status
    modem_register ^= CALL_ACTIVE;
    printf("Modem Register After Toggling CALL_ACTIVE: \n");
    print_binary(modem_register);

    return 0;
}