DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
QM	= qemu-system-i386

KernelC		= main.c
KernelO		= ../build/kernel/obj/main.o
KernelS		= main.S
KernelB 	= ../build/kernel/bin/main.bin
Stage2O		= ../build/boot/obj/stage2.o

THIS_DIR    = ${shell dirname ${PWD}}

HEADER 		:= -I${THIS_DIR}/inc/
HEADER 		+= -I${THIS_DIR}/lib/
HEADER 		+= -I${THIS_DIR}/inc/libk

SRCS		:= ${THIS_DIR}/lib/kernel/tty.c
SRCO		:= ${THIS_DIR}/build/lib/obj/tty.o
SIOS		:= ${THIS_DIR}/lib/io/printk.c
SIOO		:= ${THIS_DIR}/build/lib/obj/printk.o
PICS		:= ${THIS_DIR}/devices/cpu/irq.c
PICO		:= ${THIS_DIR}/build/devices/cpu/irq.o

ASMS		:= ${THIS_DIR}/inc/asm/interrupt.S
ASMO		:= ${THIS_DIR}/build/kernel/obj/interrupt.o
CPUS		:= ${THIS_DIR}/inc/asm/irq.S
CPUO		:= ${THIS_DIR}/build/kernel/obj/irq.o

COLOR_INFO	:= \e[1;32m
COLOR_ERR	:= \e[1;31m
COLOR_WARN	:= \e[1;33m
COLOR_RESET := $<\e[0m

all: asmo srco kernelo link

kernelo:
	@echo "${COLOR_INFO}[   OBJ   ]${COLOR_RESET}    Proparing kerenl (Object file)..."
	@mkdir -p ../build/kernel/obj
	@if ${CC} ${HEADER} -ffreestanding -c ${KernelC} -o ${KernelO} -masm=intel; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

srco:
	@echo "${COLOR_INFO}[   OBJ   ]${COLOR_RESET}    Proparing source (Object file)..."
	@mkdir -p ../build/lib/obj
	@mkdir -p ../build/devices/cpu
	@if ${CC} ${HEADER} -ffreestanding -c ${SRCS} -o ${SRCO} -masm=intel && \
	${CC} ${HEADER} -ffreestanding -c ${SIOS} -o ${SIOO} -masm=intel && \
	${CC} ${HEADER} -ffreestanding -c ${PICS} -o ${PICO} -masm=intel; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

asmo:
	@echo "${COLOR_INFO}[   OBJ   ]${COLOR_RESET}    Proparing source files (Asm file)..."
	@mkdir -p ../build/kernel/obj
	@if ${AS} -felf ${ASMS} -o ${ASMO} && \
	${AS} -felf ${CPUS} -o ${CPUO}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

link:
	@echo "${COLOR_INFO}[   LNK   ]${COLOR_RESET}    Linking kerenl ..."
	@mkdir -p ../build/kernel/bin
	@if ${LD} -o ${KernelB} -Ttext 0x1000 ${Stage2O} ${KernelO} ${SRCO} ${ASMO} ${SIOO} ${PICO} ${CPUO} --oformat binary; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

clean:
	@echo "${COLOR_INFO}[   CLN   ]${COLOR_RESET}    Cleaning kerenl ..."
	@if rm -f ${KernelO} && \
	rm -f ${KernelB}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi