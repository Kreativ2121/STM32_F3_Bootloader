################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/adc.c \
../Src/dma.c \
../Src/gpio.c \
../Src/i2c.c \
../Src/stm32f3xx_hal_msp.c \
../Src/stm32f3xx_it.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f3xx.c \
../Src/tim.c \
../Src/usart.c 

CPP_SRCS += \
../Src/main.cpp 

C_DEPS += \
./Src/adc.d \
./Src/dma.d \
./Src/gpio.d \
./Src/i2c.d \
./Src/stm32f3xx_hal_msp.d \
./Src/stm32f3xx_it.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f3xx.d \
./Src/tim.d \
./Src/usart.d 

OBJS += \
./Src/adc.o \
./Src/dma.o \
./Src/gpio.o \
./Src/i2c.o \
./Src/main.o \
./Src/stm32f3xx_hal_msp.o \
./Src/stm32f3xx_it.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f3xx.o \
./Src/tim.o \
./Src/usart.o 

CPP_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Inc -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Device/ST/STM32F3xx/Include -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Include -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Device/ST/STM32F3xx/Include -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/%.o Src/%.su: ../Src/%.cpp Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Inc -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Device/ST/STM32F3xx/Include -IC:/Users/Administrator/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Include -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Device/ST/STM32F3xx/Include -IC:/Users/Kreativ/STM32Cube/Repository/STM32Cube_FW_F3_V1.11.3/Drivers/CMSIS/Include -Og -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/adc.d ./Src/adc.o ./Src/adc.su ./Src/dma.d ./Src/dma.o ./Src/dma.su ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/stm32f3xx_hal_msp.d ./Src/stm32f3xx_hal_msp.o ./Src/stm32f3xx_hal_msp.su ./Src/stm32f3xx_it.d ./Src/stm32f3xx_it.o ./Src/stm32f3xx_it.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32f3xx.d ./Src/system_stm32f3xx.o ./Src/system_stm32f3xx.su ./Src/tim.d ./Src/tim.o ./Src/tim.su ./Src/usart.d ./Src/usart.o ./Src/usart.su

.PHONY: clean-Src

