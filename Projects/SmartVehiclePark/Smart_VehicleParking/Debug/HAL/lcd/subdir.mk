################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/lcd/lcd.c 

OBJS += \
./HAL/lcd/lcd.o 

C_DEPS += \
./HAL/lcd/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/lcd/%.o HAL/lcd/%.su HAL/lcd/%.cyclo: ../HAL/lcd/%.c HAL/lcd/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/HAL/inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/Inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-lcd

clean-HAL-2f-lcd:
	-$(RM) ./HAL/lcd/lcd.cyclo ./HAL/lcd/lcd.d ./HAL/lcd/lcd.o ./HAL/lcd/lcd.su

.PHONY: clean-HAL-2f-lcd

