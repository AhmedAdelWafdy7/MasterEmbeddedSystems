################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/servo/servo.c 

OBJS += \
./HAL/servo/servo.o 

C_DEPS += \
./HAL/servo/servo.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/servo/%.o HAL/servo/%.su HAL/servo/%.cyclo: ../HAL/servo/%.c HAL/servo/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/HAL/inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/Inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-servo

clean-HAL-2f-servo:
	-$(RM) ./HAL/servo/servo.cyclo ./HAL/servo/servo.d ./HAL/servo/servo.o ./HAL/servo/servo.su

.PHONY: clean-HAL-2f-servo

