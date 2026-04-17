#include <stdint.h>
#define RCC_BASE 0x40023800UL
#define RCC_CR   (*(volatile uint32_t*)(RCC_BASE + 0x00))
#define RCC_CFGR (*(volatile uint32_t*)(RCC_BASE + 0x08))

int main(void)
{
    uint32_t clk_src = (RCC_CFGR >> 2) & 0x3;  // Bits[3:2] -> system clock source
    // 00 = HSI, 01 = HSE, 10 = PLL

    if (clk_src == 0x00)
        ; // ✅ running from HSI
    else if (clk_src == 0x01)
        ; // using HSE
    else
        ; // using PLL

    while (1);
}
