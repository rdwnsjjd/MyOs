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

COLOR_INFO	:= \e[1;32m
COLOR_ERR	:= \e[1;31m
COLOR_WARN	:= \e[1;33m
COLOR_RESET := $<\e[0m

all: entry boot

entry:
	@echo "${COLOR_INFO}[   OBJ   ]${COLOR_RESET}    Proparing entry file (Object file)..."
	@mkdir -p ../build/boot/obj
	@if ${AS} -felf ${Stage2S} -o ${Stage2O}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

boot:
	@echo "${COLOR_INFO}[   BIN   ]${COLOR_RESET}    Proparing bootloader (Binary file)..."
	@mkdir -p ../build/boot/bin
	@if ${AS} -fbin	${BootS} -o ${BootB}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

run:
	@echo "${COLOR_INFO}[   RUN   ]${COLOR_RESET}    Booting bootloader ..."
	@if ${QM} -fda ${BootB}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi

clean:
	@echo "${COLOR_INFO}[   CLN   ]${COLOR_RESET}    Cleaning bootloader (Object file)..."
	@if rm -f ${Stage2O} && \
	rm -f ${BootB}; \
		then echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"; \
	else \
		echo "${COLOR_ERR}[   ERR   ]${COLOR_RESET}    Failed!"; \
	fi
	@echo "${COLOR_INFO}[   MSG   ]${COLOR_RESET}    Done!"
