################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ccs/%.obj: ../ccs/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"D:/ti_IDE/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/MCU/msp/msp432/2023-Electronic-Design-Competition-TI/Hardware" --include_path="D:/MCU/msp/msp432/2023-Electronic-Design-Competition-TI/System" --include_path="D:/MCU/msp/msp432/2023-Electronic-Design-Competition-TI" --include_path="D:/TI/simplelink_msp432e4_sdk_3_40_01_02/source" --include_path="D:/TI/simplelink_msp432e4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="D:/TI/simplelink_msp432e4_sdk_3_40_01_02/source/ti/net/bsd" --include_path="D:/ti_IDE/ccs/tools/compiler/ti-cgt-arm_20.2.7.LTS/include" --advice:power=none --define=DeviceFamily_MSP432E4 --define=__MSP432E401Y__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="ccs/$(basename $(<F)).d_raw" --obj_directory="ccs" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


