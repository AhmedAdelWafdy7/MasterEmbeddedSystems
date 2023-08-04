################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_RTOS/CortexMX_OS_PORTING.c \
../MY_RTOS/My_RTOS_FIFO.c \
../MY_RTOS/Scheduler.c 

OBJS += \
./MY_RTOS/CortexMX_OS_PORTING.o \
./MY_RTOS/My_RTOS_FIFO.o \
./MY_RTOS/Scheduler.o 

C_DEPS += \
./MY_RTOS/CortexMX_OS_PORTING.d \
./MY_RTOS/My_RTOS_FIFO.d \
./MY_RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MY_RTOS/%.o MY_RTOS/%.su MY_RTOS/%.cyclo: ../MY_RTOS/%.c MY_RTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Arm_Modes/MY_RTOS/inc" -I"D:/embeded Systems/STMdrivers/Arm_Modes/CMSIS" -I"D:/embeded Systems/STMdrivers/Arm_Modes/Inc" -I"D:/embeded Systems/STMdrivers/Arm_Modes/HAL/INC" -I"D:/embeded Systems/STMdrivers/Arm_Modes/Stm32F103c8t6_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MY_RTOS

clean-MY_RTOS:
	-$(RM) ./MY_RTOS/CortexMX_OS_PORTING.cyclo ./MY_RTOS/CortexMX_OS_PORTING.d ./MY_RTOS/CortexMX_OS_PORTING.o ./MY_RTOS/CortexMX_OS_PORTING.su ./MY_RTOS/My_RTOS_FIFO.cyclo ./MY_RTOS/My_RTOS_FIFO.d ./MY_RTOS/My_RTOS_FIFO.o ./MY_RTOS/My_RTOS_FIFO.su ./MY_RTOS/Scheduler.cyclo ./MY_RTOS/Scheduler.d ./MY_RTOS/Scheduler.o ./MY_RTOS/Scheduler.su

.PHONY: clean-MY_RTOS

