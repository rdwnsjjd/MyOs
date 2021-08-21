DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
QM	= qemu-system-i386

THIS_DIR    = ${shell dirname ${PWD}}

SRC		:= ${THIS_DIR}/asm/segment.S
OBJ		:= ../../build/kernel/obj/segment.o

COLOR_INFO	:= \e[1;32m
COLOR_ERR	:= \e[1;31m
COLOR_WARN	:= \e[1;33m
COLOR_RESET := $<\e[0m

asm:
	@echo "${COLOR_INFO}[   OBJ   ]${COLOR_RESET}    Proparing source files (Asm headers)..."
	@mkdir -p ../../build/kernel/obj
	@if ${AS} -felf ${SRC} -o ${OBJ}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
		false; \
	fi