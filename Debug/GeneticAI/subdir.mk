################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/wagner/Dropbox/Wagner/C++/GeneticAI/CodeGenerator.cpp \
/home/wagner/Dropbox/Wagner/C++/GeneticAI/Dna.cpp \
/home/wagner/Dropbox/Wagner/C++/GeneticAI/GeneChain.cpp \
/home/wagner/Dropbox/Wagner/C++/GeneticAI/Organism.cpp \
/home/wagner/Dropbox/Wagner/C++/GeneticAI/Permutations.cpp 

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
GeneticAI/CodeGenerator.o: /home/wagner/Dropbox/Wagner/C++/GeneticAI/CodeGenerator.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

GeneticAI/Dna.o: /home/wagner/Dropbox/Wagner/C++/GeneticAI/Dna.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

GeneticAI/GeneChain.o: /home/wagner/Dropbox/Wagner/C++/GeneticAI/GeneChain.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

GeneticAI/Organism.o: /home/wagner/Dropbox/Wagner/C++/GeneticAI/Organism.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

GeneticAI/Permutations.o: /home/wagner/Dropbox/Wagner/C++/GeneticAI/Permutations.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I/home/wagner/Dropbox/Wagner/C++/TCC/include -I/home/wagner/Dropbox/Wagner/C++/waglib -I/home/wagner/Dropbox/Wagner/C++/GeneticAI -I/home/wagner/Dropbox/Wagner/C++/NeuralNetwork -O0 -g3 -w -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


