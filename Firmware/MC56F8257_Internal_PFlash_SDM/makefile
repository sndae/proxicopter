################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 9
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(Gnu_Make_Install_DirEnv)/rm" -f

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ProxiCopter.elf \

EXECUTABLES_QUOTED += \
"ProxiCopter.elf" \

EXECUTABLES_OS_FORMAT += \
ProxiCopter.elf \


# All Target
all: ProxiCopter.elf

# Tool invocations
ProxiCopter.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #10 $@'
	@echo 'Invoking: DSC Linker'
	"$(DSC_ToolsDirEnv)/mwld56800e" -msgstyle parseable -g -nostdlib "$(ProjDirPath)/Project_Settings/Linker_Files/MC56F8257_Internal_PFlash_SDM.cmd" -main F_EntryPoint -L"$(MCUToolsBaseDirEnv)/M56800E Support/msl/MSL_C/DSP_56800E/lib" -o "ProxiCopter.elf" $(OBJS_QUOTED) $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CXX_DEPS_QUOTED) $(C_UPPER_DEPS_QUOTED) "./*/*.o" "./*/*/*.o"  $(CPP_DEPS_QUOTED) $(CC_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d"  ProxiCopter.elf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
