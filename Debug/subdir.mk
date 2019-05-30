################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Coord.cpp \
../Simulator.cpp \
../main.cpp 

OBJS += \
./Coord.o \
./Simulator.o \
./main.o 

CPP_DEPS += \
./Coord.d \
./Simulator.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I"/home/wagner/Dropbox/Wagner/C++/TCC/GeneticAI" -I"/home/wagner/Dropbox/Wagner/C++/TCC/NeuralNetwork" -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


