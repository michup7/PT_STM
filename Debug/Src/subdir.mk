################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/Pan_Tompkins.c \
../Src/RR_Arytmia.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/Pan_Tompkins.o \
./Src/RR_Arytmia.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/Pan_Tompkins.d \
./Src/RR_Arytmia.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/micha/OneDrive/Dokumenty/STM/CWICZENIA/DMA_EKG/Inc" -I"C:/Users/micha/OneDrive/Dokumenty/STM/CWICZENIA/DMA_EKG/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/micha/OneDrive/Dokumenty/STM/CWICZENIA/DMA_EKG/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/micha/OneDrive/Dokumenty/STM/CWICZENIA/DMA_EKG/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/micha/OneDrive/Dokumenty/STM/CWICZENIA/DMA_EKG/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


