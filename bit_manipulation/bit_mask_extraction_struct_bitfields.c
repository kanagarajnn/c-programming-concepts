#include <stdio.h>
#include <stdint.h>

// Define a struct with bitfields
typedef struct {
    uint8_t error     : 1;  // 1 bit (LSB)
    uint8_t ack       : 1;  // 1 bit
    uint8_t priority  : 2;  // 2 bits
    uint8_t encrypt   : 1;  // 1 bit
    uint8_t qos       : 2;  // 2 bits
    uint8_t reserved  : 1;  // 1 bit (MSB, unused in this example)
} Packet;

int main() {
    // Initialize a packet with the same value (0x5A -> Binary: 01011010)
    Packet packet = { .qos = 2, .encrypt = 1, .priority = 2, .ack = 1, .error = 0 };

    printf("QoS: %u\n", packet.qos);
    printf("Encryption: %u\n", packet.encrypt);
    printf("Priority: %u\n", packet.priority);
    printf("ACK: %u\n", packet.ack);
    printf("Error: %u\n", packet.error);

    return 0;
}
