#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <basic_types.h>
#include <kernel/tty.h>
#include <kernel/panic.h>

#include <cpu/idt.h>
#include <cpu/gdt.h>
#include <cpu/cpu.h>

#include <drivers/keyboard.h>

#if defined(__linux__)
#warning "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#warning "This tutorial needs to be compiled with a ix86-elf compiler"
#endif


Void main() {
    tty_init(VGA_WHITE, VGA_BLUE);

    gdt_init();
    idt_init();

    keyboard_init();
    // keyboard_disable();
    // keyboard_init();

    tty_print("MyOs Kernel\n");
    tty_print("Copyright (C) 2021 Redwan. All rights reserved.\n");
    tty_print("\n> ");
        

    return;
}
