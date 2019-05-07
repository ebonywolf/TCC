################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/wagner/Dropbox/Wagner/C++/NeuralNetwork/Functions.cpp \
/home/wagner/Dropbox/Wagner/C++/NeuralNetwork/NeuralNetwork.cpp \
/home/wagner/Dropbox/Wagner/C++/NeuralNetwork/Neuron.cpp 

OBJS += \
./NeuralNetwork/Functions.o \
./NeuralNetwork/NeuralNetwork.o \
./NeuralNetwork/Neuron.o 

CPP_DEPS += \
./NeuralNetwork/Functions.d \
./NeuralNetwork/NeuralNetwork.d \
./NeuralNetwork/Neuron.d 


# Each subdirectory must supply rules for building sources it contributes
NeuralNetwork/Functions.o: /home/wagner/Dropbox/Wagner/C++/NeuralNetwork/Functions.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

NeuralNetwork/NeuralNetwork.o: /home/wagner/Dropbox/Wagner/C++/NeuralNetwork/NeuralNetwork.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

NeuralNetwork/Neuron.o: /home/wagner/Dropbox/Wagner/C++/NeuralNetwork/Neuron.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


