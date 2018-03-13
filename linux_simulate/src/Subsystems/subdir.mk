################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Subsystems/DriveTrain.cpp \
../src/Subsystems/Gripper.cpp \
../src/Subsystems/LiftMast.cpp 

OBJS += \
./src/Subsystems/DriveTrain.o \
./src/Subsystems/Gripper.o \
./src/Subsystems/LiftMast.o 

CPP_DEPS += \
./src/Subsystems/DriveTrain.d \
./src/Subsystems/Gripper.d \
./src/Subsystems/LiftMast.d 


# Each subdirectory must supply rules for building sources it contributes
src/Subsystems/%.o: ../src/Subsystems/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\Robotics\eclipse-workspace\6856_2018/src" -IC:\Users\Robotics/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -Og -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


