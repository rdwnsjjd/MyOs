DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
CT  = cat
QM	= qemu-system-i386

KernelO		= kernel/kernel.o
KernelB		= kernel/main.bin
BootO		= boot/boot.o
BootB		= boot/boot.bin
Stage2O		= boot/stage2.o
KernelImg 	= os.bin

all: img run

# withoutlinking: dd run



img: booto kernelo
	@echo "[   LNK   ]    Proparing OS ..."
	@${CT} ${BootB} ${KernelB} > ${KernelImg}
	@echo "[   MSG   ]    Done!"

# dd: bootb kernelb
# 	@echo "Proparing kernel (Binary file)..."
# 	@${DD} if=${KernelImg} of=${BootB}  seek=1
# 	@echo "Done!"

kernelo:
	@ cd kernel && make

# kernelb:
# 	@ cd kernel && make kernelo && make link

booto:
	@ cd boot && make

# bootb:
# 	@ cd boot && make bootb

run:
	@echo "[   RUN   ]    Booting OS ..."
	@${QM} -fda ${KernelImg}

clean: cleank cleanb
	@echo "[   CLN   ]    Cleaning kerenl ..."
	@rm ${KernelImg}
	@echo "[   MSG   ]    Done!"

cleank:
	@ cd kernel && make clean

cleanb:
	@ cd boot && make clean