#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskGetSchedulerState 1
#define xPortSysTickHandler SysTick_Handler
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define configUSE_PREEMPTION        1
#define configCPU_CLOCK_HZ          (16000000UL)
#define configTICK_RATE_HZ          (1000)

#define configMAX_PRIORITIES        5
#define configMINIMAL_STACK_SIZE    (128)
#define configTOTAL_HEAP_SIZE       (10 * 1024)

#define configMAX_TASK_NAME_LEN     16

#define configUSE_16_BIT_TICKS      0
#define configUSE_MUTEXES           1

#define configUSE_IDLE_HOOK         0   // 🔥 ADD
#define configUSE_TICK_HOOK         0   // 🔥 ADD

/* Interrupt priority config */
#define configPRIO_BITS                         4
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 5

#define configKERNEL_INTERRUPT_PRIORITY         ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

#define configUSE_TIMERS 1
#define configTIMER_TASK_PRIORITY 2
#define configTIMER_QUEUE_LENGTH 5
#define configTIMER_TASK_STACK_DEPTH 256

#endif
