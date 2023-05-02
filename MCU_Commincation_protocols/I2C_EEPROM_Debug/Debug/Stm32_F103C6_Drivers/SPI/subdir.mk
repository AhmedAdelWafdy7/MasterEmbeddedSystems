################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.c 

OBJS += \
./Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.o 

C_DEPS += \
./Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/SPI/%.o Stm32_F103C6_Drivers/SPI/%.su Stm32_F103C6_Drivers/SPI/%.cyclo: ../Stm32_F103C6_Drivers/SPI/%.c Stm32_F103C6_Drivers/SPI/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -c -I../Inc -I"D:/embeded Systems/STMdrivers/Drivers/HAL/inc" -I"D:/embeded Systems/STMdrivers/Drivers/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-SPI

clean-Stm32_F103C6_Drivers-2f-SPI:
	-$(RM) ./Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.cyclo ./Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.d ./Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.o ./Stm32_F103C6_Drivers/SPI/Stm32_F103C6_SPI.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-SPI

