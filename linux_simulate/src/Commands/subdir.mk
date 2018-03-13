################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Commands/DebugTalonSRXTester.cpp \
../src/Commands/DriveWithJoystick.cpp \
../src/Commands/ExampleCommand.cpp \
../src/Commands/GripperControl.cpp \
../src/Commands/LiftControl.cpp \
../src/Commands/MyAutoCommand.cpp 

OBJS += \
./src/Commands/DebugTalonSRXTester.o \
./src/Commands/DriveWithJoystick.o \
./src/Commands/ExampleCommand.o \
./src/Commands/GripperControl.o \
./src/Commands/LiftControl.o \
./src/Commands/MyAutoCommand.o 

CPP_DEPS += \
./src/Commands/DebugTalonSRXTester.d \
./src/Commands/DriveWithJoystick.d \
./src/Commands/ExampleCommand.d \
./src/Commands/GripperControl.d \
./src/Commands/LiftControl.d \
./src/Commands/MyAutoCommand.d 


# Each subdirectory must supply rules for building sources it contributes
src/Commands/%.o: ../src/Commands/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -I"C:\Users\Robotics\eclipse-workspace\6856_2018/src" -IC:\Users\Robotics/wpilib/simulation/include -I/usr/include -I/usr/include/gazebo-6.5 -I/usr/include/ignition/math2 -I/usr/include/sdformat-3.7 -O0 -Og -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


