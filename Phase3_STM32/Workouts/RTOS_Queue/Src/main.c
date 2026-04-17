#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include "portable.h"
#include "queue.h"

QueueHandle_t myQueue;
/* RCC */
#define RCC_AHB1ENR (*(volatile uint32_t*)0x40023830)

/* GPIOD */
#define GPIOD_MODER (*(volatile uint32_t*)0x40020C00)
#define GPIOD_ODR   (*(volatile uint32_t*)0x40020C14)

void GPIO_Init(void)
{
    // Enable GPIOD clock
    RCC_AHB1ENR |= (1 << 3);

    // Set PD12 and PD13 as output
    GPIOD_MODER |= (1 << 24); // PD12
    GPIOD_MODER |= (1 << 26); // PD13
}
void Task1_Handler(void *params)
{
    int count = 0;

    while(1)
    {
        count++;

        xQueueSend(myQueue, &count, portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Task2_Handler(void *params)
{
    int received;

    while(1)
    {
        if(xQueueReceive(myQueue, &received, portMAX_DELAY))
        {
            if(received % 2 == 0)
                GPIOD_ODR |= (1 << 13);   // ON
            else
                GPIOD_ODR &= ~(1 << 13);  // OFF
        }
    }
}

int main(void)
{
    // Hardware init (clock, GPIO etc)
	GPIO_Init();
    // Create queue (can hold 5 integers)
    myQueue = xQueueCreate(5, sizeof(int));
    xTaskCreate(Task1_Handler, "Task1", 128, NULL, 2, NULL);
    xTaskCreate(Task2_Handler, "Task2", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1); // should never reach here
}
