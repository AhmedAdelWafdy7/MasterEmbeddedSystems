################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/Timer/Timer.c 

OBJS += \
./MCAL/Timer/Timer.o 

C_DEPS += \
./MCAL/Timer/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/Timer/%.o MCAL/Timer/%.su MCAL/Timer/%.cyclo: ../MCAL/Timer/%.c MCAL/Timer/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/HAL/inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/Inc" -I"D:/embeded Systems/STMdrivers/Smart_VehicleParking/MCAL/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-Timer

clean-MCAL-2f-Timer:
	-$(RM) ./MCAL/Timer/Timer.cyclo ./MCAL/Timer/Timer.d ./MCAL/Timer/Timer.o ./MCAL/Timer/Timer.su

.PHONY: clean-MCAL-2f-Timer

