################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/drivers/core.c \
../src/drivers/eth.c \
../src/drivers/led.c \
../src/drivers/vga.c 

OBJS += \
./src/drivers/core.o \
./src/drivers/eth.o \
./src/drivers/led.o \
./src/drivers/vga.o 

C_DEPS += \
./src/drivers/core.d \
./src/drivers/eth.d \
./src/drivers/led.d \
./src/drivers/vga.d 


# Each subdirectory must supply rules for building sources it contributes
src/drivers/%.o: ../src/drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O2 -c -fmessage-length=0 -I../../standalone_bsp_0/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.50.c -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


