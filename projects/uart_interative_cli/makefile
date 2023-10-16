TARGET = uart_interactive_cli

INCLUDES += -I inc/

SRCS += src/main.c
SRCS += src/uart.c
SRCS += src/systick.c
SRCS += src/parser.c

LINKER_SCRIPT = ../../flash/STM32F446RETX_FLASH.ld

# Generate debug info
DEBUG = 1

# Choose processor
CDEFS  = -DSTM32F446xx
# Enable FPU
#CDEFS += -D__VFP_FP__

include ../armf4.mk