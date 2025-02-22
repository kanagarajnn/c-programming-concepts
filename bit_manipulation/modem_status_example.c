#include <stdio.h>
#include <stdint.h>

#define LINK_ACTIVE_BIT 0
#define SIGNAL_OK_BIT   1
#define MODE_5G_BIT     2
#define ROAMING_BIT     3

#define CHECK_BIT(reg, bit) ((reg) & (1 << (bit)))

void check_modem_status(uint8_t modem_register) {
    if (CHECK_BIT(modem_register, LINK_ACTIVE_BIT)) {
        printf("Modem is CONNECTED\n");
    }
    if (CHECK_BIT(modem_register, SIGNAL_OK_BIT)) {
        printf("Signal strength is GOOD\n");
    }
    if (CHECK_BIT(modem_register, MODE_5G_BIT)) {
        printf("5G mode is ENABLED\n");
    }
    if (CHECK_BIT(modem_register, ROAMING_BIT)) {
        printf("Roaming is ENABLED\n");
    }
}


int main() {
    uint8_t modem_status = 0b00001101; 
    // Modem is connected (link active), weak signal, 5G enabled, roaming enabled

    check_modem_status(modem_status);

    return 0;
}
