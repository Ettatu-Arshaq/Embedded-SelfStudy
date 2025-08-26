#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>  // For Sleep(ms) on Windows. Use usleep() on Linux.

typedef struct {
    uint8_t pattern;   // 8-bit LED pattern (1 = ON, 0 = OFF)
    int delay_ms;      // Delay in milliseconds
} Config;

void setConfig(Config *cfg);
void saveConfig(Config *cfg, const char *filename);
int loadConfig(Config *cfg, const char *filename);
void simulateBlink(Config cfg);

int main() {
    Config cfg;
    int choice;
    const char *file = "config.bin";

    // Try loading previous config
    if (loadConfig(&cfg, file)) {
        printf("\nLoaded saved config!\n");
    } else {
        printf("No saved config found. Using defaults.\n");
        cfg.pattern = 0b1010;   // Default: LED1 ON, LED2 OFF, LED3 ON, LED4 OFF
        cfg.delay_ms = 500;     // 500 ms
    }

    while (1) {
        printf("\n\n===== LED Blinker Config Menu =====\n");
        printf("1. Set Config\n");
        printf("2. Save Config\n");
        printf("3. Simulate Blinking\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (getchar() != '\n');  // flush input buffer
        switch (choice) {
            case 1: setConfig(&cfg); break;
            case 2: saveConfig(&cfg, file); break;
            case 3: simulateBlink(cfg); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}

void setConfig(Config *cfg) {
    // TODO: Take user input for pattern & delay
    // Example: pattern = binary (like 1010), delay_ms = 500
    uint8_t bitset=0;
    char bitsetstr[9];
    unsigned int delay;
    printf("Set the Bit for lighting(eg:10101010-8bit) :");
    scanf("%8s",bitsetstr);
    printf("Set the Delay for lighting in ms(eg:500) :");
    scanf("%u",&delay);
    for(int i=0;i<8;i++){
        if(bitsetstr[i]=='1'){
            bitset|=(1<<(7-i));
        }
    }
    cfg->pattern=bitset;
    cfg->delay_ms=delay;
    int flagset=1;

    if(flagset==1) printf("\nBit Set Sucessfully");
    else printf("\nBit Set failed");

}

void saveConfig(Config *cfg, const char *filename) {
    // TODO: Save struct to file (use fwrite)
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("\nERROR! Couldn't Open File %s\n", filename);
        return;
    }

    size_t writ = fwrite(cfg, sizeof(*cfg), 1, fp);
    if (writ != 1) printf("Error writing to file!\n");
    else{
        printf("Saved Successfully\n");
        printf("Pattern:%u",cfg->pattern);
        printf("(");
        for (int i = sizeof(cfg->pattern) * 8 - 1; i >= 0; i--) {
            printf("%d", (cfg->pattern >> i) & 1);
        }
        printf(")");
        printf("\nDelay:%d",cfg->delay_ms);
    }
    fclose(fp);
}


int loadConfig(Config *cfg, const char *filename) {
    // TODO: Load struct from file (use fread)
    // Return 1 if loaded successfully, 0 if file not found
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("\nERROR! Couldn't Open File %s\n", filename);
        return 0;
    }
    size_t read = fread(cfg, sizeof(*cfg), 1, fp);
    fclose(fp);
    if (read != 1){
        printf("Error reading from file!\n");
        return 0;
    }
    else{
        printf("Read Successfully\n");
        printf("Pattern:%u",cfg->pattern);
        printf("(");
        for (int i = sizeof(cfg->pattern) * 8 - 1; i >= 0; i--) {
            printf("%d", (cfg->pattern >> i) & 1);
        }
        printf(")");
        printf("\nDelay:%d",cfg->delay_ms);
    return 1;
    }
}
void simulateBlink(Config cfg) {
    // TODO: Loop through 8 bits of cfg.pattern
    // Print "LEDx: ON/OFF"
    // Add delay (Sleep(cfg.delay_ms))
    for (int repeat = 0; repeat < 5; repeat++) {
        for (int i = 7; i >= 0; i--) {
            printf("LED%d: %s\n", 8-i, ((cfg.pattern >> i) & 1) ? "ON" : "OFF");
            Sleep(cfg.delay_ms);
        }
        printf("--- Cycle %d Complete ---\n", repeat+1);
    }

    printf("End");
}
