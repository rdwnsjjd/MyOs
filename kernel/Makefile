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
# SRCS		+= ${THIS_DIR}/lib/io/printk.c

SRCO		:= ${THIS_DIR}/build/lib/obj/tty.o
# SRCO		:= ${THIS_DIR}/build/lib/obj/printk.o

ASMS		:= ${THIS_DIR}/inc/asm/interrupt.S
ASMO		:= ${THIS_DIR}/build/kernel/interrupt.o

# ASMO		+= ${THIS_DIR}/build/kernel/interrupt.o
# ASMO		+= ${THIS_DIR}/build/kernel/irq.o

CPUS		:= ${THIS_DIR}/inc/asm/irq.S
CPUO		:= ${THIS_DIR}/build/kernel/irq.o

all: asmo srco kernelo link

kernelo:
	@echo "[   ELF   ]    Proparing kerenl (Object file)..."
	@mkdir -p ../build/kernel/obj
	@${CC} ${HEADER} -ffreestanding -c ${KernelC} -o ${KernelO} -masm=intel
	@echo "[   MSG   ]    Done!"

srco:
	@echo "[   ELF   ]    Proparing source (Object file)..."
	@mkdir -p ../build/lib/obj
	@${CC} ${HEADER} -ffreestanding -c ${SRCS} -o ${SRCO} -masm=intel
	@${CC} ${HEADER} -ffreestanding -c ${THIS_DIR}/lib/io/printk.c -o ${THIS_DIR}/build/lib/obj/printk.o -masm=intel
	@echo "[   MSG   ]    Done!"

asmo:
	@echo "[   ELF   ]    Proparing source files (Asm file)..."
	@mkdir -p ../build/kernel/obj
	@${AS} -felf ${ASMS} -o ${ASMO}
	@${AS} -felf ${CPUS} -o ${CPUO}
	@echo "[   MSG   ]    Done!"

link:
	@echo "[   LNK   ]    Linking kerenl ..."
	@mkdir -p ../build/kernel/bin
	@${LD} -o ${KernelB} -Ttext 0x1000 ${Stage2O} ${KernelO} ${SRCO} ${ASMO} ${CPUO} --oformat binary
	@echo "[   MSG   ]    Done!"

clean:
	@echo "[   CLN   ]    Cleaning kerenl ..."
	@rm -f ${KernelO}
	@rm -f ${KernelB}
	@echo "[   MSG   ]    Done!"