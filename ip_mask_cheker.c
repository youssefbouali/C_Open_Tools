#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function to validate the IP address
bool is_valid_ip(const char *ip) {
    unsigned int num;
    int parts[4];
    int count = sscanf(ip, "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]);
    
    if (count != 4) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        if (parts[i] < 0 || parts[i] > 255) {
            return false;
        }
    }

    return true;
}

// Function to validate the subnet mask
bool is_valid_mask(const char *mask) {
    unsigned int num;
    int parts[4];
    int count = sscanf(mask, "%d.%d.%d.%d", &parts[0], &parts[1], &parts[2], &parts[3]);

    if (count != 4) {
        return false;
    }

    for (int i = 0; i < 4; i++) {
        if (parts[i] < 0 || parts[i] > 255) {
            return false;
        }
    }

    // Check if subnet mask is valid
    unsigned long long bitmask = (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8) | parts[3];
    unsigned long long inverted_mask = ~bitmask;

    // Check if the inverted mask contains any 1's after the first 0
    if ((inverted_mask & (inverted_mask + 1)) != 0) {
        return false;
    }

    return true;
}

int main() {
    char ip[16];
    char mask[16];

    printf("Enter an IP address: ");
    scanf("%15s", ip);

    if (!is_valid_ip(ip)) {
        printf("Invalid IP address format!\n");
        return 1;
    }

    printf("Enter a subnet mask: ");
    scanf("%15s", mask);

    if (!is_valid_mask(mask)) {
        printf("Invalid subnet mask format!\n");
        return 1;
    }

    printf("IP address: %s\n", ip);
    printf("Subnet mask: %s\n", mask);

    return 0;
}
