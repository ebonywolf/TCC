################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../GeneticAI/CodeGenerator.cpp \
../GeneticAI/Dna.cpp \
../GeneticAI/GeneChain.cpp \
../GeneticAI/Organism.cpp \
../GeneticAI/Permutations.cpp 

OBJS += \
./GeneticAI/CodeGenerator.o \
./GeneticAI/Dna.o \
./GeneticAI/GeneChain.o \
./GeneticAI/Organism.o \
./GeneticAI/Permutations.o 

CPP_DEPS += \
./GeneticAI/CodeGenerator.d \
./GeneticAI/Dna.d \
./GeneticAI/GeneChain.d \
./GeneticAI/Organism.d \
./GeneticAI/Permutations.d 


# Each subdirectory must supply rules for building sources it contributes
GeneticAI/%.o: ../GeneticAI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I"/home/wagner/Dropbox/Wagner/C++/TCC/GeneticAI" -I"/home/wagner/Dropbox/Wagner/C++/TCC/NeuralNetwork" -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


