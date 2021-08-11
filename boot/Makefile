DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
QM  = qemu-system-i386

BootS		= boot.S
BootB		= ../build/boot/bin/boot.bin
BootO		= ../build/boot/obj/boot.o
Stage2S	    = stage2.S
Stage2B	    = ../build/boot/bin/stage2.bin
Stage2O		= ../build/boot/obj/stage2.o

all: entry boot

entry:
	@echo "[   ELF   ]    Proparing entry file (Object file)..."
	@mkdir -p ../build/boot/obj
	@${AS} -felf ${Stage2S} -o ${Stage2O}
	@echo "[   MSG   ]    Done!"

boot:
	@echo "[   BIN   ]    Proparing bootloader (Binary file)..."
	@mkdir -p ../build/boot/bin
	@${AS} -fbin	${BootS}   -o ${BootB}
	@echo "[   MSG   ]    Done!"

run:
	@echo "[   RUN   ]    Booting bootloader ..."
	${QM} -fda ${BootB}

clean:
	@echo "[   CLN   ]    Cleaning bootloader (Object file)..."
	@rm -f ${Stage2O}
	@rm -f ${BootB}
	@echo "[   MSG   ]    Done!"
