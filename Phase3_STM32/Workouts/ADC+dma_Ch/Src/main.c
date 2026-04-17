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
#define ADC1_SQR1       (*(volatile uint32_t*)(ADC1_BASE + 0x2C))
#define ADC1_SQR3       (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t*)(ADC1_BASE + 0x4C))

/* ---------------- DMA2 Stream0 ---------------- */
#define DMA2_BASE       0x40026400UL
#define DMA2_S0CR       (*(volatile uint32_t*)(DMA2_BASE + 0x10))
#define DMA2_S0NDTR     (*(volatile uint32_t*)(DMA2_BASE + 0x14))
#define DMA2_S0PAR      (*(volatile uint32_t*)(DMA2_BASE + 0x18))
#define DMA2_S0M0AR     (*(volatile uint32_t*)(DMA2_BASE + 0x1C))

#define NUM_CHANNELS 3
uint16_t adc_buffer[NUM_CHANNELS];

void ADC_DMA_MultiChannel_Init(void)
{
    /* 1. Enable clocks */
    RCC_AHB1ENR |= (1 << 0);   // GPIOA
    RCC_AHB1ENR |= (1 << 22);  // DMA2
    RCC_APB2ENR |= (1 << 8);   // ADC1

    /* 2. PA1, PA2, PA3 → Analog */
    GPIOA_MODER |= (3 << 2);   // PA1
    GPIOA_MODER |= (3 << 4);   // PA2
    GPIOA_MODER |= (3 << 6);   // PA3

    /* 3. Configure DMA */
    DMA2_S0CR = 0;

    DMA2_S0PAR  = (uint32_t)&ADC1_DR;
    DMA2_S0M0AR = (uint32_t)adc_buffer;
    DMA2_S0NDTR = NUM_CHANNELS;

    DMA2_S0CR |= (1 << 8);   // Circular mode
    DMA2_S0CR |= (1 << 10);  // Memory increment
    DMA2_S0CR |= (1 << 13);  // Memory size = 16-bit
    DMA2_S0CR |= (1 << 11);  // Peripheral size = 16-bit

    DMA2_S0CR |= (1 << 0);   // Enable DMA

    /* 4. Configure ADC */

    ADC1_CR1 |= (1 << 8);    // Scan mode

    ADC1_CR2 |= (1 << 1);    // Continuous mode
    ADC1_CR2 |= (1 << 8);    // DMA enable

    /* Set sampling time for channels */
    ADC1_SMPR2 |= (3 << 3);   // CH1
    ADC1_SMPR2 |= (3 << 6);   // CH2
    ADC1_SMPR2 |= (3 << 9);   // CH3

    /* Sequence length = 3 conversions */
    ADC1_SQR1 |= ((NUM_CHANNELS - 1) << 20);

    /* Channel order */
    ADC1_SQR3 |= (1 << 0);   // 1st = CH1
    ADC1_SQR3 |= (2 << 5);   // 2nd = CH2
    ADC1_SQR3 |= (3 << 10);  // 3rd = CH3

    /* Enable ADC */
    ADC1_CR2 |= (1 << 0);

    /* Start conversion */
    ADC1_CR2 |= (1 << 30);
}

int main(void)
{
    ADC_DMA_MultiChannel_Init();

    while (1)
    {
        /* adc_buffer[0] → PA1
           adc_buffer[1] → PA2
           adc_buffer[2] → PA3 */

        /* Debug / process values */
    }
}
