################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/FreeRTOS/portable/port.c 

OBJS += \
./Src/FreeRTOS/portable/port.o 

C_DEPS += \
./Src/FreeRTOS/portable/port.d 


# Each subdirectory must supply rules for building sources it contributes
Src/FreeRTOS/portable/%.o Src/FreeRTOS/portable/%.su: ../Src/FreeRTOS/portable/%.c Src/FreeRTOS/portable/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I"C:/Users/arsha/STM32CubeIDE/STM32DISC1/RTOS_SoftTimer/FreeRTOS" -I"C:/Users/arsha/STM32CubeIDE/STM32DISC1/RTOS_SoftTimer/FreeRTOS/include" -I"C:/Users/arsha/STM32CubeIDE/STM32DISC1/RTOS_SoftTimer/FreeRTOS/portable" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-FreeRTOS-2f-portable

clean-Src-2f-FreeRTOS-2f-portable:
	-$(RM) ./Src/FreeRTOS/portable/port.d ./Src/FreeRTOS/portable/port.o ./Src/FreeRTOS/portable/port.su

.PHONY: clean-Src-2f-FreeRTOS-2f-portable

