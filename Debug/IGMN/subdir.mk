################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IGMN/constants.cpp \
../IGMN/igmn.cpp \
../IGMN/statistic.cpp 

OBJS += \
./IGMN/constants.o \
./IGMN/igmn.o \
./IGMN/statistic.o 

CPP_DEPS += \
./IGMN/constants.d \
./IGMN/igmn.d \
./IGMN/statistic.d 


# Each subdirectory must supply rules for building sources it contributes
IGMN/%.o: ../IGMN/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


