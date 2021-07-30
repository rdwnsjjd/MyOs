DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
QM  = qemu-system-i386

BootS		= boot.asm
BootB		= boot.bin
BootO		= boot.o
Stage2S	    = stage2.asm
Stage2B	    = stage2.bin
Stage2O		= stage2.o

all: entry boot

entry:
	@echo "[   ELF   ]    Proparing entry file (Object file)..."
	@${AS} -felf ${Stage2S} -o ${Stage2O}
	@echo "[   MSG   ]    Done!"

boot:
	@echo "[   BIN   ]    Proparing bootloader (Binary file)..."
	@${AS} -fbin	${BootS}   -o ${BootB}
	@echo "[   MSG   ]    Done!"

run:
	@echo "[   RUN   ]    Booting bootloader ..."
	${QM} -fda ${BootB}

# clean:cleanb cleano

clean:
	@echo "[   CLN   ]    Cleaning bootloader (Object file)..."
	@rm ${Stage2O}
	@rm ${BootB}
	@echo "[   MSG   ]    Done!"

# cleanb:
# 	@echo "[   CLN   ]    Cleaning bootloader (Binary file)..."
# 	@rm ${BootB}
# 	@rm ${Stage2B}
# 	@echo "[   MSG   ]    Done!"