#include <stdio.h>
#include <arpa/inet.h>

int main() {
    uint32_t host_val = 0x12345678;  // Example in host byte order
    uint32_t network_val = htonl(host_val);

    printf("Host Byte Order: 0x%X\n", host_val);
    printf("Network Byte Order: 0x%X\n", network_val);

    uint32_t network_val_ = 0x78563412;  // Example in network byte order
    uint32_t host_val_ = ntohl(network_val);

    printf("Network Byte Order: 0x%X\n", network_val_);
    printf("Host Byte Order: 0x%X\n", host_val_);

    return 0;
}
