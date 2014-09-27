################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ESN_detailed_localization.c \
../RFID_rough_localization.c \
../RFID_rough_localization_Lin.c \
../setup.c 

OBJS += \
./ESN_detailed_localization.o \
./RFID_rough_localization.o \
./RFID_rough_localization_Lin.o \
./setup.o 

C_DEPS += \
./ESN_detailed_localization.d \
./RFID_rough_localization.d \
./RFID_rough_localization_Lin.d \
./setup.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


