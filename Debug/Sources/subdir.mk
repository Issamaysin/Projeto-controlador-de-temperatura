################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/UART.c \
../Sources/adc.c \
../Sources/aquecedorECooler.c \
../Sources/communicationStateMachine.c \
../Sources/filter.c \
../Sources/fsl_debug_console.c \
../Sources/interfacelocal.c \
../Sources/lcd.c \
../Sources/ledSwi.c \
../Sources/ledrgb.c \
../Sources/lptmr.c \
../Sources/lut_adc_3v3.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/pid.c \
../Sources/print_scan.c \
../Sources/tacometro.c \
../Sources/timer.c \
../Sources/util.c 

OBJS += \
./Sources/UART.o \
./Sources/adc.o \
./Sources/aquecedorECooler.o \
./Sources/communicationStateMachine.o \
./Sources/filter.o \
./Sources/fsl_debug_console.o \
./Sources/interfacelocal.o \
./Sources/lcd.o \
./Sources/ledSwi.o \
./Sources/ledrgb.o \
./Sources/lptmr.o \
./Sources/lut_adc_3v3.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/pid.o \
./Sources/print_scan.o \
./Sources/tacometro.o \
./Sources/timer.o \
./Sources/util.o 

C_DEPS += \
./Sources/UART.d \
./Sources/adc.d \
./Sources/aquecedorECooler.d \
./Sources/communicationStateMachine.d \
./Sources/filter.d \
./Sources/fsl_debug_console.d \
./Sources/interfacelocal.d \
./Sources/lcd.d \
./Sources/ledSwi.d \
./Sources/ledrgb.d \
./Sources/lptmr.d \
./Sources/lut_adc_3v3.d \
./Sources/main.d \
./Sources/mcg.d \
./Sources/pid.d \
./Sources/print_scan.d \
./Sources/tacometro.d \
./Sources/timer.d \
./Sources/util.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL25Z4/include" -I"C:\Freescale\KSDK_1.2.0/platform/osa/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/system/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


