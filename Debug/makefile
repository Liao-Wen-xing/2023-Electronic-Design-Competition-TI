################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/CCSv8/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./system_msp432e401y.obj" \
"./Hardware/ADC.obj" \
"./Hardware/DCMotor.obj" \
"./Hardware/Encoder.obj" \
"./Hardware/Key.obj" \
"./Hardware/OLED.obj" \
"./Hardware/Sevor.obj" \
"./Hardware/_UART.obj" \
"./System/Motor_Con.obj" \
"./System/Timer.obj" \
"./ccs/startup_msp432e401y_ccs.obj" \
"../msp432e401y.cmd" \
$(GEN_CMDS__FLAG) \
-l"ti/display/lib/display.aem4f" \
-l"ti/grlib/lib/ccs/m4f/grlib.a" \
-l"third_party/spiffs/lib/ccs/m4f/spiffs.a" \
-l"ti/drivers/lib/drivers_msp432e4.aem4f" \
-l"third_party/fatfs/lib/ccs/m4f/fatfs.a" \
-l"ti/devices/msp432e4/driverlib/lib/ccs/m4f/msp432e4_driverlib.a" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Hardware/subdir_vars.mk
-include System/subdir_vars.mk
-include ccs/subdir_vars.mk
-include subdir_rules.mk
-include Hardware/subdir_rules.mk
-include System/subdir_rules.mk
-include ccs/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
AAA_car.out \

EXE_OUTPUTS__QUOTED += \
"AAA_car.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "AAA_car.out"

# Tool invocations
AAA_car.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: Arm Linker'
	"D:/CCSv8/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=none --define=DeviceFamily_MSP432E4 --define=__MSP432E401Y__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"AAA_car.map" --stack_size=512 -i"D:/CCSv8/simplelink_msp432e4_sdk_4_20_00_12/source" -i"D:/CCSv8/ccs1230/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/lib" --diag_wrap=off --display_error_number --warn_sections --xml_link_info="AAA_car_linkInfo.xml" --rom_model -o "AAA_car.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "system_msp432e401y.obj" "Hardware\ADC.obj" "Hardware\DCMotor.obj" "Hardware\Encoder.obj" "Hardware\Key.obj" "Hardware\OLED.obj" "Hardware\Sevor.obj" "Hardware\_UART.obj" "System\Motor_Con.obj" "System\Timer.obj" "ccs\startup_msp432e401y_ccs.obj" 
	-$(RM) "main.d" "system_msp432e401y.d" "Hardware\ADC.d" "Hardware\DCMotor.d" "Hardware\Encoder.d" "Hardware\Key.d" "Hardware\OLED.d" "Hardware\Sevor.d" "Hardware\_UART.d" "System\Motor_Con.d" "System\Timer.d" "ccs\startup_msp432e401y_ccs.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

