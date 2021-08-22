DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
QM	= qemu-system-i386

THIS_DIR    = ${shell dirname ${PWD}}

SRC		:= ${THIS_DIR}/devices/keyboard.c
OBJ		:= ../build/devices/keyboard.o

HEADER 		:= -I../inc/
HEADER 		+= -I../inc/libk/

COLOR_INFO	:= \e[1;32m
COLOR_ERR	:= \e[1;31m
COLOR_WARN	:= \e[1;33m
COLOR_RESET := $<\e[0m


devices: keyboard
		@cd cpu && make

keyboard:
	@echo "${COLOR_INFO}[   OBJ   ]${COLOR_RESET}    Proparing Devices (Object file)..."
	@mkdir -p ../build/devices
	@if ${CC} ${HEADER} -ffreestanding -c ${SRC} -o ${OBJ} -masm=intel; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
		false;\
	fi