#include <stdint.h>

/* ---------------- RCC ---------------- */
#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB2ENR     (*(volatile uint32_t*)(RCC_BASE + 0x44))

/* ---------------- GPIOA ---------------- */
#define GPIOA_BASE      0x40020000UL
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))

/* ---------------- ADC1 ---------------- */
#define ADC1_BASE       0x40012000UL
#define ADC1_CR1        (*(volatile uint32_t*)(ADC1_BASE + 0x04))
#define ADC1_CR2        (*(volatile uint32_t*)(ADC1_BASE + 0x08))
#define ADC1_SMPR2      (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC1_SQR3       (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t*)(ADC1_BASE + 0x4C))

/* ---------------- DMA2 Stream0 ---------------- */
#define DMA2_BASE       0x40026400UL
#define DMA2_S0CR       (*(volatile uint32_t*)(DMA2_BASE + 0x10))
#define DMA2_S0NDTR     (*(volatile uint32_t*)(DMA2_BASE + 0x14))
#define DMA2_S0PAR      (*(volatile uint32_t*)(DMA2_BASE + 0x18))
#define DMA2_S0M0AR     (*(volatile uint32_t*)(DMA2_BASE + 0x1C))

#define ADC_BUFFER_SIZE 10
uint16_t adc_buffer[ADC_BUFFER_SIZE];

/* ---------------- INIT ---------------- */

void ADC_DMA_Init(void)
{
    /* 1. Enable clocks */
    RCC_AHB1ENR |= (1 << 0);   // GPIOA
    RCC_AHB1ENR |= (1 << 22);  // DMA2
    RCC_APB2ENR |= (1 << 8);   // ADC1

    /* 2. PA1 → Analog */
    GPIOA_MODER |= (3 << 2);

    /* 3. Configure DMA */

    DMA2_S0CR = 0;  // Reset

    DMA2_S0PAR  = (uint32_t)&ADC1_DR;        // Peripheral = ADC data register
    DMA2_S0M0AR = (uint32_t)adc_buffer;      // Memory buffer
    DMA2_S0NDTR = ADC_BUFFER_SIZE;           // Number of transfers

    /* Channel 0, Peripheral-to-Memory, Circular mode */
    DMA2_S0CR |= (0 << 25);  // Channel 0
    DMA2_S0CR |= (0 << 6);   // Peripheral to Memory
    DMA2_S0CR |= (1 << 8);   // Circular mode
    DMA2_S0CR |= (1 << 10);  // Memory increment
    DMA2_S0CR |= (1 << 13);  // Memory size = 16-bit
    DMA2_S0CR |= (1 << 11);  // Peripheral size = 16-bit

    /* Enable DMA */
    DMA2_S0CR |= (1 << 0);

    /* 4. Configure ADC */

    ADC1_SMPR2 |= (3 << 3);  // Channel 1 sampling time
    ADC1_SQR3 = 1;           // Channel 1

    ADC1_CR2 |= (1 << 8);    // DMA enable
    ADC1_CR2 |= (1 << 1);    // Continuous mode

    ADC1_CR2 |= (1 << 0);    // ADC ON

    /* Start ADC */
    ADC1_CR2 |= (1 << 30);
}

int main(void)
{
    ADC_DMA_Init();

    while (1)
    {
        /* adc_buffer continuously updated automatically */

        /* Put breakpoint here to watch adc_buffer */
    }
}
