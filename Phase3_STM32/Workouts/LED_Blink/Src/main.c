#include <stdint.h>

#define PERIPH_BASE       0x40000000UL
#define AHB1PERIPH_OFFSET 0x00020000UL
#define AHB1PERIPH_BASE   (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define RCC_BASE          (AHB1PERIPH_BASE + 0x3800UL)
#define GPIOD_BASE        (AHB1PERIPH_BASE + 0x0C00UL)

#define RCC_AHB1ENR       (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define GPIOD_MODER       (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_ODR         (*(volatile uint32_t *)(GPIOD_BASE + 0x14))

static void delay_ms(uint32_t ms)
{
    for (uint32_t i = 0; i < (ms * 800); i++) __asm__("nop");
}

int main(void){
	RCC_AHB1ENR|=(1<<3);
	GPIOD_MODER &=~(3<<(12*2));
	GPIOD_MODER |=(1<<(12*2));
	while(1){
		GPIOD_ODR ^=(1<<12);
		delay_ms(1000);
	}
}
