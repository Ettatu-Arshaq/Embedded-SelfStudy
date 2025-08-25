#include <stdio.h>
#include <stdint.h>

// Function Prototypes
void setBit(uint8_t *reg, int bit);
void clearBit(uint8_t *reg, int bit);
void toggleBit(uint8_t *reg, int bit);
int readBit(uint8_t reg, int bit);
void printBinary(uint8_t reg);

int main() {
    uint8_t reg = 0x00;  // Simulated 8-bit register
    int choice, bit;

    while (1) {
        printf("\n--- 8-Bit Register Simulator ---\n");
        printf("1. Set Bit\n");
        printf("2. Clear Bit\n");
        printf("3. Toggle Bit\n");
        printf("4. Read Bit\n");
        printf("5. Print Register\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            printf("Enter bit position (0-7): ");
            scanf("%d", &bit);
        }

        switch (choice) {
            case 1: setBit(&reg, bit); break;
            case 2: clearBit(&reg, bit); break;
            case 3: toggleBit(&reg, bit); break;
            case 4:
                printf("Bit %d = %d\n", bit, readBit(reg, bit));
                break;
            case 5: printBinary(reg); break;
            case 6: return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

// Function Definitions
void setBit(uint8_t *reg, int bit) {
    // TODO: use OR to set the bit
    *reg|=(1<<bit);
}

void clearBit(uint8_t *reg, int bit) {
    // TODO: use AND with NOT to clear the bit
    *reg&=~(1<<bit);
}

void toggleBit(uint8_t *reg, int bit) {
    // TODO: use XOR to toggle the bit
    *reg^=(1<<bit);
}

int readBit(uint8_t reg, int bit) {
    // TODO: return 1 if bit is set, 0 otherwise
    if(reg&(1<<bit)){
        return 1;
    }
    else return 0;
}

void printBinary(uint8_t reg) {
    printf("Register: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
    }
    printf("\n");
}
