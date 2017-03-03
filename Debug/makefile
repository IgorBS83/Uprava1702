################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv5/tools/compiler/c6000_7.4.4

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./main.obj" \
"./TMR_Init.obj" \
"./Protocol.obj" \
"./PLL_Init.obj" \
"./INT_Init.obj" \
"./GPIO_Init.obj" \
"./EMIFA_Init.obj" \
"./EDMA3_Init.obj" \
"./Dispatcher.obj" \
"./Corr.obj" \
"./BootLoader.obj" \
"./AlgEnargy.obj" \
"./AlgCoiSea.obj" \
"./AlgCoi.obj" \
"../C6455.cmd" \
-l"D:\Documents\CCS_Projects\MathFuncs\Release\MathFuncs.lib" \
-l"C:\ti\sprc234(C6455 Chip Support Library (CSL))\6455\default_package\csl_c6455\lib\csl_c6455.lib" \
-l"C:\ti\sprc234(C6455 Chip Support Library (CSL))\6455\default_package\csl_c64xplus_intc\lib\csl_c64xplus_intc.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Uprava1702.out

# Tool invocations
Uprava1702.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C6000 Linker'
	"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/cl6x" -mv64+ --abi=coffabi -O2 -g --define=c6455 --display_error_number --diag_warning=225 --diag_wrap=off -z --stack_size=0x800 -m"Uprava1702.map" --heap_size=0x800 -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/lib" -i"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="Uprava1702_linkInfo.xml" --rom_model -o "Uprava1702.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(C6000_EXECUTABLE_OUTPUTS__QUOTED) "Uprava1702.out"
	-$(RM) "AlgCoi.pp" "AlgCoiSea.pp" "AlgEnargy.pp" "Corr.pp" "Dispatcher.pp" "EDMA3_Init.pp" "EMIFA_Init.pp" "GPIO_Init.pp" "INT_Init.pp" "PLL_Init.pp" "Protocol.pp" "TMR_Init.pp" "main.pp" 
	-$(RM) "AlgCoi.obj" "AlgCoiSea.obj" "AlgEnargy.obj" "BootLoader.obj" "Corr.obj" "Dispatcher.obj" "EDMA3_Init.obj" "EMIFA_Init.obj" "GPIO_Init.obj" "INT_Init.obj" "PLL_Init.obj" "Protocol.obj" "TMR_Init.obj" "main.obj" 
	-$(RM) "BootLoader.pp" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"C:/ti/ccsv5/tools/compiler/c6000_7.4.4/bin/hex6x" C6Hex.cmd
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets

