################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/keypad/keypad.c 

OBJS += \
./HAL/keypad/keypad.o 

C_DEPS += \
./HAL/keypad/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/keypad/%.o HAL/keypad/%.su HAL/keypad/%.cyclo: ../HAL/keypad/%.c HAL/keypad/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/HAL/inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/Inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-keypad

clean-HAL-2f-keypad:
	-$(RM) ./HAL/keypad/keypad.cyclo ./HAL/keypad/keypad.d ./HAL/keypad/keypad.o ./HAL/keypad/keypad.su

.PHONY: clean-HAL-2f-keypad

