#include <stdint.h>

/* RCC Registers */
#define RCC_BASE        0x40023800UL
#define RCC_AHB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x30))
#define RCC_APB1ENR     (*(volatile uint32_t*)(RCC_BASE + 0x40))
/* GPIOA Registers */
#define GPIOA_BASE      0x40020000UL
#define GPIOA_MODER     (*(volatile uint32_t*)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL      (*(volatile uint32_t*)(GPIOA_BASE + 0x20))
/* USART2 Registers */
#define USART2_BASE     0x40004400UL
#define USART2_SR       (*(volatile uint32_t*)(USART2_BASE + 0x00))
#define USART2_DR       (*(volatile uint32_t*)(USART2_BASE + 0x04))
#define USART2_BRR      (*(volatile uint32_t*)(USART2_BASE + 0x08))
#define USART2_CR1      (*(volatile uint32_t*)(USART2_BASE + 0x0C))
//LED
#define GPIOD_BASE      0x40020C00UL
#define GPIOD_MODER     (*(volatile uint32_t*)(GPIOD_BASE + 0x00))
#define GPIOD_ODR       (*(volatile uint32_t*)(GPIOD_BASE + 0x14))
//Timer Reg
#define TIM2_BASE   0x40000000UL
#define TIM2_PSC    (*(volatile uint32_t*)(TIM2_BASE + 0x28))
#define TIM2_ARR    (*(volatile uint32_t*)(TIM2_BASE + 0x2C))
#define TIM2_CCR1   (*(volatile uint32_t*)(TIM2_BASE + 0x34))
#define TIM2_CCMR1  (*(volatile uint32_t*)(TIM2_BASE + 0x18))
#define TIM2_CCER   (*(volatile uint32_t*)(TIM2_BASE + 0x20))
#define TIM2_CR1    (*(volatile uint32_t*)(TIM2_BASE + 0x00))

//------------Defines-----------------
#define BUFFER_SIZE 50

char rx_buffer[BUFFER_SIZE];
int index = 0;

int temp = 0;
int light = 0;

int fan_manual = -1;   // -1 means auto mode
int led_manual = -1;   // -1 means auto mode
int status_requested = 0;

void PWM_GPIO_Init()
{
    GPIOA_MODER &= ~(0x3 << 0);
    GPIOA_MODER |=  (0x2 << 0);   // AF mode

    GPIOA_AFRL &= ~(0xF << 0);
    GPIOA_AFRL |=  (0x1 << 0);    // AF1 = TIM2
}

void PWM_Init()
{
    TIM2_PSC = 16 - 1;     // 16 MHz /16 = 1 MHz
    TIM2_ARR = 1000 - 1;   // 1 kHz PWM

    TIM2_CCR1 = 0;         // Start with 0% duty

    TIM2_CCMR1 |= (6 << 4); // PWM mode 1
    TIM2_CCMR1 |= (1 << 3); // Enable preload
    TIM2_CCER  |= (1 << 0); // Enable CH1

    TIM2_CR1 |= (1 << 0);   // Enable timer
}

void FAN_SetSpeed(int duty)
{
    if (duty > 100) duty = 100;
    if (duty < 0) duty = 0;

    TIM2_CCR1 = duty * 10; // since ARR = 1000
}

void control_fan()
{
    if (fan_manual != -1)
    {
        FAN_SetSpeed(fan_manual);
        return;
    }

    int duty;

    if (temp < 500)
    {
        duty = 0;
    }
    else
    {
        if (temp > 4000) temp = 4000;

        duty = temp / 40;

        if (duty < 20) duty = 20;
    }

    FAN_SetSpeed(duty);
}
void LED_Init()
{
	RCC_AHB1ENR |= (1 << 3); // Enable GPIOD
    GPIOD_MODER &= ~(0x3 << 24); // Clear PD12
    GPIOD_MODER |=  (0x1 << 24); // Set as OUTPUT
}
void LED_ON()
{
    GPIOD_ODR |= (1 << 12);
}

void LED_OFF()
{
    GPIOD_ODR &= ~(1 << 12);
}
void control_led()
{
    if (led_manual == 1)
        LED_ON();
    else if (led_manual == 0)
        LED_OFF();
    else
    {
        if (light < 1000)
            LED_ON();
        else
            LED_OFF();
    }
}

void UART2_Clock_Enable()
{
    RCC_AHB1ENR |= (1 << 0);   // Enable GPIOA clock
    RCC_APB1ENR |= (1 << 17);  // Enable USART2 clock
    RCC_APB1ENR |= (1 << 0); // TIM2 for PWM
}

