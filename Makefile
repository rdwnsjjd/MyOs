DD 	= dd
LD	= /home/rdwn/opt/cross/bin/i686-elf-ld
CC	= /home/rdwn/opt/cross/bin/i686-elf-gcc
AS	= nasm
CT  = cat
QM	= qemu-system-i386

KernelB		= build/kernel/bin/main.bin
BootB		= build/boot/bin/boot.bin
KernelBin 	= build/bin/os.bin
KernelImg   = build/img/os.img
KernelIso   = build/iso/os.iso

COLOR_INFO	:= \e[1;32m
COLOR_ERR	:= \e[1;31m
COLOR_WARN	:= \e[1;33m
COLOR_RESET := $<\e[0m

all: clear bin img iso run

iso:
	@echo "${COLOR_INFO}[   BLD   ]${COLOR_RESET}    Building OS (iso) ..."
	@mkdir -p build/iso
	@if genisoimage -quiet -V 'MYOS' -input-charset iso8859-1 -o ${KernelIso} -b os.img -hide os.img build/img; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

img:
	@echo "${COLOR_INFO}[   BLD   ]${COLOR_RESET}    Building OS (img) ..."
	@mkdir -p build/img
	@if dd if=/dev/zero of=${KernelImg} bs=1024 count=1440 && \
	dd if=${KernelBin} of=${KernelImg} seek=0 count=30 conv=notrunc; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

bin: booto kernelo
	@echo "${COLOR_INFO}[   LNK   ]${COLOR_RESET}    Proparing OS (bin) ..."
	@mkdir -p build/bin
	@if ${CT} ${BootB} ${KernelB} > ${KernelBin}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

kernelo:
	@ cd kernel && make

booto:
	@ cd boot && make

run:
	@echo "${COLOR_INFO}[   RUN   ]${COLOR_RESET}    Booting OS ..."
	@if ${QM} -fda ${KernelBin}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

clean: cleank cleanb
	@echo "${COLOR_INFO}[   CLN   ]${COLOR_RESET}    Cleaning kerenl ..."
	@if rm -f ${KernelBin} && \
	rm -f ${KernelImg} && \
	rm -f ${KernelIso} && \
	rm -rf build; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

cleank:
	@ cd kernel && make clean

cleanb:
	@ cd boot && make clean

clear:
	@clear