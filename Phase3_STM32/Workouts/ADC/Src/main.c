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
#define ADC1_SR         (*(volatile uint32_t*)(ADC1_BASE + 0x00))
#define ADC1_CR1        (*(volatile uint32_t*)(ADC1_BASE + 0x04))
#define ADC1_CR2        (*(volatile uint32_t*)(ADC1_BASE + 0x08))
#define ADC1_SMPR2      (*(volatile uint32_t*)(ADC1_BASE + 0x10))
#define ADC1_SQR3       (*(volatile uint32_t*)(ADC1_BASE + 0x34))
#define ADC1_DR         (*(volatile uint32_t*)(ADC1_BASE + 0x4C))

/* Function to initialize ADC */
void ADC1_Init(void)
{
    /* 1. Enable GPIOA clock */
    RCC_AHB1ENR |= (1 << 0);

    /* 2. Set PA1 to Analog mode (MODER1 = 11) */
    GPIOA_MODER |= (3 << 2);

    /* 3. Enable ADC1 clock */
    RCC_APB2ENR |= (1 << 8);

    /* 4. Set sampling time for channel 1 */
    ADC1_SMPR2 |= (3 << 3);  // 56 cycles (safe)

    /* 5. Select channel 1 in regular sequence */
    ADC1_SQR3 = 1;

    /* 6. Enable ADC */
    ADC1_CR2 |= (1 << 0);
}

/* Function to read ADC value */
uint16_t ADC1_Read(void)
{
    /* Start conversion */
    ADC1_CR2 |= (1 << 30);

    /* Wait until conversion complete (EOC = bit 1) */
    while (!(ADC1_SR & (1 << 1)));

    /* Read result */
    return (uint16_t)ADC1_DR;
}

int main(void)
{
    volatile uint16_t adc_value = 0;

    ADC1_Init();

    while (1)
    {
        adc_value = ADC1_Read();
        for (volatile int i = 0; i < 500000; i++);

        /* Put breakpoint here to watch adc_value */
    }
}
