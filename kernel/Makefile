DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
QM	= qemu-system-i386

KernelC		= main.c
KernelO		= main.o
KernelS		= main.S
KernelB 	= main.bin
Stage2O		= ../boot/stage2.o

THIS_DIR    = ${shell dirname ${PWD}}

HEADER 		:= -I${THIS_DIR}/inc/
HEADER 		+= -I${THIS_DIR}/lib/

SRCS		:= ${THIS_DIR}/lib/src/kernel/tty.c
SRCO		:= ${THIS_DIR}/lib/src/kernel/tty.o

all:	kernelo link

kernelo:
	@echo "[   ELF   ]    Proparing kerenl (Object file)..."
	${CC} ${HEADER} -ffreestanding -c ${SRCS} -o ${SRCO} -masm=intel
	${CC} ${HEADER} -ffreestanding -c ${KernelC} -o ${KernelO} -masm=intel
	@echo "[   MSG   ]    Done!"

link:
	@echo "[   LNK   ]    Linking kerenl ..."
	@${LD} -o ${KernelB} -Ttext 0x1000 ${Stage2O} ${KernelO} --oformat binary
	@echo "[   MSG   ]    Done!"

clean:
	@echo "[   CLN   ]    Cleaning kerenl ..."
	@rm ${KernelO}
	@rm ${KernelB}
	@echo "[   MSG   ]    Done!"