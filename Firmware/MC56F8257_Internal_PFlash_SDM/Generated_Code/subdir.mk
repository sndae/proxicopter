################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Generated_Code/AS1.c" \
"../Generated_Code/Cpu.c" \
"../Generated_Code/I2C2.c" \
"../Generated_Code/SM1.c" \
"../Generated_Code/Vectors.c" \

C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/I2C2.c \
../Generated_Code/SM1.c \
../Generated_Code/Vectors.c \

OBJS += \
./Generated_Code/AS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/I2C2.o \
./Generated_Code/SM1.o \
./Generated_Code/Vectors.o \

C_DEPS += \
./Generated_Code/AS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/I2C2.d \
./Generated_Code/SM1.d \
./Generated_Code/Vectors.d \

OBJS_QUOTED += \
"./Generated_Code/AS1.o" \
"./Generated_Code/Cpu.o" \
"./Generated_Code/I2C2.o" \
"./Generated_Code/SM1.o" \
"./Generated_Code/Vectors.o" \

OBJS_OS_FORMAT += \
./Generated_Code/AS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/I2C2.o \
./Generated_Code/SM1.o \
./Generated_Code/Vectors.o \

C_DEPS_QUOTED += \
"./Generated_Code/AS1.d" \
"./Generated_Code/Cpu.d" \
"./Generated_Code/I2C2.d" \
"./Generated_Code/SM1.d" \
"./Generated_Code/Vectors.d" \


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c -msgstyle parseable -g -i "$(ProjDirPath)/Project_Headers" -i "$(MCUToolsBaseDirEnv)/M56800E Support/runtime_56800E/include" -i "$(ProjDirPath)/Generated_Code" -i "$(ProjDirPath)/Sources" -I- -i "$(MCUToolsBaseDirEnv)/M56800E Support/msl/MSL_C/MSL_Common/Include" -I- -i "$(MCUToolsBaseDirEnv)/M56800E Support/msl/MSL_C/DSP_56800E/prefix" -I- -ir "$(MCUToolsBaseDirEnv)/M56800E Support" -w illpragmas -w possible -w extended -w extracomma -w emptydecl -w structclass -w notinlined -opt speed -requireprotos -o "$@" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Generated_Code/%.d: ../Generated_Code/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


