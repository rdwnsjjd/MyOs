#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <basic_types.h>
#include <string.h>
#include <kernel/tty.h>
#include<kernel/panic.h>

#if defined(__linux__)
#warning "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#warning "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

Terminal tty = {0};

Void main() {
    tty.col = 30;
    tty.row = 7;
    tty_init(&tty, VGA_LIGHT_GREY, VGA_BLACK);
    tty_print(&tty, "Hello from my kernel!");
    // tty_print(&tty, "This is my first kernel!\n");

    // panic(&tty, "Kernel Paniced!\n");
    // print("SALAM\n");
    // print("SALAM\n");
    // print("SALAM\n");
    // print("Hello from my kernel!\n");
    // print("This is my first kernel!\n");
    // print("SALAM");
    // print("SALAM");
    // print("SALAM");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("salam!");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("12");
    // print("SALAM!   sdf ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! SALAM! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
    // print("BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! BBBB! ");
}
