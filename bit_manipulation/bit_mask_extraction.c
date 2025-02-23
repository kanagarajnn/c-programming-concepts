#include <stdio.h>
#include <stdint.h>

#define QOS_MASK       0b01100000  // Bits 5-6
#define ENCRYPT_MASK   0b00010000  // Bit 4
#define PRIORITY_MASK  0b00001100  // Bits 2-3
#define ACK_MASK       0b00000010  // Bit 1
#define ERROR_MASK     0b00000001  // Bit 0

int main() {
    uint8_t packet = 0x5A; // Binary: 01011010

    uint8_t qos       = (packet & QOS_MASK) >> 5;
    uint8_t encrypt   = (packet & ENCRYPT_MASK) >> 4;
    uint8_t priority  = (packet & PRIORITY_MASK) >> 2;
    uint8_t ack       = (packet & ACK_MASK) >> 1;
    uint8_t error     = (packet & ERROR_MASK);

    printf("QoS: %u\n", qos);
    printf("Encryption: %u\n", encrypt);
    printf("Priority: %u\n", priority);
    printf("ACK: %u\n", ack);
    printf("Error: %u\n", error);

    return 0;
}
