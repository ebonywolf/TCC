################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../NeuralNetwork/BasicNN.cpp \
../NeuralNetwork/Functions.cpp \
../NeuralNetwork/NeuralNetwork.cpp \
../NeuralNetwork/Neuron.cpp 

OBJS += \
./NeuralNetwork/BasicNN.o \
./NeuralNetwork/Functions.o \
./NeuralNetwork/NeuralNetwork.o \
./NeuralNetwork/Neuron.o 

CPP_DEPS += \
./NeuralNetwork/BasicNN.d \
./NeuralNetwork/Functions.d \
./NeuralNetwork/NeuralNetwork.d \
./NeuralNetwork/Neuron.d 


# Each subdirectory must supply rules for building sources it contributes
NeuralNetwork/%.o: ../NeuralNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I"/home/wagner/Dropbox/Wagner/C++/TCC/GeneticAI" -I"/home/wagner/Dropbox/Wagner/C++/TCC/NeuralNetwork" -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