void UART2_GPIO_Init()
{
    /* Set PA2 and PA3 to Alternate Function mode (10) */
    GPIOA_MODER &= ~(0xF << 4);   // Clear bits for PA2, PA3
    GPIOA_MODER |=  (0xA << 4);   // Set AF mode

    /* Select AF7 (USART2) */
    GPIOA_AFRL &= ~(0xFF << 8);   // Clear AFRL for PA2, PA3
    GPIOA_AFRL |=  (0x77 << 8);   // AF7 for both
}


void UART2_Init()
{
    /* Baud rate = 115200 (Assuming 16 MHz clock) */
    USART2_BRR = 0x8B;

    /* Enable TX, RX */
    USART2_CR1 |= (1 << 3);  // TE
    USART2_CR1 |= (1 << 2);  // RE

    /* Enable USART */
    USART2_CR1 |= (1 << 13); // UE
}

void UART2_WriteChar(char c)
{
    while (!(USART2_SR & (1 << 7))); // Wait until TXE = 1
    USART2_DR = c;
}

char UART2_ReadChar()
{
    while (!(USART2_SR & (1 << 5))); // Wait until RXNE = 1
    return (char)USART2_DR;
}

int startsWith(char *str, char *prefix)
{
    while (*prefix)
    {
        if (*str != *prefix)
            return 0;

        str++;
        prefix++;
    }
    return 1;
}

int parse_value(char *str)
{
    int value = 0;

    while (*str >= '0' && *str <= '9')
    {
        value = value * 10 + (*str - '0');
        str++;
    }

    return value;
}


void process_command(char *cmd)
{
    if (startsWith(cmd, "TEMP:") ||startsWith(cmd, "Temp:") ||startsWith(cmd, "temp:"))
    {
        temp = parse_value(&cmd[5]);
    }
    else if (startsWith(cmd, "LIGHT:") ||startsWith(cmd, "Light:") ||startsWith(cmd, "light:"))
    {
        light = parse_value(&cmd[6]);
    }
    else if (startsWith(cmd, "FAN:"))
    {
        fan_manual = parse_value(&cmd[4]);  // 0–100
    }

    else if (startsWith(cmd, "LED:ON"))
    {
        led_manual = 1;
    }
    else if (startsWith(cmd, "LED:OFF"))
    {
        led_manual = 0;
    }
    else if (startsWith(cmd, "AUTO"))
    {
        fan_manual = -1;
        led_manual = -1;
    }
    else if (startsWith(cmd, "STATUS"))
    {
        status_requested = 1;
    }
}

void UART2_WriteNumber(int num)
{
    char buf[10];
    int i = 0;

    if (num == 0)
    {
        UART2_WriteChar('0');
        return;
    }

    while (num > 0)
    {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    while (i > 0)
    {
        UART2_WriteChar(buf[--i]);
    }
}

int main()
{
    UART2_Clock_Enable();
    UART2_GPIO_Init();
    UART2_Init();
    LED_Init();
    PWM_GPIO_Init();
    PWM_Init();
    while (1)
    {
        char c = UART2_ReadChar();

        if (c == '\r' || c == '\n')
        {
            rx_buffer[index] = '\0';

            process_command(rx_buffer);
            control_led();
            control_fan();

            if (status_requested)
            {
                UART2_WriteChar('\n');

                UART2_WriteChar('T');
                UART2_WriteChar(':');
                UART2_WriteNumber(temp);
                UART2_WriteChar('\n');

                UART2_WriteChar('L');
                UART2_WriteChar(':');
                UART2_WriteNumber(light);
                UART2_WriteChar('\n');

                UART2_WriteChar('F');
                UART2_WriteChar(':');
                UART2_WriteNumber(TIM2_CCR1 / 10);
                UART2_WriteChar('\n');

                status_requested = 0;
            }
//            // Print TEMP
//            UART2_WriteChar('T');
//            UART2_WriteChar(':');
//            UART2_WriteNumber(temp);
//            UART2_WriteChar('\n');
//
//            // Print LIGHT
//            UART2_WriteChar('L');
//            UART2_WriteChar(':');
//            UART2_WriteNumber(light);
//            UART2_WriteChar('\n');
            // Debug print
            int i = 0;
            while (rx_buffer[i] != '\0')
            {
                UART2_WriteChar(rx_buffer[i]);
                i++;
            }
            UART2_WriteChar('\n');

            index = 0;

        }
        else
        {
        	if (index < BUFFER_SIZE - 1)
        	{
        	    rx_buffer[index++] = c;
        	}
        }

    }

}
