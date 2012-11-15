################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../Project_Settings/Startup_Code/56F80xx_init.asm \

ASM_SRCS_QUOTED += \
"../Project_Settings/Startup_Code/56F80xx_init.asm" \

OBJS += \
./Project_Settings/Startup_Code/56F80xx_init.o \

OBJS_QUOTED += \
"./Project_Settings/Startup_Code/56F80xx_init.o" \

OBJS_OS_FORMAT += \
./Project_Settings/Startup_Code/56F80xx_init.o \


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.asm
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: DSC Assembler'
	"$(DSC_ToolsDirEnv)/mwasm56800e" -msgstyle parseable -debug -nosyspath -i "$(ProjDirPath)/Project_Headers" -i "$(ProjDirPath)/Generated_Code" -i "$(ProjDirPath)/Sources" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


