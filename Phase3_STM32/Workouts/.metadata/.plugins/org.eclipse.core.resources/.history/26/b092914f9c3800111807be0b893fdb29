#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdint.h>

/* RCC */
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)
#define RCC_APB1ENR (*(volatile uint32_t*)0x40023840)

/* GPIOA */
#define GPIOA_MODER (*(volatile uint32_t*)0x40020000)
#define GPIOA_AFRL  (*(volatile uint32_t*)0x40020020)

/* USART2 */
#define USART2_SR   (*(volatile uint32_t*)0x40004400)
#define USART2_DR   (*(volatile uint32_t*)0x40004404)
#define USART2_BRR  (*(volatile uint32_t*)0x40004408)
#define USART2_CR1  (*(volatile uint32_t*)0x4000440C)

QueueHandle_t dataQueue;

/* UART INIT */
void UART2_Init(void)
{
    RCC_AHB1ENR |= (1 << 0);
    RCC_APB1ENR |= (1 << 17);

    GPIOA_MODER &= ~(3 << 4);
    GPIOA_MODER |=  (2 << 4);

    GPIOA_AFRL &= ~(0xF << 8);
    GPIOA_AFRL |=  (7 << 8);

    USART2_BRR = 0x008B; // 115200 @16MHz

    USART2_CR1 |= (1 << 3);
    USART2_CR1 |= (1 << 13);
}

/* UART SEND */
void UART_SendChar(char c)
{
    while(!(USART2_SR & (1 << 7)));
    USART2_DR = c;
}

/* SEND NUMBER AS ASCII */
void UART_SendNumber(uint32_t num)
{
    char buffer[10];
    int i = 0;

    if(num == 0)
    {
        UART_SendChar('0');
        return;
    }

    while(num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    for(int j = i - 1; j >= 0; j--)
    {
        UART_SendChar(buffer[j]);
    }
}

/* TASK 1: PRODUCER */
void Task1_Handler(void *params)
{
    uint32_t count = 0;

    while(1)
    {
        count++;

        xQueueSend(dataQueue, &count, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* TASK 2: CONSUMER */
void Task2_Handler(void *params)
{
    uint32_t receivedData;

    while(1)
    {
        if(xQueueReceive(dataQueue, &receivedData, portMAX_DELAY))
        {
            UART_SendNumber(receivedData);
            UART_SendChar('\n');
        }
    }
}

/* MAIN */
int main(void)
{
    UART2_Init();

    dataQueue = xQueueCreate(5, sizeof(uint32_t));

    if(dataQueue == NULL)
    {
        while(1); // error
    }

    xTaskCreate(Task1_Handler, "Producer", 128, NULL, 1, NULL);
    xTaskCreate(Task2_Handler, "Consumer", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1);
}
