DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
CT  = cat
QM	= qemu-system-i386

KernelB		= build/kernel/bin/main.bin
BootB		= build/boot/bin/boot.bin
KernelImg 	= build/img/os.bin

all: img run

img: booto kernelo
	@echo "[   LNK   ]    Proparing OS ..."
	@mkdir -p build/img
	@${CT} ${BootB} ${KernelB} > ${KernelImg}
	@echo "[   MSG   ]    Done!"

kernelo:
	@ cd kernel && make

booto:
	@ cd boot && make

run:
	@echo "[   RUN   ]    Booting OS ..."
	@${QM} -fda ${KernelImg}

clean: cleank cleanb
	@echo "[   CLN   ]    Cleaning kerenl ..."
	@rm -f ${KernelImg}
	@rm -rf build
	@echo "[   MSG   ]    Done!"

cleank:
	@ cd kernel && make clean

cleanb:
	@ cd boot && make clean