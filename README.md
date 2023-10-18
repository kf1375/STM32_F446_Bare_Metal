# STM32_F446_Bare_Metal

This repository was created to demonstrate my technical skills for the Firmware Developer role at Epitome GmbH. This repository contains two projects, "logger" and "uart_interactive_cli". Firmwares written in Bare-Metal for STs NUCLEO-F446. The projects were also evaluated on the hardware and their functionality was confirmed.

Common startup functions are located in the `include/startup_stm32f446retx.s` and `include/system_stm32f4xx.c` files to be included in all projects.

## Installation
The repository includes `CMSIS` as submodules under `lib` folder. You can clone the repository, then initialize and update the submodules with `git submodule init` and `git submodule update` commands.

## Compile
[makefile](projects/armf4.mk) contains necessary build scripts and compiler flags for all projects. Individual settings can be changed from local makefiles from projects such as [blinky makefile](projects/logger/makefile)

Browse into any directory and run `make` to compile.
```
cd projects/logger
make
```
If everything is set up correctly, you should see the completed message.
```
Cleaning logger
Building logger.c
   text    data     bss     dec     hex filename
    852	      8	   1568	   2428	    97c	logger.elf
Successfully finished...
```
## Program
Run `make burn` to program the chip. It uses `STM32_Programmer_CLI` as an uploading interface.
```
...
.. Flash written and verified!
```
## Projects

* [logger](projects/logger/) - Contains a pure C logging module and it streams the output through UART
* [uart_interative_cli](projects/uart_interative_cli/) - Accepts a string from the user over UART, interprets the string as commands with arguments, and gives back the corresponding response yo the user on UART.
