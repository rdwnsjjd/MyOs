#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <basic_types.h>
#include <kernel/tty.h>
#include <kernel/panic.h>

#include <cpu/idt.h>

#include <drivers/keyboard.h>

#if defined(__linux__)
#warning "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#warning "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

#include <cpu/gdt.h>
#include <cpu/cpu.h>


Void main() {
    tty_init(VGA_LIGHT_GREY, VGA_BLUE);
    // panic("Paniced!");  

    gdt_init();
    idt_init();

    __asm__ volatile ("int 33");

    // static char s[16] = "BogusProces!";
	// cpuid_string(0, (int*)(s));
    // tty_print(s);

    tty_print("HELLO!\n");

    // keyboard_init();
}
