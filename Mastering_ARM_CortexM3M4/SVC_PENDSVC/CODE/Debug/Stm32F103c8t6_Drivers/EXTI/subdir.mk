################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32F103c8t6_Drivers/EXTI/exti.c 

OBJS += \
./Stm32F103c8t6_Drivers/EXTI/exti.o 

C_DEPS += \
./Stm32F103c8t6_Drivers/EXTI/exti.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32F103c8t6_Drivers/EXTI/%.o Stm32F103c8t6_Drivers/EXTI/%.su Stm32F103c8t6_Drivers/EXTI/%.cyclo: ../Stm32F103c8t6_Drivers/EXTI/%.c Stm32F103c8t6_Drivers/EXTI/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Arm_Modes/CMSIS" -I"D:/embeded Systems/STMdrivers/Arm_Modes/Inc" -I"D:/embeded Systems/STMdrivers/Arm_Modes/HAL/INC" -I"D:/embeded Systems/STMdrivers/Arm_Modes/Stm32F103c8t6_Drivers/INC" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32F103c8t6_Drivers-2f-EXTI

clean-Stm32F103c8t6_Drivers-2f-EXTI:
	-$(RM) ./Stm32F103c8t6_Drivers/EXTI/exti.cyclo ./Stm32F103c8t6_Drivers/EXTI/exti.d ./Stm32F103c8t6_Drivers/EXTI/exti.o ./Stm32F103c8t6_Drivers/EXTI/exti.su

.PHONY: clean-Stm32F103c8t6_Drivers-2f-EXTI

