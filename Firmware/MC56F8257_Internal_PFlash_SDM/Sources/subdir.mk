################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/ProcessorExpert.c" \
"../Sources/Quad_Functions.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/ProcessorExpert.c \
../Sources/Quad_Functions.c \

OBJS += \
./Sources/Events.o \
./Sources/ProcessorExpert.o \
./Sources/Quad_Functions.o \

C_DEPS += \
./Sources/Events.d \
./Sources/ProcessorExpert.d \
./Sources/Quad_Functions.d \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/ProcessorExpert.o" \
"./Sources/Quad_Functions.o" \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/ProcessorExpert.o \
./Sources/Quad_Functions.o \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/ProcessorExpert.d" \
"./Sources/Quad_Functions.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: DSC Compiler'
	"$(DSC_ToolsDirEnv)/mwcc56800e" -c -msgstyle parseable -g -i "$(ProjDirPath)/Project_Headers" -i "$(MCUToolsBaseDirEnv)/M56800E Support/runtime_56800E/include" -i "$(ProjDirPath)/Generated_Code" -i "$(ProjDirPath)/Sources" -I- -i "$(MCUToolsBaseDirEnv)/M56800E Support/msl/MSL_C/MSL_Common/Include" -I- -i "$(MCUToolsBaseDirEnv)/M56800E Support/msl/MSL_C/DSP_56800E/prefix" -I- -ir "$(MCUToolsBaseDirEnv)/M56800E Support" -w illpragmas -w possible -w extended -w extracomma -w emptydecl -w structclass -w notinlined -opt speed -requireprotos -o "$@" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


