################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/FreeRTOS/heap_4.c \
../Src/FreeRTOS/list.c \
../Src/FreeRTOS/queue.c \
../Src/FreeRTOS/tasks.c 

OBJS += \
./Src/FreeRTOS/heap_4.o \
./Src/FreeRTOS/list.o \
./Src/FreeRTOS/queue.o \
./Src/FreeRTOS/tasks.o 

C_DEPS += \
./Src/FreeRTOS/heap_4.d \
./Src/FreeRTOS/list.d \
./Src/FreeRTOS/queue.d \
./Src/FreeRTOS/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
Src/FreeRTOS/%.o Src/FreeRTOS/%.su: ../Src/FreeRTOS/%.c Src/FreeRTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/arsha/STM32CubeIDE/STM32DISC1/RTOS_LED/FreeRTOS" -I"C:/Users/arsha/STM32CubeIDE/STM32DISC1/RTOS_LED/FreeRTOS/include" -I"C:/Users/arsha/STM32CubeIDE/STM32DISC1/RTOS_LED/FreeRTOS/portable" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-FreeRTOS

clean-Src-2f-FreeRTOS:
	-$(RM) ./Src/FreeRTOS/heap_4.d ./Src/FreeRTOS/heap_4.o ./Src/FreeRTOS/heap_4.su ./Src/FreeRTOS/list.d ./Src/FreeRTOS/list.o ./Src/FreeRTOS/list.su ./Src/FreeRTOS/queue.d ./Src/FreeRTOS/queue.o ./Src/FreeRTOS/queue.su ./Src/FreeRTOS/tasks.d ./Src/FreeRTOS/tasks.o ./Src/FreeRTOS/tasks.su

.PHONY: clean-Src-2f-FreeRTOS

